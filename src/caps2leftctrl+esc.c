/*
 * Forked from
 * https://github.com/vyp/dots/blob/f6ba411/interception-tools/plugins/caps2leftctrl%2Besc.c
 */
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>

#include "event.h"

// clang-format off
const struct input_event
        esc_up          = {.type = EV_KEY, .code = KEY_ESC,      .value = 0},
        ctrl_up         = {.type = EV_KEY, .code = KEY_LEFTCTRL, .value = 0},
        capslock_up     = {.type = EV_KEY, .code = KEY_CAPSLOCK, .value = 0},
        esc_down        = {.type = EV_KEY, .code = KEY_ESC,      .value = 1},
        ctrl_down       = {.type = EV_KEY, .code = KEY_LEFTCTRL, .value = 1},
        capslock_down   = {.type = EV_KEY, .code = KEY_CAPSLOCK, .value = 1},
        esc_repeat      = {.type = EV_KEY, .code = KEY_ESC,      .value = 2},
        ctrl_repeat     = {.type = EV_KEY, .code = KEY_LEFTCTRL, .value = 2},
        capslock_repeat = {.type = EV_KEY, .code = KEY_CAPSLOCK, .value = 2};
// clang-format on

int main(void) {
  int capslock_is_down = 0, esc_give_up = 0;
  struct input_event input;

  setbuf(stdin, NULL), setbuf(stdout, NULL);

  while (read_event(&input)) {
    if (input.type != EV_KEY) {
      write_event(&input);
      continue;
    }

    if (capslock_is_down) {
      if (equal(&input, &capslock_down) || equal(&input, &capslock_repeat)) {
        continue;
      }

      if (equal(&input, &capslock_up)) {
        capslock_is_down = 0;

        if (esc_give_up) {
          esc_give_up = 0;
          write_event(&ctrl_up);
          continue;
        }

        write_event(&esc_down);
        write_event(&esc_up);
        continue;
      }

      if (!esc_give_up && input.value) {
        esc_give_up = 1;
        write_event(&ctrl_down);
      }
    } else {
      if (equal(&input, &capslock_down)) {
        capslock_is_down = 1;
        continue;
      }
    }

    write_event(&input);
  }
}
