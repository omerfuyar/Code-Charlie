# CMAKE_BINARY_DIR : Build file which is in the same directory as main CMakeLists.txt
# CMAKE_SOURCE_DIR : The directory where the top-level CMakeLists.txt file is located
# CMAKE_CURRENT_SOURCE_DIR : The directory of the current CMakeLists.txt file

cmake_minimum_required(VERSION 3.31)

project(Code-Charlie LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/arc)

include_directories(${PROJECT_NAME} PRIVATE 
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME}
    "${CMAKE_SOURCE_DIR}/src/main.c"
)

target_link_libraries(${PROJECT_NAME}
    # kernel32.lib
    # user32.lib
    # gdi32.lib
    # winspool.lib
    # shell32.lib
    # ole32.lib
    # oleaut32.lib
    # uuid.lib
    # comdlg32.lib
    # advapi32.lib
)