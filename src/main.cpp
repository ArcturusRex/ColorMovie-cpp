#include <iostream>
#include "kMeansCluster.h"
#include "frameExtractor.h"

int main(int argc, char *argv[])
{
    // load video
    io::frameExtractor fe("input/test.mp4");
    io::videoInfo_t videoInfo;
    cv::Mat testFrame;
    testFrame.convertTo(testFrame, CV_8UC3);
    fe.getVideoInfo(videoInfo);

    for (int i = 0; i < videoInfo.frameCount; i+=100 )
    {
        std::string outname = "output/frames/frame" + std::to_string(i) + ".png";
        fe.saveFrame(outname, i);
    }
    return 0;
}