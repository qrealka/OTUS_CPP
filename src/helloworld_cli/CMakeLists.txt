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

# Install section
install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
