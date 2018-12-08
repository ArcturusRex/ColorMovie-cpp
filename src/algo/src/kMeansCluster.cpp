#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/viz.hpp"
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

// Generate random 2D point set, compute k-means and print results in an opencv window
// (green circle : point, red circle : k-means centroid)
void KMeans::test2DClustering()
{
    std::random_device r;
    std::mt19937 randomEngine(r());

    double pointSetMaxRange = 100.0;
    uint32_t pointSetNb = 100;
    uint32_t clusterNb = 5;
    uint32_t iterationNb = 300;
    PointSet pointSet(pointSetNb);

    //create a test gui window:
    cv::namedWindow("2D clustering test",1);

    //initialize a matrix of black pixels:
    cv::Mat output = cv::Mat::zeros((int)pointSetMaxRange*10, (int)pointSetMaxRange*10, CV_8UC3 );

    // opencv point vector

    std::vector<cv::Point2f> cvPointVec;
    for(uint32_t i = 0; i < pointSet.size(); i++)
    {
        // All indexes for input PointSet

        if (i <= 20)
        {
            std::uniform_real_distribution<float> xCoords(0.0, 10.0);
            std::uniform_real_distribution<float> yCoords(0.0, 10.0);
            pointSet[i].x = xCoords(randomEngine);
            pointSet[i].y = yCoords(randomEngine);
        }
        else if ( i > 20 && i <= 40)
        {
            std::uniform_real_distribution<float> xCoords(90.0, 100.0);
            std::uniform_real_distribution<float> yCoords(0.0, 10.0);
            pointSet[i].x = xCoords(randomEngine);
            pointSet[i].y = yCoords(randomEngine);
        }
        else if (i > 40 && i <= 60)
        {
            std::uniform_real_distribution<float> xCoords(0.0, 10.0);
            std::uniform_real_distribution<float> yCoords(90.0, 100.0);
            pointSet[i].x = xCoords(randomEngine);
            pointSet[i].y = yCoords(randomEngine);
        }
        else if (i > 60 && i <= 80)
        {
            std::uniform_real_distribution<float> xCoords(90.0, 100.0);
            std::uniform_real_distribution<float> yCoords(90.0, 100.0);
            pointSet[i].x = xCoords(randomEngine);
            pointSet[i].y = yCoords(randomEngine);
        }
        else if (i > 80 && i <=100)
        {
            std::uniform_real_distribution<float> xCoords(40.0, 60.0);
            std::uniform_real_distribution<float> yCoords(40.0, 60.0);
            pointSet[i].x = xCoords(randomEngine);
            pointSet[i].y = yCoords(randomEngine);
        }

        cv::Point cvPoint (pointSet[i].x*10, pointSet[i].y*10);
        cvPointVec.push_back(cvPoint);
        std::cout << "X : " << pointSet[i].x << " Y : " << pointSet[i].y << std::endl;
    }
    PointSet kMeansVec(clusterNb);

    // Set list of points to be analysed
    m_points = pointSet;

    kMeansVec = kMeansClustering(iterationNb, clusterNb);
    std::vector<cv::Point2f> cvClustVec;
    for(auto const & kMean : kMeansVec)
    {
        cv::Point cvClust (kMean.x*10, kMean.y*10);
        cvClustVec.push_back(cvClust);
        std::cout << "XMean : " << kMean.x << " YMean : " << kMean.y << std::endl;
    }


    //write text on the matrix:
    cv::Scalar green(0.0, 255.0, 0.0);
    cv::Scalar red(0.0, 0.0, 255.0);
    for(auto const & cvPoint : cvPointVec)
    {
        cv::circle(output, cvPoint, 2, green);
    }

    for(auto const & cvClust : cvClustVec)
    {
        cv::Point2f clustPt1(cvClust.x - 2, cvClust.y - 2);
        cv::Point2f clustPt2(cvClust.x + 2, cvClust.y + 2);
        cv::rectangle(output, clustPt1, clustPt2, red, 2);
    }

    //display the image:
    cv::imshow("2D clustering test", output);

    //wait for the user to press any key:
    cv::waitKey(0);
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

// Generate random 2D point set, compute k-means and print results in an opencv window
// (green circle : point, red circle : k-means centroid)
void KMeans3d::test3DClustering()
{
    std::random_device r;
    std::mt19937 randomEngine(r());

    double pointSetMaxRange = 100.0;  // Range of points ((pointSetMaxRange*2)^3 space)
    int pointSetDimensions[] = {floor(pointSetMaxRange*2), floor(pointSetMaxRange*2), floor(pointSetMaxRange*2)}; // Space dimensions
    uint32_t pointSetNb = 100;  // Amount of points in set
    uint32_t pointSetDivision = (uint32_t)floor(pointSetNb * 0.2);  // 20% of points
    uint32_t clusterNb = 5;  // Number of clusters
    uint32_t iterationNb = 300;  // Number of iterations for K-means
    PointSet3d pointSet3d(pointSetNb);

    //create a test gui window:
    cv::viz::Viz3d myWindow("3D clustering test");
    myWindow.showWidget("Coordinate Widget", cv::viz::WCoordinateSystem());



    cv::Point3d camPos(100.0f, 100.0f,0.0f), camFocalPoint(0.0f,0.0f,0.0f), camYDir(-1.0f,0.0f,0.0f);
    cv::Affine3f camPose = cv::viz::makeCameraPose(camPos, camFocalPoint, camYDir);
    cv::Affine3f transform = cv::viz::makeTransformToGlobal(cv::Vec3f(0.0f,-1.0f,0.0f), cv::Vec3f(-1.0f,0.0f,0.0f), cv::Vec3f(0.0f,0.0f,-1.0f), camPos);

    cv::viz::WWidgetMerger widgetMerger;

    // opencv point vector
    std::vector<cv::Point3f> cvPointVec;
    for(uint32_t i = 0; i < pointSet3d.size(); i++)
    {
        // All indexes for input PointSet

        if (i <= pointSetDivision)
        {
            std::uniform_real_distribution<float> xCoords(-45.0, -55.0);
            std::uniform_real_distribution<float> yCoords(-45.0, -55.0);
            std::uniform_real_distribution<float> zCoords(-5.0, 5.0);
            pointSet3d[i].x = xCoords(randomEngine);
            pointSet3d[i].y = yCoords(randomEngine);
            pointSet3d[i].z = zCoords(randomEngine);
        }
        else if ( i > pointSetDivision && i <= 2*pointSetDivision)
        {
            std::uniform_real_distribution<float> xCoords(45.0, 55.0);
            std::uniform_real_distribution<float> yCoords(45.0, 55.0);
            std::uniform_real_distribution<float> zCoords(-5.0, 5.0);
            pointSet3d[i].x = xCoords(randomEngine);
            pointSet3d[i].y = yCoords(randomEngine);
            pointSet3d[i].z = zCoords(randomEngine);
        }
        else if (i > 2*pointSetDivision && i <= 3*pointSetDivision)
        {
            std::uniform_real_distribution<float> xCoords(-45.0, -55.0);
            std::uniform_real_distribution<float> yCoords(45.0, 55.0);
            std::uniform_real_distribution<float> zCoords(-5.0, 5.0);
            pointSet3d[i].x = xCoords(randomEngine);
            pointSet3d[i].y = yCoords(randomEngine);
            pointSet3d[i].z = zCoords(randomEngine);
        }
        else if (i > 3*pointSetDivision && i <= 4*pointSetDivision)
        {
            std::uniform_real_distribution<float> xCoords(45.0, 55.0);
            std::uniform_real_distribution<float> yCoords(-45.0, -55.0);
            std::uniform_real_distribution<float> zCoords(-5.0, 5.0);
            pointSet3d[i].x = xCoords(randomEngine);
            pointSet3d[i].y = yCoords(randomEngine);
            pointSet3d[i].z = zCoords(randomEngine);
        }
        else if (i > 4*pointSetDivision && i <=pointSetNb)
        {
            std::uniform_real_distribution<float> xCoords(-10.0, 10.0);
            std::uniform_real_distribution<float> yCoords(-10.0, 10.0);
            std::uniform_real_distribution<float> zCoords(-10.0, 10.0);
            pointSet3d[i].x = xCoords(randomEngine);
            pointSet3d[i].y = yCoords(randomEngine);
            pointSet3d[i].z = zCoords(randomEngine);
        }

        cv::Point3f cvPoint (pointSet3d[i].x, pointSet3d[i].y, pointSet3d[i].z);
        cvPointVec.push_back(cvPoint);
        std::cout << "X : " << pointSet3d[i].x << " Y : " << pointSet3d[i].y << " Z : " << pointSet3d[i].z << std::endl;
    }
    PointSet3d kMeansVec(clusterNb);

    // Set list of points to be analysed
    m_points = pointSet3d;

    kMeansVec = kMeansClustering(iterationNb, clusterNb);
    std::vector<cv::Point3f> cvClustVec;
    for(auto const & kMean : kMeansVec)
    {
        cv::Point3f cvClust (kMean.x, kMean.y, kMean.z);
        cvClustVec.push_back(cvClust);
        std::cout << "XMean : " << kMean.x << " YMean : " << kMean.y << " ZMean : " << kMean.z << std::endl;
    }


    //write text on the matrix:
    cv::Scalar green(0.0, 255.0, 0.0);
    cv::Scalar red(0.0, 0.0, 255.0);
    for(auto const & cvPoint : cvPointVec)
    {
        // Create a sphere widget
        cv::viz::WSphere sphere(cv::Point3f(cvPoint.x,cvPoint.y,cvPoint.z), true, 10, cv::viz::Color::red());
        // Cast sphere widget to cloud widget
        widgetMerger.addWidget(sphere);
    }

    for(auto const & cvClust : cvClustVec)
    {
        cv::Point3f clustPt1(cvClust.x - 2, cvClust.y - 2, cvClust.z - 2);
        cv::Point3f clustPt2(cvClust.x + 2, cvClust.y + 2, cvClust.z + 2);
        cv::viz::WCube cube(clustPt1, clustPt2, false, cv::viz::Color::green());
        widgetMerger.addWidget(cube);
    }

    widgetMerger.finalize();

    cv::Affine3f cloudPose = cv::Affine3f().translate(cv::Vec3f(0.0f,0.0f,3.0f));
    cv::Affine3f cloudPoseGlobal = transform * cloudPose;
    //display the image:
    myWindow.showWidget("3D clustering test", widgetMerger, cloudPoseGlobal);
    myWindow.setViewerPose(camPose);
    myWindow.spin();
}

int main()
{
    KMeans3d kMeans3d;
    kMeans3d.test3DClustering();
    return 0;
}