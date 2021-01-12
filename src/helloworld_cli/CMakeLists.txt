# demo static library target
add_library(helloworld
        lib.cpp
        lib.h
        )

target_link_libraries(helloworld
        PUBLIC project_warnings project_options
        PRIVATE project_version
        )

# demo executable target for CI/CD
add_executable(helloworld_cli main.cpp)
target_link_libraries(helloworld_cli PRIVATE helloworld CONAN_PKG::fmt)

# demo unit test target
add_executable(helloworld_tests test_version.cpp)
target_link_libraries(helloworld_tests PRIVATE helloworld catch_main)

# automatically discover tests that are defined in catch based test files.
catch_discover_tests(
        helloworld_tests
        TEST_PREFIX
        "version."
        EXTRA_ARGS
        -s
        --reporter=xml
        --out=version_tests.xml)