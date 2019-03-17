#pragma once
#include <string>
#include "opencv2/opencv.hpp"

namespace io
{

typedef struct videoInfo
{
    uint32_t height_px;
    uint32_t width_px;
    uint32_t frameRate;
    uint32_t frameCount;
} videoInfo_t;

class frameExtractor
{
 public:
    explicit frameExtractor(const std::string& videoPath);
    ~frameExtractor();
    void open();
    void computeVideoInfo();
    void getVideoInfo(videoInfo_t& videoInfo);
    void loadFrame(uint32_t index);
    void getFrame(cv::Mat& frame, uint32_t index);
    void saveFrame(const std::string& filename, uint32_t index);

 private:
    cv::VideoCapture* m_videoCapture;
    cv::Mat* m_currentFrame;
    std::string m_videoPath;
    videoInfo_t* m_videoInfo;
};
}  // namespace io
