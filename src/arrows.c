#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "event.h"

// clang-format off
const struct input_event
        h_up =           {.type = EV_KEY, .code = KEY_H,       .value = 0},
        h_down =         {.type = EV_KEY, .code = KEY_H,       .value = 1},
        h_repeat =       {.type = EV_KEY, .code = KEY_H,       .value = 2},
        j_up =           {.type = EV_KEY, .code = KEY_J,       .value = 0},
        j_down =         {.type = EV_KEY, .code = KEY_J,       .value = 1},
        j_repeat =       {.type = EV_KEY, .code = KEY_J,       .value = 2},
        k_up =           {.type = EV_KEY, .code = KEY_K,       .value = 0},
        k_down =         {.type = EV_KEY, .code = KEY_K,       .value = 1},
        k_repeat =       {.type = EV_KEY, .code = KEY_K,       .value = 2},
        l_up =           {.type = EV_KEY, .code = KEY_L,       .value = 0},
        l_down =         {.type = EV_KEY, .code = KEY_L,       .value = 1},
        l_repeat =       {.type = EV_KEY, .code = KEY_L,       .value = 2},

        a_up =           {.type = EV_KEY, .code = KEY_U,       .value = 0},
        a_down =         {.type = EV_KEY, .code = KEY_U,       .value = 1},
        a_repeat =       {.type = EV_KEY, .code = KEY_U,       .value = 2},
        s_up =           {.type = EV_KEY, .code = KEY_I,       .value = 0},
        s_down =         {.type = EV_KEY, .code = KEY_I,       .value = 1},
        s_repeat =       {.type = EV_KEY, .code = KEY_I,       .value = 2},
        d_up =           {.type = EV_KEY, .code = KEY_O,       .value = 0},
        d_down =         {.type = EV_KEY, .code = KEY_O,       .value = 1},
        d_repeat =       {.type = EV_KEY, .code = KEY_O,       .value = 2},
        f_up =           {.type = EV_KEY, .code = KEY_P,       .value = 0},
        f_down =         {.type = EV_KEY, .code = KEY_P,       .value = 1},
        f_repeat =       {.type = EV_KEY, .code = KEY_P,       .value = 2},

        home_up =           {.type = EV_KEY, .code = KEY_HOME,       .value = 0},
        home_down =         {.type = EV_KEY, .code = KEY_HOME,       .value = 1},
        home_repeat =       {.type = EV_KEY, .code = KEY_HOME,       .value = 2},
        pgup_up =           {.type = EV_KEY, .code = KEY_PAGEDOWN,       .value = 0},
        pgup_down =         {.type = EV_KEY, .code = KEY_PAGEDOWN,       .value = 1},
        pgup_repeat =       {.type = EV_KEY, .code = KEY_PAGEDOWN,       .value = 2},
        pgdw_up =           {.type = EV_KEY, .code = KEY_PAGEUP,       .value = 0},
        pgdw_down =         {.type = EV_KEY, .code = KEY_PAGEUP,       .value = 1},
        pgdw_repeat =       {.type = EV_KEY, .code = KEY_PAGEUP,       .value = 2},
        end_up =           {.type = EV_KEY, .code = KEY_END,       .value = 0},
        end_down =         {.type = EV_KEY, .code = KEY_END,       .value = 1},
        end_repeat =       {.type = EV_KEY, .code = KEY_END,       .value = 2},
        left_up =           {.type = EV_KEY, .code = KEY_LEFT,       .value = 0},
        left_down =         {.type = EV_KEY, .code = KEY_LEFT,       .value = 1},
        left_repeat =       {.type = EV_KEY, .code = KEY_LEFT,       .value = 2},
        down_up =           {.type = EV_KEY, .code = KEY_DOWN,       .value = 0},
        down_down =         {.type = EV_KEY, .code = KEY_DOWN,       .value = 1},
        down_repeat =       {.type = EV_KEY, .code = KEY_DOWN,       .value = 2},
        up_up =           {.type = EV_KEY, .code = KEY_UP,       .value = 0},
        up_down =         {.type = EV_KEY, .code = KEY_UP,       .value = 1},
        up_repeat =       {.type = EV_KEY, .code = KEY_UP,       .value = 2},
        right_up =           {.type = EV_KEY, .code = KEY_RIGHT,       .value = 0},
        right_down =         {.type = EV_KEY, .code = KEY_RIGHT,       .value = 1},
        right_repeat =       {.type = EV_KEY, .code = KEY_RIGHT,       .value = 2},
        win_up =           {.type = EV_KEY, .code = KEY_LEFTMETA, .value = 0},
        win_down =         {.type = EV_KEY, .code = KEY_LEFTMETA, .value = 1},
        win_repeat =       {.type = EV_KEY, .code = KEY_LEFTMETA, .value = 2}
;
// clang-format on

const struct input_event* const h[] = {&left_up, &left_down, &left_repeat};
const struct input_event* const j[] = {&down_up, &down_down, &down_repeat};
const struct input_event* const k[] = {&up_up, &up_down, &up_repeat};
const struct input_event* const l[] = {&right_up, &right_down, &right_repeat};
const struct input_event* const a[] = {&home_up, &home_down, &home_repeat};
const struct input_event* const s[] = {&pgdw_up, &pgdw_down, &pgdw_repeat};
const struct input_event* const d[] = {&pgup_up, &pgup_down, &pgup_repeat};
const struct input_event* const f[] = {&end_up, &end_down, &end_repeat};

int main(int argc, char* argv[]) {
  short mod_is_down = 0;
  struct input_event input;

  setbuf(stdin, NULL), setbuf(stdout, NULL);

  while (read_event(&input)) {
    if (input.type != EV_KEY) {
      write_event(&input);
    } else if (mod_is_down) {
      if (input.code == KEY_H || input.code == KEY_J || input.code == KEY_K ||
          input.code == KEY_L || input.code == a_up.code || input.code == s_up.code || input.code == d_up.code ||
          input.code == f_up.code) {
        write_event(&win_up);

        switch (input.code) {
          case KEY_H:
            write_event(h[input.value]);
            break;
          case KEY_J:
            write_event(j[input.value]);
            break;
          case KEY_K:
            write_event(k[input.value]);
            break;
          case KEY_L:
            write_event(l[input.value]);
            break;
          case KEY_U:
            write_event(a[input.value]);
            break;
          case KEY_I:
            write_event(s[input.value]);
            break;
          case KEY_O:
            write_event(d[input.value]);
            break;
          case KEY_P:
            write_event(f[input.value]);
            break;
        }
        write_event(&win_down);
      } else if (equal(&input, &win_up)) {
        mod_is_down = 0;
        write_event(&win_up);
      } else {
        write_event(&input);
      }
    } else if (equal(&input, &win_down)) {
      mod_is_down = 1;
      write_event(&input);
    } else {
      write_event(&input);
    }
  }
}
