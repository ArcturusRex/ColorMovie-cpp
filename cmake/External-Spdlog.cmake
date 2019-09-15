message("External project: Spdlog")
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
ExternalProject_Add(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.3.1
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_SOURCE_DIR}/install/thirdparty/spdlog/ -DSPDLOG_BUILD_BENCH=OFF
    EXCLUDE_FROM_ALL TRUE
)

set(SPDLOG_INSTALL_DIR ${CMAKE_SOURCE_DIR}/install/thirdparty/spdlog/)
set(SPDLOG_LIBRARY spdlog)

include_directories(${CMAKE_SOURCE_DIR}/install/thirdparty/spdlog/include/)