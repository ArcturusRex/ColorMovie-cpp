#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include "kMeansCluster.h"


double algo::squareDist2d(Point2d ptA, Point2d ptB)
{
    float dist = {0.0};

    dist = std::pow(ptB.x - ptA.x, 2) + std::pow(ptB.y - ptA.y, 2);
    return dist;
}

double algo::squareDist3d(Point3d ptA, Point3d ptB)
{
    float dist = {0.0};

    dist = std::pow(ptB.x - ptA.x, 2) + std::pow(ptB.y - ptA.y, 2) + std::pow(ptB.z - ptA.z, 2);
    return dist;
}

using namespace algo;

void KMeans::setPoints(PointSet &pointSet)
{
    m_points = pointSet;
}

PointSet& KMeans::getPoints()
{
    return m_points;
}

PointSet KMeans::kMeansClustering(uint32_t iterations, uint32_t nbClusters)
{
    // Output k-Means centroids
    PointSet kMeans(nbClusters);

    // Random number generator and seed
    std::random_device r;
    std::mt19937 randomEngine(r());

    // All indexes for input PointSet
    std::uniform_int_distribution<uint32_t> ptId(0, m_points.size()-1);

    // Choose random points in set as initial k-means centroids
    // Id of points already used as k-means initial points to avoid duplicata
    std::vector<uint32_t> kMeansId;

    // Only compute if number of k-Means clusters is superior or equal to the number of m_points in set
    if(nbClusters <= m_points.size())
    {
        for(uint32_t i = 0; i < nbClusters; i++)
        {
            // TODO : PointSet as class with overloaded copy operator
            uint32_t id = ptId(randomEngine);

            // Select Id while the one selected is already used
            while(std::find(kMeansId.begin(), kMeansId.end(), id)!=kMeansId.end())
            {
                id = ptId(randomEngine);
            }
            kMeans[i].x = m_points[id].x;
            kMeans[i].y = m_points[id].y;
            kMeansId.push_back(id);
        }
    }
    else
    {
        std::cout << "Number of clusters must be inferior or equal to number of points in set" << std::endl;
        // TODO : proper error management
        exit;
    }

    // Clustering according to given centroids and centroid updating
    for(int i =0; i < iterations; i++)
    {
        for(auto & point : m_points)
        {
            // Store square distances between all centroids and given point;
            std::vector<double> distKMeansVec;
            for(auto const & kMeansPoint : kMeans)
            {
                double distKmeans = {0.0};
                distKMeansVec.push_back(squareDist2d(kMeansPoint, point));
            }

            // Find nearer centroid, store it and squared distance
            std::vector<double>::iterator minDistIt = std::min_element(distKMeansVec.begin(), distKMeansVec.end());
            point.kMeansId = std::distance(distKMeansVec.begin(), minDistIt);
        }

        std::vector<ClusterData> clusterDataVec(nbClusters);
        // Init vector
        for(auto & clusterData : clusterDataVec)
        {
            clusterData.cumulX = 0.0;
            clusterData.cumulY = 0.0;
            clusterData.pointNb = 0;
        }

        // Cumulate distances
        for(auto const & point : m_points)
        {
            clusterDataVec[point.kMeansId].cumulX += point.x;
            clusterDataVec[point.kMeansId].cumulY += point.y;
            clusterDataVec[point.kMeansId].pointNb++;
        }

        // Update centroids
        for(int i = 0; i < kMeans.size(); i++)
        {
            // Avoid divinding by zero if no point belong to cluster
            kMeans[i].x =  clusterDataVec[i].cumulX / std::max(1u,clusterDataVec[i].pointNb);
            kMeans[i].y =  clusterDataVec[i].cumulY / std::max(1u,clusterDataVec[i].pointNb);
        }
    }

    return kMeans;
}

void KMeans3d::setPoints(PointSet3d &pointSet)
{
    m_points = pointSet;
}

PointSet3d& KMeans3d::getPoints()
{
    return m_points;
}

PointSet3d KMeans3d::kMeansClustering(uint32_t iterations, uint32_t nbClusters)
{
    // Output k-Means centroids
    PointSet3d kMeans3d(nbClusters);

    // Random number generator and seed
    std::random_device r;
    std::mt19937 randomEngine(r());

    // All indexes for input PointSet
    std::uniform_int_distribution<uint32_t> ptId(0, m_points.size()-1);

    // Choose random points in set as initial k-means centroids
    // Id of points already used as k-means initial points to avoid duplicata
    std::vector<uint32_t> kMeansId;

    // Only compute if number of k-Means clusters is superior or equal to the number of m_points in set
    if(nbClusters <= m_points.size())
    {
        for(uint32_t i = 0; i < nbClusters; i++)
        {
            // TODO : PointSet as class with overloaded copy operator
            uint32_t id = ptId(randomEngine);

            // Select Id while the one selected is already used
            while(std::find(kMeansId.begin(), kMeansId.end(), id)!=kMeansId.end())
            {
                id = ptId(randomEngine);
            }
            kMeans3d[i].x = m_points[id].x;
            kMeans3d[i].y = m_points[id].y;
            kMeansId.push_back(id);
        }
    }
    else
    {
        std::cout << "Number of clusters must be inferior or equal to number of points in set" << std::endl;
        // TODO : proper error management
        exit;
    }

    // Clustering according to given centroids and centroid updating
    for(int i =0; i < iterations; i++)
    {
        for(auto & point : m_points)
        {
            // Store square distances between all centroids and given point;
            std::vector<double> distKMeansVec;
            for(auto const & kMeansPoint : kMeans3d)
            {
                double distKmeans = {0.0};
                distKMeansVec.push_back(squareDist3d(kMeansPoint, point));
            }

            // Find nearer centroid, store it and squared distance
            std::vector<double>::iterator minDistIt = std::min_element(distKMeansVec.begin(), distKMeansVec.end());
            point.kMeansId = std::distance(distKMeansVec.begin(), minDistIt);
        }

        std::vector<ClusterData3d> clusterDataVec(nbClusters);
        // Init vector
        for(auto & clusterData : clusterDataVec)
        {
            clusterData.cumulX = 0.0;
            clusterData.cumulY = 0.0;
            clusterData.cumulZ = 0.0;
            clusterData.pointNb = 0;
        }

        // Cumulate distances
        for(auto const & point : m_points)
        {
            clusterDataVec[point.kMeansId].cumulX += point.x;
            clusterDataVec[point.kMeansId].cumulY += point.y;
            clusterDataVec[point.kMeansId].cumulZ += point.z;
            clusterDataVec[point.kMeansId].pointNb++;
        }

        // Update centroids
        for(int i = 0; i < kMeans3d.size(); i++)
        {
            // Avoid divinding by zero if no point belong to cluster
            kMeans3d[i].x =  clusterDataVec[i].cumulX / std::max(1u,clusterDataVec[i].pointNb);
            kMeans3d[i].y =  clusterDataVec[i].cumulY / std::max(1u,clusterDataVec[i].pointNb);
            kMeans3d[i].z =  clusterDataVec[i].cumulZ / std::max(1u,clusterDataVec[i].pointNb);
        }
    }

    return kMeans3d;
}