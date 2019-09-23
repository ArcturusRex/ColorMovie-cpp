#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace algo
{
    typedef struct Point3d
    {
        float x = 0.0;
        float y = 0.0;
        float z = 0.0;
        uint32_t kMeansId = 0;
    } Point3d;

    typedef struct ClusterData3d
    {
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        uint32_t pointNb = 0;
    } ClusterData3d;

    typedef std::vector<Point3d> PointSet3d;
    typedef std::vector<ClusterData3d> ClusterSet3d;

    // Squared Euclidean distance calculation for 3d points
    double squareDistToClust3d(Point3d ptA, ClusterData3d ptB);

    class KMeans3d
    {
        public:

        KMeans3d();

        // Takes a set of 3D points, return a set of k-means centroids
        ClusterSet3d kMeansClustering(uint32_t iterations, uint32_t nbClusters);

        // Sets input point set
        void setPoints(PointSet3d &pointSet3d);

        // Gets input point set
        PointSet3d& getPoints();

        private:
        PointSet3d m_points;
        std::shared_ptr<spdlog::logger> m_logger;
    };
}

