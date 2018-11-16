cmake_minimum_required(VERSION 3.12)
project(hyper C)

set(CMAKE_C_STANDARD 11)

add_executable(hyper src/hyper.c src/event.c)
add_executable(caps2leftctrl+esc src/caps2leftctrl+esc.c src/event.c)
