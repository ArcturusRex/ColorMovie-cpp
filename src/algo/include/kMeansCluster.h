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
        double cumulX;
        double cumulY;
        uint32_t pointNb;
    } ClusterData;

        typedef struct ClusterData3d
    {
        double cumulX;
        double cumulY;
        double cumulZ;
        uint32_t pointNb;
    } ClusterData3d;

    typedef std::vector<Point2d> PointSet;
    typedef std::vector<Point3d> PointSet3d;

    // Squared Euclidean distance calculation for 2d points
    double squareDist2d(Point2d ptA, Point2d ptB);

    // Squared Euclidean distance calculation for 3d points
    double squareDist3d(Point3d ptA, Point3d ptB);

    class KMeans
    {
        public:

        // Takes a set of 2D points, return a set of k-means centroids
        PointSet kMeansClustering(uint32_t iterations, uint32_t nbClusters);

        // Generate random 2D point set, compute k-means and print results in an opencv window
        // (green circle : point, red circle : k-means centroid)
        // Temporary test function, to be moved later on
        void test2DClustering();

        private:
        PointSet m_points;
    };

        class KMeans3d
    {
        public:

        // Takes a set of 3D points, return a set of k-means centroids
        PointSet3d kMeansClustering(uint32_t iterations, uint32_t nbClusters);

        // Generate random 3D point set, compute k-means and print results in an opencv window
        // (green circle : point, red circle : k-means centroid)
        // Temporary test function, to be moved later on
        void test3DClustering();

        private:
        PointSet3d m_points;
    };
}

