#include <iostream>
#include "frameExtractor.h"

using namespace io;
frameExtractor::frameExtractor(const std::string& videoPath)
{
    m_videoPath = videoPath;
    m_videoCapture = new cv::VideoCapture();
    m_currentFrame = new cv::Mat();
    m_currentFrame->convertTo(*m_currentFrame, CV_8UC3);
    m_videoInfo = new videoInfo_t();

    // try to open video
    try
    {
        open();
        computeVideoInfo();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }

    // retrieve file metadata
}

frameExtractor::~frameExtractor()
{
    delete m_videoCapture;
    delete m_currentFrame;
    delete m_videoInfo;
}

void frameExtractor::open()
{
    // try to open video
    bool rc = m_videoCapture->open(m_videoPath);
    if (rc == false)
    {
        std::runtime_error re("Cannot open video");
        throw(re);
    }
}

void frameExtractor::computeVideoInfo()
{
    if (m_videoCapture->isOpened())
    {

        *m_videoInfo = { static_cast<uint32_t>(m_videoCapture->get(cv::CAP_PROP_FRAME_HEIGHT)),
                         static_cast<uint32_t>(m_videoCapture->get(cv::CAP_PROP_FRAME_WIDTH)),
                         static_cast<uint32_t>(m_videoCapture->get(cv::CAP_PROP_FPS)),
                         static_cast<uint32_t>(m_videoCapture->get(cv::CAP_PROP_FRAME_COUNT))
        };
    }
    else
    {
        std::runtime_error re("Video not opened");
        throw(re);
    }
}

void frameExtractor::getVideoInfo(videoInfo_t& videoInfo)
{
    if (m_videoCapture->isOpened())
    {
        videoInfo = *m_videoInfo;
    }
    else
    {
        std::runtime_error re("Video not opened");
        throw(re);
    }
}

void frameExtractor::loadFrame(uint32_t index)
{
    if (m_videoCapture->isOpened())
    {
        if (index < m_videoInfo->frameCount)
        {
            // load desired frame
            m_videoCapture->set(CV_CAP_PROP_POS_FRAMES, index);
            *m_videoCapture >> *m_currentFrame;
        }
        else
        {
            std::runtime_error re("Frame index is out of bounds");
            throw(re);
        }
    }
    else
    {
        std::runtime_error re("Video not opened");
        throw(re);
    }
}

void frameExtractor::getFrame(cv::Mat& frame, uint32_t index)
{
    try
    {
        loadFrame(index);
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }

    frame = *m_currentFrame;
}

void frameExtractor::saveFrame(const std::string& filename, uint32_t index)
{
     try
    {
        loadFrame(index);
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
    cv::imwrite(filename, *m_currentFrame);
}


