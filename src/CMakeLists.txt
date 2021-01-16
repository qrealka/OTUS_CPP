add_subdirectory(helloworld_cli)
add_subdirectory(ip_filter)

# Install section
# For testing:
# echo "deb https://dl.bintray.com/qrealka/OTUS {distribution} {components}" | sudo tee -a /etc/apt/sources.list
# apt update && apt install -y helloworld
# helloworld_cli
install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

if(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR DEB)
else()
    set(CPACK_GENERATOR OSXX11)
endif()

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
