#include <linux/input.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>

#include "event.h"
#include "keyboard-event-mapping.hpp"

int main(int argc, char* argv[]) {
  int is_mapped_key_down = 0, compose_give_up = 0;
  struct input_event input;
  const struct input_event *mapped_down, *mapped_repeat, *mapped_up;

  auto counter = std::map<std::string, unsigned long>();

  setbuf(stdin, NULL), setbuf(stdout, NULL);

  std::ifstream prev("/var/log/interception-keycoutner.log");
  if (prev.is_open()) {
    for (std::string line; std::getline(prev, line);) {
      int pos = line.find_first_of(':');
      std::string count = line.substr(pos + 1), symbol = line.substr(0, pos);
      counter[symbol] = stoi(count);
    }
  }

  short c = 0;
  while (read_event(&input)) {
    if (input.type == EV_KEY && input.value == 1) {

      counter[input.code] = counter[input.code] + 1;

      if (c++ % 10 == 0) {
        std::ofstream myfile("/var/log/interception-keycoutner.log");
        for (auto it = counter.begin(); it != counter.end(); it++) {
          myfile << it->first << ":" << it->second << "\n";
        }
        myfile.flush();
        myfile.close();
      }
    }
    write_event(&input);
  }
}
