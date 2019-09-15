#include <iostream>
#include "kMeansCluster.h"
#include "frameExtractor.h"
#include "frameAnalyzer.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/base_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "loggerUtils.h"

int main(int argc, char *argv[])
{
    utils::init_logger();
    std::shared_ptr<spdlog::logger> logger = spdlog::get("logger");
    if(!logger)
        throw std::runtime_error("Cannot initialize logger, exiting...");
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

    for (uint32_t i = 0; i < info.frameCount; i+=100)
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
        logger->info("Frame {}/{} clustered", i/100 + 1, info.frameCount/100 + 1);
        for (auto const & cluster : clusterVec)
        {
            logger->debug("cluster : ({}, {}, {}) : {} points", cluster.x, cluster.y, cluster.z, cluster.pointNb);
        }
    }
    return 0;
}