# CMAKE_BINARY_DIR : Build file which is in the same directory as main CMakeLists.txt
# CMAKE_SOURCE_DIR : The directory where the top-level CMakeLists.txt file is located
# CMAKE_CURRENT_SOURCE_DIR : The directory of the current CMakeLists.txt file

cmake_minimum_required(VERSION 4.0)

project(Code-Charlie C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/arc)

include_directories(${PROJECT_NAME} 
    ${CMAKE_SOURCE_DIR}/include
)

file(GLOB_RECURSE PROJECT_SOURCE
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/**/*.c
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE}
)

target_link_libraries(${PROJECT_NAME}
    gpiod
)
