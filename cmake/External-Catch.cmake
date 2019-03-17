message("External project: Catch")
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
ExternalProject_Add(catch
  GIT_REPOSITORY ${git_protocol}://github.com/charlesw/catch.git
  GIT_TAG master
  SOURCE_DIR catch
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    ${ep_common_args}
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_SOURCE_DIR}/install/thirdparty/catch/
)

set(CATCH_INSTALL_DIR ${CMAKE_SOURCE_DIR}/install/thirdparty/catch)

set(CATCH_INCLUDE_DIR ${CATCH_INSTALL_DIR}/include)
set(CATCH_LIBRARIES Catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
