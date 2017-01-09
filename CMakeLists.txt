cmake_minimum_required(VERSION 3.5)
project(jnp6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp monster.cc monster.h citizen.cc citizen.h smalltown.cc smalltown.h)
add_executable(smaltown ${SOURCE_FILES})