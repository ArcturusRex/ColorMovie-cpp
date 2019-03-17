#include <iostream>
#include "frameAnalyzer.h"
#include "frameExtractor.h"
#include "kMeansCluster.h"

using namespace core;

frameAnalyzer::frameAnalyzer(): m_clusterNb(5),
                                m_iterationNb(10)
{}

frameAnalyzer::frameAnalyzer(uint32_t clusterNb): m_clusterNb(clusterNb),
                                                  m_iterationNb(10)
{}

frameAnalyzer::frameAnalyzer(uint32_t clusterNb, uint32_t iterationNb): m_clusterNb(clusterNb),
                                                                        m_iterationNb(iterationNb)
{}

algo::ClusterSet3d frameAnalyzer::clusterizeFrame(cv::Mat& frame)
{
    algo::PointSet3d pointVec;
    algo::ClusterSet3d clusterVec;
    algo::Point3d point ={0, 0, 0, 0};
    for (uint32_t i = 0; i < frame.rows; ++i)
    {
        for (uint32_t j = 0; j < frame.cols; ++j)
        {
            point.x = frame.at<cv::Vec3b>(i, j)[0];
            point.y = frame.at<cv::Vec3b>(i, j)[1];
            point.z = frame.at<cv::Vec3b>(i, j)[2];
            pointVec.push_back(point);
        }
    }
    algo::KMeans3d clusterizer;
    clusterizer.setPoints(pointVec);
    clusterVec = clusterizer.kMeansClustering(m_iterationNb, m_clusterNb);
    return clusterVec;
}

