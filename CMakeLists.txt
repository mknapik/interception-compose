cmake_minimum_required(VERSION 3.12)
project(compose)

set(CMAKE_C_STANDARD 11)

add_executable(interception-keycounter src/keycounter.cpp src/event.c)
add_executable(interception-keylogger src/keylogger.cpp src/event.c)
add_executable(interception-compose src/compose.c src/event.c)
add_executable(interception-ctrl-win-alt src/ctrl-win-alt.c src/event.c)
add_executable(interception-arrows src/arrows.cpp src/event.c)
add_executable(interception-caps2leftctrl+esc src/caps2leftctrl+esc.c src/event.c)
