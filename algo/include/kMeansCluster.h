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

    typedef struct ClusterData
    {
        double cumulX;
        double cumulY;
        uint32_t pointNb;
    } ClusterData;

    typedef std::vector<Point2d> PointSet;

    double squareDist2d(Point2d ptA, Point2d ptB)
    {
        float dist = {0.0};

        dist = std::pow(ptB.x - ptA.x, 2) + std::pow(ptB.y - ptA.y, 2);
        return dist;
    }
    class KMeans
    {
        public:

        // Takes a set of 2D points, return a set of k-means centroids
        PointSet kMeansClustering(uint32_t iterations, uint32_t nbClusters);

        // Temporary test function, to be moved later on
        void test2DClustering();
        

        void setPoints(PointSet points);
        
        private:
        PointSet m_points;
    };
}