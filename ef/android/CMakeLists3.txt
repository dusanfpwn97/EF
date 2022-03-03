cmake_minimum_required (VERSION 3.8)
project("ef")

set(EF_SOURCE_DIR ../src)

file(GLOB_RECURSE SOURCES
	${EF_SOURCE_DIR}/*.cpp
	${EF_SOURCE_DIR}/*.c
	)


add_library(
        ef
        SHARED
		${SOURCES}
		src/main/cpp/native-lib.cpp)

find_library(
        log-lib
        log)


target_link_libraries( # Specifies the target library.
        ef

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})