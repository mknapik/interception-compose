#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "event.h"

// clang-format off
const struct input_event
        tab_up =           {.type = EV_KEY, .code = KEY_TAB,       .value = 0},
        backslash_up =     {.type = EV_KEY, .code = KEY_BACKSLASH, .value = 0},
        compose_up =       {.type = EV_KEY, .code = KEY_COMPOSE,   .value = 0},
        tab_down =         {.type = EV_KEY, .code = KEY_TAB,       .value = 1},
        backslash_down =   {.type = EV_KEY, .code = KEY_BACKSLASH, .value = 1},
        compose_down =     {.type = EV_KEY, .code = KEY_COMPOSE,   .value = 1},
        tab_repeat =       {.type = EV_KEY, .code = KEY_TAB,       .value = 2},
        backslash_repeat = {.type = EV_KEY, .code = KEY_BACKSLASH, .value = 2},
        compose_repeat =   {.type = EV_KEY, .code = KEY_COMPOSE,   .value = 2};
// clang-format on

int main(int argc, char* argv[]) {
  int is_mapped_key_down = 0, compose_give_up = 0;
  struct input_event input;
  const struct input_event *mapped_down, *mapped_repeat, *mapped_up;

  if (argc != 2) {
    printf("Program accepts exactly one argument: tab or backslash");
    exit(1);
  }

  if (!strcmp(argv[1], "backslash") || !strcmp(argv[1], "tab")) {
    if (!strcmp(argv[1], "backslash")) {
      mapped_down = &backslash_down;
      mapped_up = &backslash_up;
      mapped_repeat = &backslash_repeat;
    }
    if (!strcmp(argv[1], "tab")) {
      mapped_down = &tab_down;
      mapped_up = &tab_up;
      mapped_repeat = &tab_repeat;
    }
  }

  setbuf(stdin, NULL), setbuf(stdout, NULL);

  while (read_event(&input)) {
    if (input.type != EV_KEY) {
      write_event(&input);
      continue;
    }

    if (is_mapped_key_down) {
      if (equal(&input, mapped_down) || equal(&input, mapped_repeat)) {
        continue;
      }

      if (equal(&input, mapped_up)) {
        is_mapped_key_down = 0;

        if (compose_give_up) {
          compose_give_up = 0;
          write_event(&compose_up);
          continue;
        }

        write_event(mapped_down);
        write_event(mapped_up);
        continue;
      }

      if (!compose_give_up && input.value) {
        compose_give_up = 1;
        write_event(&compose_down);
      }
    } else {
      if (equal(&input, mapped_down)) {
        is_mapped_key_down = 1;
        continue;
      }
    }

    write_event(&input);
  }
}
