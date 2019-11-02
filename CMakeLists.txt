cmake_minimum_required (VERSION 2.6)
cmake_policy(SET CMP0048 NEW)
project (ColorMovie VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

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
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(COLORMOVIE_DEPENDENCIES ${COLORMOVIE_DEPENDENCIES} ${OPENCV_LIBRARIES} ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})

# Sources
set(COLORMOVIE_SOURCES  src/algo/src/kMeansCluster.cpp
                        src/io/src/frameExtractor.cpp
                        src/core/src/frameAnalyzer.cpp
                        src/utils/src/loggerUtils.cpp
                        src/main.cpp)

# Includes
set(COLOLORMOVIE_INCLUDE_DIRECTORIES src/algo/include
                                     src/io/include
                                     src/core/include
                                     src/utils/include)
include_directories(${COLOLORMOVIE_INCLUDE_DIRECTORIES})

# Target
add_executable(ColorMovie ${COLORMOVIE_SOURCES})
target_include_directories(ColorMovie PUBLIC ${CONAN_INCLUDE_DIRS})
target_link_libraries(ColorMovie ${CONAN_LIBS} ${COLORMOVIE_DEPENDENCIES})




