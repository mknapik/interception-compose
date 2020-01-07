#include <linux/input.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

#include "event.h"

int main(int argc, char* argv[]) {
  int is_mapped_key_down = 0, compose_give_up = 0;
  struct input_event input;
  const struct input_event *mapped_down, *mapped_repeat, *mapped_up;

  setbuf(stdin, NULL), setbuf(stdout, NULL);

  std::ofstream myfile("/tmp/interception-keylogger.log", std::ios_base::app);

  while (read_event(&input)) {
    if (input.type == EV_KEY && input.value == 1 && myfile.is_open()) {
      myfile << input.code << " ";
      myfile.flush();
    }
    write_event(&input);
  }
}
