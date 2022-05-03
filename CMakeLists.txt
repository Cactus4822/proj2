cmake_minimum_required(VERSION 3.21)
project(proj2 C)

set(CMAKE_C_STANDARD 11)

add_executable(proj2 main.c twitter_create.c twitter_create.h)
