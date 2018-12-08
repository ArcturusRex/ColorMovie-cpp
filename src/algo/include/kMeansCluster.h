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

    typedef std::vector<Point2d> PointSet;

    double squareDist2d(Point2d ptA, Point2d ptB);
    double squareDist3d(Point2d ptA, Point2d ptB);

    class KMeans
    {
        public:

        // Takes a set of 2D points, return a set of k-means centroids
        PointSet kMeansClustering(uint32_t iterations, uint32_t nbClusters);

        // Generate random 2D point set, compute k-means and print results in an opencv window
        // (green circle : point, red circle : k-means centroid)
        // Temporary test function, to be moved later on
        void test2DClustering();


        void setPoints(PointSet points);

        private:
        PointSet m_points;
    };
}

