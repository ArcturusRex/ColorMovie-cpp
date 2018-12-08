# ColorMovie-Cpp

ColorMovie aims to give a visual representation of dominant colors in movies. For that, it outputs a frame-by-frame histogram of dominant colors for a given video. Colors are detected thanks to k-means method.
ColorMovie uses OpenCV for video management. The GUI is running with Qt. 
The project is only in its early stages, for now only k-means method and tests have been implemented.

# Prerequisites

3D K-means test function requires openCV Viz module, which required **libvtk** to be installed.
In order to install it, you need to type the following in a terminal:
`sudo apt install sudo apt-get install libvtk7-dev`
