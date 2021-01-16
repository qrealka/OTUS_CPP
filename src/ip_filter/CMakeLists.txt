# ipv4 homework targets
add_library(ipv4
        ipv4.h
        ipv4.cpp
        )

target_link_libraries(ipv4
        PUBLIC
            project_warnings
            project_options
            CONAN_PKG::fmt
        PRIVATE
            CONAN_PKG::boost
        )

add_executable(ip_filter ip_filter.cpp)
target_link_libraries(ip_filter PRIVATE ipv4)

# unit tests target

add_executable(ip_filter_tests
        parse_ipv4_test.cpp
        )
target_link_libraries(ip_filter_tests
        PRIVATE
            catch_main
            ipv4
        )

catch_discover_tests(
        ip_filter_tests
        TEST_PREFIX
        "ip_filter."
        EXTRA_ARGS
        -s
        --reporter=xml
        --out=ip_filter_tests.xml)
