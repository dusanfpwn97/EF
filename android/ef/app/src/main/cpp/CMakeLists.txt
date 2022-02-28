cmake_minimum_required(VERSION 3.18.1)
project("ef")

add_library(
        ef
        SHARED
        native-lib.cpp)

find_library(
        log-lib
        log)


target_link_libraries( # Specifies the target library.
        ef

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})