#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace algo
{
    typedef struct Point2d
    {
        float x;
        float y;
        uint32_t kMeansId;
    } Point2d;

    typedef struct Point3d
    {
        float x;
        float y;
        float z;
        uint32_t kMeansId;
    } Point3d;

    typedef struct ClusterData
    {
        double x;
        double y;
        uint32_t pointNb;
    } ClusterData;

    typedef struct ClusterData3d
    {
        double x;
        double y;
        double z;
        uint32_t pointNb;
    } ClusterData3d;

    typedef std::vector<Point2d> PointSet;
    typedef std::vector<Point3d> PointSet3d;
    typedef std::vector<ClusterData> ClusterSet;
    typedef std::vector<ClusterData3d> ClusterSet3d;

    // Squared Euclidean distance calculation for 2d points
    double squareDistToClust2d(Point2d ptA, ClusterData ptB);

    // Squared Euclidean distance calculation for 3d points
    double squareDistToClust3d(Point3d ptA, ClusterData3d ptB);

    class KMeans
    {
        public:

        // Takes a set of 2D points, return a set of k-means centroids
        ClusterSet kMeansClustering(uint32_t iterations, uint32_t nbClusters);

        // Sets input point set
        void setPoints(PointSet &pointSet);

        // Gets input point set
        PointSet& getPoints();

        private:
        PointSet m_points;
    };

        class KMeans3d
    {
        public:

        // Takes a set of 3D points, return a set of k-means centroids
        ClusterSet3d kMeansClustering(uint32_t iterations, uint32_t nbClusters);

        // Sets input point set
        void setPoints(PointSet3d &pointSet3d);

        // Gets input point set
        PointSet3d& getPoints();

        private:
        PointSet3d m_points;
    };
}

