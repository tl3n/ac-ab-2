cmake_minimum_required(VERSION 3.27)
project(ac_lab_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(Headers)

add_executable(ac_lab_2 main.cpp
        Headers/PerfectHashing.h
        Sources/PerfectHashing.cpp
        Headers/Menu.h
        Sources/Menu.cpp
        Headers/BinomialHeap.h
        Sources/BinomialHeap.cpp
)
