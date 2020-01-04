cmake_minimum_required(VERSION 3.12)
project(compose C)

set(CMAKE_C_STANDARD 11)

add_executable(compose src/compose.c src/event.c)
add_executable(ctrl-win-alt src/ctrl-win-alt.c src/event.c)
add_executable(arrows src/arrows.c src/event.c)
add_executable(caps2leftctrl+esc src/caps2leftctrl+esc.c src/event.c)
