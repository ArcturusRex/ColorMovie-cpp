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

    PointSet kMeansClustering(PointSet points, uint32_t iterations, uint32_t nbClusters)
    {
        // Output k-Means centroids
        PointSet kMeans(nbClusters);

        // Random number generator and seed
        std::random_device r;
        std::mt19937 randomEngine(r());

        // All indexes for input PointSet
        std::uniform_int_distribution<uint32_t> ptId(0, points.size()-1);

        // Choose random points in set as initial k-means centroids
        // Id of points already used as k-means initial points to avoid duplicata
        std::vector<uint32_t> kMeansId;

        // Only compute if number of k-Means clusters is superior or equal to the number of points in set
        if(nbClusters <= points.size())
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
                kMeans[i].x = points[id].x;
                kMeans[i].y = points[id].y;
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
            for(auto & point : points)
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
            for(auto const & point : points)
            {
                clusterDataVec[point.kMeansId].cumulX += point.x;
                clusterDataVec[point.kMeansId].cumulY += point.y;
                clusterDataVec[point.kMeansId].pointNb++;
            }

            // Update centroids
            for(int i = 0; i < kMeans.size(); i++)
            {
                kMeans[i].x =  clusterDataVec[i].cumulX / clusterDataVec[i].pointNb;
                kMeans[i].y =  clusterDataVec[i].cumulY / clusterDataVec[i].pointNb;
            }
        }

        return kMeans;
    }

    // Generate random 2D point set, compute k-means and print results in an opencv window 
    // (green circle : point, red circle : k-means centroid)
    void test2DClustering()
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
        PointSet kMeans(clusterNb);

        kMeans = kMeansClustering(pointSet, iterationNb, clusterNb);
        std::vector<cv::Point2f> cvClustVec;
        for(auto const & kMean : kMeans)
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
}