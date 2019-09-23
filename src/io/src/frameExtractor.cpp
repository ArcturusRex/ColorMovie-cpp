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
    m_logger = spdlog::get("logger");

    // try to open video
    try
    {
        open();
        computeVideoInfo();
    }
    catch (std::string e)
    {
        m_logger->error(e);
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
        throw std::string("Cannot open video");
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
        throw std::string("Video not opened");
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
        throw std::string("Cannot get info on video");
    }
}

void frameExtractor::loadFrame(uint32_t index)
{
    if (m_videoCapture->isOpened())
    {
        if (index < m_videoInfo->frameCount)
        {
            // load desired frame
            m_videoCapture->set(cv::CAP_PROP_POS_FRAMES, index);
            *m_videoCapture >> *m_currentFrame;
        }
        else
        {
            throw std::string("Frame index is out of bounds");
        }
    }
    else
    {
        throw std::string("Cannot load frame");
    }
}

void frameExtractor::getFrame(cv::Mat& frame, uint32_t index)
{
    try
    {
        loadFrame(index);
    }
    catch(std::string e)
    {
        m_logger->error(e);
    }

    frame = *m_currentFrame;
}

void frameExtractor::saveFrame(const std::string& filename, uint32_t index)
{
     try
    {
        loadFrame(index);
    }
    catch(std::string e)
    {
        m_logger->error(e);
    }
    cv::imwrite(filename, *m_currentFrame);
}


