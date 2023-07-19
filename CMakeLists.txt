cmake_minimum_required(VERSION 3.24)
project(Json_Interpreter)

set(CMAKE_CXX_STANDARD 14)

add_executable(Json_Interpreter
        main.cpp json.h json.cpp Parse.h Parse.cpp)
