# Code Charlie

* This project started to explore SBCs and their capabilities.
* But later on I decided to make it a cross platform terminal based game engine like application.

## Overview

* Project is using **C23** standard
* Cross-platform support for **Linux**, **macOS**, **Windows**
* Uses **Clang** as the preferred compiler
* **curses** libraries for terminal rendering
* There are some Linux-only hardware modules (like GPIO via `gpiod`)

## Project Structure

```text
ProjectRoot/
├── App/                    # App (Game) layer
    ├──include/             
    └──src/
├── Core/                   # Core (Engine) layer
    ├──include/
    └──src/
├── CMakeLists.txt          # Build configuration
└── build/                  # CMake build output
```

* Core sources can not include any of the App headers.
* All header files (so indirectly source files) must include a central `Core.h` header.
* That file includes:
  * Common standard headers
  * Debugging macros
  * Core functions to build the application.
* For Linux modules involving GPIO, the application must be run with `sudo`.

## Dependencies

### Build System: `CMake`

#### Linux

```bash
# For Debian
sudo apt install cmake
```

#### MacOS

```bash
# For Homebrew
brew install cmake
```

#### Windows

1. Download and install CMake from the [official site](https://cmake.org/download/) in binary distributions section.

### Recommended Compiler: `Clang` 

#### Linux

```bash
# For Debian
sudo apt install clang
```

#### MacOS

```bash
# For Homebrew
brew install llvm
# Ensure Clang is added to your PATH:
echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zprofile
```

#### Windows

1. Download and install LLVM from the [official site](https://releases.llvm.org/download.html)
2. Enable the option "Add LLVM to system PATH" during installation

### HTTP Client: `libcurl`

#### Linux

```bash
# For Debian
sudo apt install libcurl4-openssl-dev
```

#### MacOS

```bash
# For Homebrew
brew install curl            
```

#### Windows

```PowerShell
# Install vcpkg if not already done
git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
C:\vcpkg\bootstrap-vcpkg.bat
C:\vcpkg\vcpkg integrate install

# Install curl
C:\vcpkg\vcpkg install curl:x64-windows
```

### Terminal Rendering: `Curses`

#### Linux: `ncurses`

```bash
# For Debian
sudo apt install libncurses-dev  
```

#### MacOS: `ncurses`

```bash
# For Homebrew
brew install ncurses            
```

#### Windows: `pdcurses`

```PowerShell
# Install vcpkg if not already done
git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
C:\vcpkg\bootstrap-vcpkg.bat
C:\vcpkg\vcpkg integrate install

# Install pdcurses
C:\vcpkg\vcpkg install pdcurses:x64-windows
```

### Optional Linux-only GPIO Support For SBCs: `gpiod`

```bash
# For Debian
sudo apt install libgpiod-dev
```

## Building the Project

### Linux

```bash
# Install Ninja (Debian)
sudo apt install ninja-build

# Build
mkdir build && cd build
cmake .. -G Ninja -DCMAKE_C_COMPILER=clang
cmake --build .
```

### MacOS

```bash
# Install Ninja (Homebrew)
brew install ninja

# Build
mkdir build && cd build
cmake .. -G Ninja -DCMAKE_C_COMPILER=clang
cmake --build .
```

### Windows

1. Install Ninja (build tool)

```PowerShell
# Install Ninja using winget
winget install -e --id Ninja-build.Ninja

# Build
mkdir build && cd build
cmake .. -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_C_COMPILER=clang
# Or you can change the path to your vcpkg installation
cmake --build .
```

## Notes
* To avoid compiler errors in code editors in Windows, add include path to intellisense `C:/vcpkg/installed/x64-windows/include` or wherever your vcpkg is installed.