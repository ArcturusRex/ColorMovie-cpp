#include <iostream>
#include "kMeansCluster.h"
#include "frameExtractor.h"
#include "frameAnalyzer.h"

int main(int argc, char *argv[])
{
    io::frameExtractor fe("input/test.mp4");
    core::frameAnalyzer fa(5, 5);
    algo::ClusterSet3d clusterVec;
    io::videoInfo_t info;
    try
    {
        fe.getVideoInfo(info);
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }

    for (uint32_t i = 0; i < info.frameCount; i+=1000)
    {
        cv::Mat frame;
        try
        {
            fe.getFrame(frame, i);
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
        clusterVec = fa.clusterizeFrame(frame);
        for (auto const & cluster : clusterVec)
        {
            std::cout << cluster.x << " - "
                      << cluster.y << " - "
                      << cluster.z << " - pts : "
                      << cluster.pointNb << std::endl;
        }
        std::cout << std::endl << std::endl;
    }
    return 0;
}