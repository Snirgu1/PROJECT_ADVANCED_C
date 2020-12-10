cmake_minimum_required(VERSION 3.17)
project(PROJECT_ADVANCED_C C)

set(CMAKE_C_STANDARD 90)

add_executable(PROJECT_ADVANCED_C main.c DataBase.c DataBase.h FilesOp.c FilesOp.h Reconstraction.c Reconstraction.h Other.c Other.h main_commands.c main_commands.h)