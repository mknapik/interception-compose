#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "event.h"

// clang-format off
const struct input_event
        ctrl_up =           {.type = EV_KEY, .code = KEY_LEFTCTRL, .value = 0},
        ctrl_down =         {.type = EV_KEY, .code = KEY_LEFTCTRL, .value = 1},
        ctrl_repeat =       {.type = EV_KEY, .code = KEY_LEFTCTRL, .value = 2},
        alt_up =            {.type = EV_KEY, .code = KEY_LEFTALT,  .value = 0},
        alt_down =          {.type = EV_KEY, .code = KEY_LEFTALT,  .value = 1},
        alt_repeat =        {.type = EV_KEY, .code = KEY_LEFTALT,  .value = 2},
        win_up =            {.type = EV_KEY, .code = KEY_LEFTMETA, .value = 0},
        win_down =          {.type = EV_KEY, .code = KEY_LEFTMETA, .value = 1},
        win_repeat =        {.type = EV_KEY, .code = KEY_LEFTMETA, .value = 2}
;
// clang-format on

const struct input_event* const ctrl[] = {&ctrl_up, &ctrl_down, &ctrl_repeat};
const struct input_event* const alt[] = {&alt_up, &alt_down, &alt_repeat};
const struct input_event* const win[] = {&win_up, &win_down, &win_repeat};

int main(int argc, char* argv[]) {
  int is_mapped_key_down = 0, compose_give_up = 0;
  struct input_event input;
  const struct input_event *mapped_down, *mapped_repeat, *mapped_up;

  setbuf(stdin, NULL), setbuf(stdout, NULL);

  while (read_event(&input)) {
    if (input.type != EV_KEY) {
      write_event(&input);
    } else if (input.code == KEY_LEFTMETA) {
      write_event(alt[input.value]);
    } else if (input.code == KEY_LEFTALT) {
      write_event(ctrl[input.value]);
    } else if (input.code == KEY_LEFTCTRL) {
      write_event(win[input.value]);
    } else {
      write_event(&input);
    }
  }
}
