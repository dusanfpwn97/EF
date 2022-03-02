cmake_minimum_required (VERSION 3.8)
project ("ef")
# DEFINITIONS
add_compile_definitions(EF_PLATFORM_WINDOWS EF_BUILD_DLL)
set(EF_PLATFORM_WINDOWS 1)
# SDL
set(SDL_DIR ${CMAKE_CURRENT_LIST_DIR}/libs/SDL)

if(EF_PLATFORM_WINDOWS)
	set(SDL_LIB_DIR ${SDL_DIR}/lib/windows)
else()
	set(SDL_LIB_DIR ${SDL_DIR}/lib/android/arm64-v8a)
endif()
# GLAD
set(GLAD_DIR ${CMAKE_CURRENT_LIST_DIR}/libs/glad)
# VARS
file(GLOB_RECURSE SOURCES
	${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
	${PROJECT_SOURCE_DIR}/src/*.c
	${GLAD_DIR}/src/glad.c
)
file(GLOB_RECURSE INCLUDE_DIRS
    ${SDL_DIR}/include
    ${GLAD_DIR}/include
)
# put generated files into the same directory as exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(ef SHARED ${SOURCES} )

target_include_directories(${PROJECT_NAME} PUBLIC 
	#${INCLUDE_DIRS}
	${SDL_DIR}/include
    ${GLAD_DIR}/include
)

target_link_directories(${PROJECT_NAME} PUBLIC 
	${SDL_LIB_DIR}
)
target_link_libraries(${PROJECT_NAME}
	SDL2
	SDL2main
)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	#COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL_LIB_DIR}/SDL2.dll ${CMAKE_CURRENT_LIST_DIR}/out/build/x64-Debug/
	COMMENT "Copying dlls..."
)