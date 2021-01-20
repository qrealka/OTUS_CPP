# OTUS C++ Course

![CMake](https://github.com/qrealka/OTUS_CPP/workflows/CMake/badge.svg)

[![Build Status](https://travis-ci.com/qrealka/OTUS_CPP.svg?branch=main)](https://travis-ci.com/qrealka/OTUS_CPP)

OTUS Course C++ for professionals. The project layout based on Jason Turner [cpp_starter_project](https://github.com/lefticus/cpp_starter_project).

## Necessary Dependencies
1. A C++ compiler that supports C++17.
   See [cppreference.com](https://en.cppreference.com/w/cpp/compiler_support)
   to see which features are supported by each compiler.
   The following compilers should work:
   
   * [gcc 7+](https://gcc.gnu.org/)
     <details>
     <summary>Install command</summary>
   
      - Debian/Ubuntu:
   
           sudo apt install build-essential
   
      - MacOS:
   
           brew install gcc
     </details>   

   * [clang 6+](https://clang.llvm.org/)
     <details>
     <summary>Install command</summary>
   
      - Debian/Ubuntu:
   
           bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"
   
      - MacOS:
   
           brew install llvm
     </details>

2. [Conan](https://conan.io/)
   <details>
   <summary>Install Command</summary>

   - Via pip - https://docs.conan.io/en/latest/installation.html#install-with-pip-recommended

        pip install --user conan

   - MacOS:

        brew install conan

   </details>

3. [CMake 3.15+](https://cmake.org/)
   <details>
   <summary>Install Command</summary>

   - Debian/Ubuntu:

     	sudo apt-get install cmake

   - MacOS:

     	brew install cmake

   </details>

## Build Instructions

### Build directory
All homework projects have a protection to prevent build from source code directory. So first of all nake a build directory:
```
mkdir build
```
### Specify the compiler using environment variables

By default (if you don't set environment variables `CC` and `CXX`), the system default compiler will be used.

Conan and CMake use the environment variables CC and CXX to decide which compiler to use. So to avoid the conflict issues only specify the compilers using these variables.

CMake will detect which compiler was used to build each of the Conan targets. If you build all of your Conan targets with one compiler, and then build your CMake targets with a different compiler, the project may fail to build.

<details>
<summary>Commands for setting the compilers </summary>

- Debian/Ubuntu/MacOS:

  Set your desired compiler (`clang`, `gcc`, etc):

   - Temporarily (only for the current shell)

     Run one of the followings in the terminal:

      - clang

        	CC=clang CXX=clang++

      - gcc

        	CC=gcc CXX=g++

   - Permanent:

     Open `~/.bashrc` using your text editor:

     	gedit ~/.bashrc

     Add `CC` and `CXX` to point to the compilers:

     	export CC=clang
     	export CXX=clang++

     Save and close the file.

- Temporarily (only for the current shell):

  		$Env:CC="clang.exe"
  		$Env:CXX="clang++.exe"

</details>

### Build
Once you have selected all the options you would like to use, you can build the 
project (all targets):

    cmake --build ./build

## Troubleshooting

### Cmake build generation doesn't work
If you see the following error message:
```bash
CMake Error at cmake/PreventInSourceBuilds.cmake:14 (message):
Quitting configuration
```
That means you are trying to build [in the source directory](https://github.com/qrealka/OTUS_CPP/blob/main/cmake/PreventInSourceBuilds.cmake#L12). Just follow the Build Instructions above.

### Update Conan
Many problems that users have can be resolved by updating Conan, so if you are
having any trouble with this project, you should start by doing that.

To update conan:

    $ pip install --user --upgrade conan 

You may need to use `pip3` instead of `pip` in this command, depending on your
platform.

### Clear Conan cache
If you continue to have trouble with your Conan dependencies, you can try
clearing your Conan cache:

    $ conan remove -f '*'

The next time you run `cmake` or `cmake --build`, your Conan dependencies will
be rebuilt. If you aren't using your system's default compiler, don't forget to
set the CC, CXX, CMAKE_C_COMPILER, and CMAKE_CXX_COMPILER variables, as
described in the 'Build using an alternate compiler' section above.

### Identifying misconfiguration of Conan dependencies

If you have a dependency 'A' that requires a specific version of another
dependency 'B', and your project is trying to use the wrong version of
dependency 'B', Conan will produce warnings about this configuration error
when you run CMake. These warnings can easily get lost between a couple
hundred or thousand lines of output, depending on the size of your project.

If your project has a Conan configuration error, you can use `conan info` to
find it. `conan info` displays information about the dependency graph of your
project, with colorized output in some terminals.

    $ cd build
    $ conan info .

In my terminal, the first couple lines of `conan info`'s output show all of the
project's configuration warnings in a bright yellow font.

For example, the package `spdlog/1.5.0` depends on the package `fmt/6.1.2`.
If you were to modify the file `cmake/Conan.cmake` so that it requires an
earlier version of `fmt`, such as `fmt/6.0.0`, and then run:

    $ conan remove -f '*'       # clear Conan cache
    $ rm -rf build              # clear previous CMake build
    $ mkdir build && cd build
    $ cmake ..                  # rebuild Conan dependencies
    $ conan info .

...the first line of output would be a warning that `spdlog` needs a more recent
version of `fmt`.

## Testing
See [Catch2 tutorial](https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md)

## Homeworks
See [another README.MD](https://github.com/qrealka/OTUS_CPP/tree/main/src)


