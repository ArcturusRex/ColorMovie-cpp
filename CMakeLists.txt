cmake_minimum_required (VERSION 2.6)
project (ColorMovie)
set(CMAKE_CXX_STANDARD 17)
find_package(Git)
find_package (Threads)

if(NOT GIT_FOUND)
    message(ERROR "Cannot find git. git is required")
endif()

option(USE_GIT_PROTOCOL ON)
if(NOT USE_GIT_PROTOCOL)
    set(git_protocol "http")
else()
    set(git_protocol "git")
endif()

# create install folder if it doesn't exist
set(COLORMOVIE_INSTALL_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/install)
if(NOT EXISTS ${COLORMOVIE_INSTALL_DIRECTORY})
    message("Creating install directory")
    file(MAKE_DIRECTORY ${COLORMOVIE_INSTALL_DIRECTORY})
endif()

# Dependencies
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/External-OpenCV.cmake)
set(COLORMOVIE_DEPENDENCIES ${COLORMOVIE_DEPENDENCIES} ${OPENCV_LIBRARIES} ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})

# Sources
set(COLORMOVIE_SOURCES src/algo/src/kMeansCluster.cpp)

# Includes
set(COLOLORMOVIE_INCLUDE_DIRECTORIES src/algo/include)
include_directories(${COLOLORMOVIE_INCLUDE_DIRECTORIES})

# Target
add_executable(ColorMovie ${COLORMOVIE_SOURCES})
add_dependencies(ColorMovie myopencv)
target_link_libraries(ColorMovie ${COLORMOVIE_DEPENDENCIES} )
