#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include "kMeansCluster.h"

namespace algo
{
double squareDistToClust3d(Point3d ptA, ClusterData3d ptB)
{
    float dist = {0.0};

    dist = std::pow(ptB.x - ptA.x, 2) + std::pow(ptB.y - ptA.y, 2) + std::pow(ptB.z - ptA.z, 2);
    return dist;
}
}  // namespace algo

using namespace algo;
void KMeans3d::setPoints(PointSet3d &pointSet)
{
    m_points = pointSet;
}

PointSet3d& KMeans3d::getPoints()
{
    return m_points;
}

ClusterSet3d KMeans3d::kMeansClustering(uint32_t iterations, uint32_t nbClusters)
{

    // Output k-Means centroids
    ClusterSet3d kMeans3d(nbClusters);

    // Random number generator and seed
    std::random_device r;
    std::mt19937 randomEngine(r());

    // All indexes for input PointSet
    std::vector<uint32_t> kMeansId(0, m_points.size());
    std::iota(kMeansId.begin(), kMeansId.end(), 0);


    if (nbClusters <= m_points.size())
    {
        // Set initial k-means centroïds ids
        std::shuffle(kMeansId.begin(), kMeansId.end(), randomEngine);
        kMeansId.resize(nbClusters);
    }
    else
    {
        std::cout << "Number of clusters must be inferior or equal to number of points in set" << std::endl;
        // TODO : proper error management
        exit;
    }

    // Clustering according to given centroids and centroid updating
    for (int i =0; i < iterations; i++)
    {
        for (auto & point : m_points)
        {
            // Store square distances between all centroids and given point;
            std::vector<double> distKMeansVec;
            distKMeansVec.resize(kMeans3d.size());

            std::transform(kMeans3d.begin(), kMeans3d.end(), distKMeansVec.begin(), [=](ClusterData3d cluster){ return squareDistToClust3d(point, cluster);});

            // Find nearer centroid, store it and squared distance
            std::vector<double>::iterator minDistIt = std::min_element(distKMeansVec.begin(), distKMeansVec.end());
            point.kMeansId = std::distance(distKMeansVec.begin(), minDistIt);
        }

        std::vector<ClusterData3d> clusterDataVec(nbClusters);

        // Cumulate distances
        for (auto const & point : m_points)
        {
            clusterDataVec[point.kMeansId].x += point.x;
            clusterDataVec[point.kMeansId].y += point.y;
            clusterDataVec[point.kMeansId].z += point.z;
            clusterDataVec[point.kMeansId].pointNb++;
        }

        // Update centroïds
        std::transform(clusterDataVec.begin(), clusterDataVec.end(), kMeans3d.begin(),
                       [](ClusterData3d cluster){
                            ClusterData3d tmp = {cluster.x / std::max(1u,cluster.pointNb),
                                                 cluster.y / std::max(1u,cluster.pointNb),
                                                 cluster.z / std::max(1u,cluster.pointNb),
                                                 cluster.pointNb};
                            return tmp;});

    }
    return kMeans3d;
}