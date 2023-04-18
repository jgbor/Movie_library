cmake_minimum_required(VERSION 3.19)
project(hazifeladat)

set(CMAKE_CXX_STANDARD 14)

add_executable(hazifeladat
        main.cpp
        memtrace.cpp
        memtrace.h
        gtest_lite.h
        string5.cpp
        string5.h
        film.cpp
        film.h
        lista.cpp
        lista.h
        csaladi.cpp
        csaladi.h
        akcio.cpp
        akcio.h
        dokumentum.cpp
        dokumentum.h
        teszt-menu.cpp
        teszt-menu.h)

add_definitions(-DMEMTRACE)