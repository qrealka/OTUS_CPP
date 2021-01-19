# OTUS_CPP

![CMake](https://github.com/qrealka/OTUS_CPP/workflows/CMake/badge.svg)

[![Build Status](https://travis-ci.com/qrealka/OTUS_CPP.svg?branch=main)](https://travis-ci.com/qrealka/OTUS_CPP)

OTUS Course C++ for professionals. The project layout based on Jason Turner [cpp_starter_project](https://github.com/lefticus/cpp_starter_project).


# Homeworks
All homework projects have a protection to prevent build from source code directory. Example bash command to build a solution:
```bash
  mkdir build
  cd build
  cmake ../
  cmake --build . 
  ctest 
```
1. Build, test, deploy
    * [Helloworld](https://github.com/qrealka/OTUS_CPP/blob/main/src/CMakeLists.txt#L5) [ ![Download](https://api.bintray.com/packages/qrealka/OTUS/helloworld/images/download.svg) ](https://bintray.com/qrealka/OTUS/helloworld/_latestVersion)
    * IP filter
