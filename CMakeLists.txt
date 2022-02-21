cmake_minimum_required (VERSION 3.8)
project ("EF")

set(SDL_DIR ${CMAKE_CURRENT_LIST_DIR}/libs/SDL)
set(SDL_INCLUDE_DIR ${SDL_DIR}/include)
set(SDL_LIB_DIR ${SDL_DIR}/lib/x64/Debug)

set(GLAD_DIR ${CMAKE_CURRENT_LIST_DIR}/libs/glad)
set(GLAD_INCLUDE_DIR ${GLAD_DIR}/include)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})

#set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/out/build")

	#find_package(OpenGL REQUIRED)

	target_include_directories(${PROJECT_NAME} PUBLIC ${SDL_INCLUDE_DIR} ${GLAD_INCLUDE_DIR})
	target_link_directories(${PROJECT_NAME} PUBLIC ${SDL_LIB_DIR})
	target_link_libraries(${PROJECT_NAME} SDL2d SDL2maind)

