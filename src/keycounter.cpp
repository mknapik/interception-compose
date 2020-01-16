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

const auto log_path = "/var/log/interception/keycounter.log";
const auto separator = ',';

int main(int argc, char* argv[]) {
  int is_mapped_key_down = 0, compose_give_up = 0;
  struct input_event input;
  const struct input_event *mapped_down, *mapped_repeat, *mapped_up;

  std::map<const std::string, unsigned long> counter;

  setbuf(stdin, NULL), setbuf(stdout, NULL);

  {
    std::ifstream prev(log_path);
    if (prev.is_open()) {
      for (std::string line; std::getline(prev, line);) {
        const int pos = line.find_first_of(separator);
        std::string count = line.substr(pos + 1), symbol = line.substr(0, pos);
        counter[symbol] = stoi(count);
      }
    }
    prev.close();
  }

  short c = 0;
  while (read_event(&input)) {
    if (input.type == EV_KEY && input.value == 1) {
      const auto code = keyboard_event_mapping[input.code];
      counter[code] = counter[code] + 1;

      if (c++ % 100 == 0) {
        std::ofstream myfile(log_path);
        for (auto it = counter.begin(); it != counter.end(); it++) {
          myfile << it->first << separator << it->second << "\n";
        }
        myfile.flush();
        myfile.close();
      }
    }
    write_event(&input);
  }
}
