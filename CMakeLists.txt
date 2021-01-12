# Minimum version of cmake
cmake_minimum_required(VERSION 3.17)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(TRAVIS_BUILD_NUMBER $ENV{TRAVIS_BUILD_NUMBER})
else()
    # TODO: git rev-parse --short=10 HEAD
    set(TRAVIS_BUILD_NUMBER 1)
endif()

project(OTUS_CPP
        VERSION 0.0.${TRAVIS_BUILD_NUMBER}
        LANGUAGES CXX)

include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
# Individual compile features are not provided for C++17 or later.
target_compile_features(project_options INTERFACE cxx_std_17)

# Provide version info for c++ targets
configure_file(version.h.in version.h)
add_library(project_version INTERFACE)
# Cmake 3.19+ allow to create INTERFACE library target with source code
# Clion bundled version is 3.17
target_include_directories(project_version INTERFACE ${CMAKE_BINARY_DIR})

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
    if(ENABLE_BUILD_WITH_TIME_TRACE)
        add_compile_definitions(project_options INTERFACE -ftime-trace)
    endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" ON)

# Very basic PCH settings
# TODO: configure it
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if(ENABLE_PCH)
    # This sets a global PCH parameter, each project will build its own PCH, which is a good idea if any #define's change
    #
    # consider breaking this out per project as necessary
    target_precompile_headers(
            project_options
            INTERFACE
            <vector>
            <string>
            <map>
            <utility>)
endif()

# Set up some extra Conan dependencies based on our needs before loading Conan
set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

include(cmake/Conan.cmake)
run_conan()

# Catch2 main
enable_testing()
add_subdirectory(test)

# homework
add_subdirectory(src)

