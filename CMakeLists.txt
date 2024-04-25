
cmake_minimum_required(VERSION 3.19)

SET(PROJECT_NAME "ConCluster")
SET(BINARY_NAME "concluster")

PROJECT("${PROJECT_NAME}")

SET(LIBRARY_VERSION_MAJOR 1)
SET(LIBRARY_VERSION_STRING 0.1)

INCLUDE(GNUInstallDirs)

SET(LIBRARY_BASE_PATH "${PROJECT_SOURCE_DIR}")

INCLUDE_DIRECTORIES (
    "${LIBRARY_BASE_PATH}"
)

SET(PUBLIC_SOURCES_FILES
    "${LIBRARY_BASE_PATH}/src/cluster.c"
    "${LIBRARY_BASE_PATH}/src/node.c"
    "${LIBRARY_BASE_PATH}/src/actions.c"
    "${LIBRARY_BASE_PATH}/src/address.c"
    "${LIBRARY_BASE_PATH}/src/id.c"
    "${LIBRARY_BASE_PATH}/src/role.c"
    "${LIBRARY_BASE_PATH}/src/background_tasks.c"
    "${LIBRARY_BASE_PATH}/src/single_server.c"
    "${LIBRARY_BASE_PATH}/src/servers.c"
    "${LIBRARY_BASE_PATH}/src/contacts.c"
)

SET(PUBLIC_HEADER_FILES
    "${LIBRARY_BASE_PATH}/include/cluster.h"
    "${LIBRARY_BASE_PATH}/include/node.h"
    "${LIBRARY_BASE_PATH}/include/actions.h"
    "${LIBRARY_BASE_PATH}/include/address.h"
    "${LIBRARY_BASE_PATH}/include/id.h"
    "${LIBRARY_BASE_PATH}/include/role.h"
    "${LIBRARY_BASE_PATH}/include/background_tasks.h"
    "${LIBRARY_BASE_PATH}/include/single_server.h"
    "${LIBRARY_BASE_PATH}/include/servers.h"
    "${LIBRARY_BASE_PATH}/include/contacts.h"
)


SET(CMAKE_C_VISIBILITY_PRESET hidden)

ADD_LIBRARY (
    ${BINARY_NAME} SHARED ${PUBLIC_SOURCES_FILES}
)

SET_TARGET_PROPERTIES (
    ${BINARY_NAME} PROPERTIES
    VERSION ${LIBRARY_VERSION_STRING}
    SOVERSION ${LIBRARY_VERSION_MAJOR}
    PUBLIC_HEADER "${PUBLIC_HEADER_FILES}"
)

ADD_DEFINITIONS("-Wno-attributes")

INSTALL (
    TARGETS ${BINARY_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${BINARY_NAME}"
)
