#pragma once
#include <string>
#include "opencv2/opencv.hpp"
#include "frameExtractor.h"
#include "kMeansCluster.h"

namespace core
{
class frameAnalyzer
{
 public:
    frameAnalyzer();
    explicit frameAnalyzer(uint32_t clusterNb);
    frameAnalyzer(uint32_t clusterNb, uint32_t iterationNb);
    algo::ClusterSet3d clusterizeFrame(cv::Mat& frame);

 private:
    uint32_t m_clusterNb;
    uint32_t m_iterationNb;
    std::string m_filename;
};
}
