# CMAKE_BINARY_DIR : Build file which is in the same directory as main CMakeLists.txt
# CMAKE_SOURCE_DIR : The directory where the top-level CMakeLists.txt file is located
# CMAKE_CURRENT_SOURCE_DIR : The directory of the current CMakeLists.txt file

# Cmake project setup
cmake_minimum_required(VERSION 3.25)

project(Code-Charlie C)

# Prefer clang if it is available
find_program(CLANG_EXECUTABLE clang)
if(CLANG_EXECUTABLE)
    set(CMAKE_C_COMPILER ${CLANG_EXECUTABLE})
endif()

message(STATUS "Using C compiler: ${CMAKE_C_COMPILER}")

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED OFF)

set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2 -Wall -Wextra")

# Build directory setup
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/arc)

# Include directories setup
include_directories(${PROJECT_NAME} 
    ${CMAKE_SOURCE_DIR}/Core/include

    ${CMAKE_SOURCE_DIR}/App/include
)

# Source files setup
file(GLOB_RECURSE PROJECT_SOURCE
    ${CMAKE_SOURCE_DIR}/Core/src/*.c
    ${CMAKE_SOURCE_DIR}/Core/src/**/*.c

    ${CMAKE_SOURCE_DIR}/App/src/*.c
    ${CMAKE_SOURCE_DIR}/App/src/**/*.c
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE}
)

target_link_libraries(${PROJECT_NAME}
    gpiod
    m
    ncurses
)
