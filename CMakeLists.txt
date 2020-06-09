cmake_minimum_required(VERSION 3.16)
project(mysh C)

set(CMAKE_C_STANDARD 11)

add_executable(mysh main.c utils.c)