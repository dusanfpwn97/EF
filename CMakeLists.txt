cmake_minimum_required (VERSION 3.8)
project ("ef")

set(SDL_DIR ${CMAKE_CURRENT_LIST_DIR}/libs/SDL)
set(SDL_INCLUDE_DIR ${SDL_DIR}/include)
set(SDL_LIB_DIR ${SDL_DIR}/lib/Debug)

set(GLAD_DIR ${CMAKE_CURRENT_LIST_DIR}/libs/glad)
set(GLAD_INCLUDE_DIR ${GLAD_DIR}/include)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.c)

add_library(ef SHARED ${SOURCES})
#set_target_properties(ef PROPERTIES
#  SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src"
#)
add_compile_definitions(EF_PLATFORM_WINDOWS EF_BUILD_DLL)
#target_compile_definitions(ef PUBLIC EF_BUILD_DLL=0)

add_subdirectory(${GLAD_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC 
	${SDL_INCLUDE_DIR}
	${GLAD_INCLUDE_DIR}
	#${CMAKE_CURRENT_LIST_DIR}/src
)
target_link_directories(${PROJECT_NAME} PUBLIC 
	${SDL_LIB_DIR}
)
target_link_libraries(${PROJECT_NAME}
	SDL2d
	SDL2maind
	glad
)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL_LIB_DIR}/SDL2d.dll ${CMAKE_CURRENT_LIST_DIR}/out/build/x64-Debug/
	COMMENT "Copying dlls..."
)