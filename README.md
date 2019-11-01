# ColorMovie-Cpp

- [ColorMovie-Cpp](#colormovie-cpp)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Usage](#usage)

ColorMovie aims to give a visual representation of dominant colors in movies. For that, it outputs a frame-by-frame histogram of dominant colors for a given video. Colors are detected thanks to k-means method.
ColorMovie uses OpenCV for video management. The GUI is running with Qt.
The project is only in its early stages, for now only k-means method and tests have been implemented.

## Prerequisites

3D K-means test function requires openCV Viz module, which required **libvtk** to be installed.
In order to install it, you need to type the following in a terminal:
```bash
sudo apt install sudo apt-get install libvtk7-dev`
```

Colormovie-cpp now uses Conan C++ package manager, which needs to be installed as well:

```bash
sudo apt install conan
# Add bincrafters repo as additional remote
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
```

## Installation
```bash
mkdir build && cd build
conan install .. --build opencv
cmake ..
make
```

## Usage
```bash
build/bin/ColorMovie 
```