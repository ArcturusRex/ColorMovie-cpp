#include <iostream>
#include "loggerUtils.h"

namespace utils
{
void init_logger()
{
    try
    {
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("log.txt", 1024*1024*5, 1);
        file_sink->set_level(spdlog::level::debug);
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::info);
        auto logger = std::make_shared<spdlog::logger>("logger", spdlog::sinks_init_list({console_sink, file_sink}));
        logger->set_level(spdlog::level::debug);
        spdlog::register_logger(logger);
    }
    catch(const spdlog::spdlog_ex& e)
    {
        std::cerr << "Log initialization failed : " << e.what() << std::endl;
    }
}
}