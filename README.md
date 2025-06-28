## Code Charlie
-This project is build for some kind of terminal game. 

-Project will be cross platform but some modules may be exclusive to SBCs (so linux os) because 
there is no GPIO support in regular PCs for example.

-C standard for this projects is 23.

# Project Structure
-Every single file, rather its .h, will include the header "Core.h".
--This file includes:
---Most basic headers for direct use like stdbool, stddef, stdlib etc.
---Necessary headers for debugging like assert, stdio.
---Debugging macros for debug usage.
---Core functions for application developing
--And shouldn't include any custom build files.

-For debugging, there is info, warning and error debugs for debug build.

--Debug build configuration can be made from global header.

## The App
-First of all, I don't know what I'm doing in this project honestly. Just trying out some hardware and 
software ideas that I can't do in windows and regular PCs. The process will show us whats going to happen.
I hope you good days, evenings and nights.

-The app must be run with sudo to make gpio interface work in linux.

## Dependencies
-Compiler I have chosen for this project is Clang so its recommended but its probably compatible with all compilers.
--For Linux and MacOS : simply get ncurses from your package manager. (llvm for apt etc...)
--For Windows, download msys machine and get to mingw64. then enter "pacman -S mingw-w64-clang-x86_64-clang"

-In CMake target_link_libraries there are gpiod, m and ncurses for now.

-To run the core: ncurses must be installed.
--For Linux and MacOS : simply get ncurses from your package manager. (libncurses-dev for apt etc...)
--For Windows, download msys machine and get to mingw64. then enter "pacman -S mingw-w64-x86_64-ncurses"

-To run specific modules: some software and hardware support may be needed like gpiod (libgpiod-dev).