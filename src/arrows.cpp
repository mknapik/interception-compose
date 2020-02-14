#include <linux/input.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "event.h"

const struct input_event
    backspace_up = {.type = EV_KEY, .code = KEY_BACKSPACE, .value = 0},
    backspace_down = {.type = EV_KEY, .code = KEY_BACKSPACE, .value = 1},
    backspace_repeat = {.type = EV_KEY, .code = KEY_BACKSPACE, .value = 2},
    delete_up = {.type = EV_KEY, .code = KEY_DELETE, .value = 0},
    delete_down = {.type = EV_KEY, .code = KEY_DELETE, .value = 1},
    delete_repeat = {.type = EV_KEY, .code = KEY_DELETE, .value = 2},
    home_up = {.type = EV_KEY, .code = KEY_HOME, .value = 0},
    home_down = {.type = EV_KEY, .code = KEY_HOME, .value = 1},
    home_repeat = {.type = EV_KEY, .code = KEY_HOME, .value = 2},
    pgdw_up = {.type = EV_KEY, .code = KEY_PAGEDOWN, .value = 0},
    pgdw_down = {.type = EV_KEY, .code = KEY_PAGEDOWN, .value = 1},
    pgdw_repeat = {.type = EV_KEY, .code = KEY_PAGEDOWN, .value = 2},
    pgup_up = {.type = EV_KEY, .code = KEY_PAGEUP, .value = 0},
    pgup_down = {.type = EV_KEY, .code = KEY_PAGEUP, .value = 1},
    pgup_repeat = {.type = EV_KEY, .code = KEY_PAGEUP, .value = 2},
    end_up = {.type = EV_KEY, .code = KEY_END, .value = 0},
    end_down = {.type = EV_KEY, .code = KEY_END, .value = 1},
    end_repeat = {.type = EV_KEY, .code = KEY_END, .value = 2},
    left_up = {.type = EV_KEY, .code = KEY_LEFT, .value = 0},
    left_down = {.type = EV_KEY, .code = KEY_LEFT, .value = 1},
    left_repeat = {.type = EV_KEY, .code = KEY_LEFT, .value = 2},
    down_up = {.type = EV_KEY, .code = KEY_DOWN, .value = 0},
    down_down = {.type = EV_KEY, .code = KEY_DOWN, .value = 1},
    down_repeat = {.type = EV_KEY, .code = KEY_DOWN, .value = 2},
    up_up = {.type = EV_KEY, .code = KEY_UP, .value = 0},
    up_down = {.type = EV_KEY, .code = KEY_UP, .value = 1},
    up_repeat = {.type = EV_KEY, .code = KEY_UP, .value = 2},
    right_up = {.type = EV_KEY, .code = KEY_RIGHT, .value = 0},
    right_down = {.type = EV_KEY, .code = KEY_RIGHT, .value = 1},
    right_repeat = {.type = EV_KEY, .code = KEY_RIGHT, .value = 2},
    win_up = {.type = EV_KEY, .code = KEY_LEFTMETA, .value = 0},
    win_down = {.type = EV_KEY, .code = KEY_LEFTMETA, .value = 1},
    win_repeat = {.type = EV_KEY, .code = KEY_LEFTMETA, .value = 2};

const struct input_event* const left[] = {&left_up, &left_down, &left_repeat};
const struct input_event* const down[] = {&down_up, &down_down, &down_repeat};
const struct input_event* const up[] = {&up_up, &up_down, &up_repeat};
const struct input_event* const right[] = {&right_up, &right_down,
                                           &right_repeat};

const struct input_event* const home[] = {&home_up, &home_down, &home_repeat};
const struct input_event* const end[] = {&end_up, &end_down, &end_repeat};
const struct input_event* const pgdw[] = {&pgdw_up, &pgdw_down, &pgdw_repeat};
const struct input_event* const pgup[] = {&pgup_up, &pgup_down, &pgup_repeat};

const struct input_event* const backspace[] = {&backspace_up, &backspace_down, &backspace_repeat};
const struct input_event* const deletekey[] = {&delete_up, &delete_down, &delete_repeat};

const __u16 left_code = KEY_J;
const __u16 down_code = KEY_K;
const __u16 up_code = KEY_I;
const __u16 right_code = KEY_L;

const __u16 home_code = KEY_M;
const __u16 end_code = KEY_COMMA;
const __u16 pgdw_code = KEY_U;
const __u16 pgup_code = KEY_O;

const __u16 backspace_code = KEY_H;
const __u16 delete_code = KEY_SEMICOLON;


bool is_mapped(__u16 code) {
  switch (code) {
    case left_code:
    case down_code:
    case right_code:
    case up_code:
    case home_code:
    case end_code:
    case pgup_code:
    case pgdw_code:
    case backspace_code:
    case delete_code:
      return true;
    default:
      return false;
  }
}

short left_is_down = 0;
short down_is_down = 0;
short right_is_down = 0;
short up_is_down = 0;
short home_is_down = 0;
short end_is_down = 0;
short pgup_is_down = 0;
short pgdw_is_down = 0;
short backspace_is_down = 0;
short delete_is_down = 0;

const struct input_event* const map_input(const __u16 code, const __s32 value) {
  switch (code) {
    case left_code:
      left_is_down = value == 0 ? 0 : 1;
      return left[value];
    case down_code:
      down_is_down = value == 0 ? 0 : 1;
      return down[value];
    case right_code:
      right_is_down = value == 0 ? 0 : 1;
      return right[value];
    case up_code:
      up_is_down = value == 0 ? 0 : 1;
      return up[value];
    case home_code:
      home_is_down = value == 0 ? 0 : 1;
      return home[value];
    case end_code:
      end_is_down = value == 0 ? 0 : 1;
      return end[value];
    case pgup_code:
      pgup_is_down = value == 0 ? 0 : 1;
      return pgup[value];
    case pgdw_code:
      pgdw_is_down = value == 0 ? 0 : 1;
      return pgdw[value];
    case backspace_code:
      backspace_is_down = value == 0 ? 0 : 1;
      return backspace[value];
    case delete_code:
      delete_is_down = value == 0 ? 0 : 1;
      return deletekey[value];
    default:
      return nullptr;
  }
}

int main(int argc, char* argv[]) {
  short mod_is_down = 0;
  struct input_event input;

  setbuf(stdin, NULL), setbuf(stdout, NULL);

  while (read_event(&input)) {
    if (input.type != EV_KEY) {
      write_event(&input);
    } else if (mod_is_down) {
      if (is_mapped(input.code)) {
        write_event(&win_up);
        auto result = map_input(input.code, input.value);

        if (result != nullptr) {
          write_event(result);
        }

        if (!(up_is_down || down_is_down || left_is_down || right_is_down ||
              home_is_down || end_is_down || pgup_is_down || pgdw_is_down ||
              backspace_is_down || delete_is_down)) {
          write_event(&win_down);
        }
      } else if (equal(&input, &win_up)) {
        mod_is_down = 0;

        if (up_is_down) {
          up_is_down = 0;
          write_event(&up_up);
        }
        if (down_is_down) {
          down_is_down = 0;
          write_event(&down_up);
        }
        if (left_is_down) {
          left_is_down = 0;
          write_event(&left_up);
        }
        if (right_is_down) {
          right_is_down = 0;
          write_event(&right_up);
        }
        if (home_is_down) {
          home_is_down = 0;
          write_event(&home_up);
        }
        if (end_is_down) {
          end_is_down = 0;
          write_event(&end_up);
        }
        if (pgup_is_down) {
          pgup_is_down = 0;
          write_event(&pgup_up);
        }
        if (pgdw_is_down) {
          pgdw_is_down = 0;
          write_event(&pgdw_up);
        }
        if (backspace_is_down) {
          backspace_is_down = 0;
          write_event(&backspace_up);
        }
        if (delete_is_down) {
          delete_is_down = 0;
          write_event(&delete_up);
        }
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
