# CMAKE_BINARY_DIR : Build file which is in the same directory as main CMakeLists.txt
# CMAKE_SOURCE_DIR : The directory where the top-level CMakeLists.txt file is located
# CMAKE_CURRENT_SOURCE_DIR : The directory of the current CMakeLists.txt file

cmake_minimum_required(VERSION 3.25)

# Cmake project setup
project(Code-Charlie C)

# Set compiler flags and standard.
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED OFF)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Prefer clang if it is available
#find_program(CLANG_EXECUTABLE clang)
#if(CLANG_EXECUTABLE)
#    set(CMAKE_C_COMPILER ${CLANG_EXECUTABLE})
#endif()

message(STATUS "Using C compiler: ${CMAKE_C_COMPILER}")

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2 -Wall -Wextra -Wshadow -Wnull-dereference -Wunused-result -fstack-protector-strong -fno-common")

# -fsanitize=undefined -fsanitize=address

# Build directory setup
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/arc)

# Define include directories
include_directories(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/Core/include
    ${CMAKE_SOURCE_DIR}/App/include
)

# Source files setup
file(GLOB_RECURSE PROJECT_SOURCE
    ${CMAKE_SOURCE_DIR}/Core/src/*.c
    ${CMAKE_SOURCE_DIR}/App/src/*.c
)

# Define the executable target
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE}
)

# Find and link libraries
if(UNIX)
    find_package(CURL REQUIRED)
    find_package(Curses REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CURSES_LIBRARIES} gpiod m CURL::libcurl)
elseif(WIN32)
    find_package(unofficial-pdcurses CONFIG REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::pdcurses::pdcurses)
endif()
