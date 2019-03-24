#include "Log.hpp"

#include "ALogger.hpp"

void Log::initialize(std::unique_ptr<ALogger> logger)
{
    instance(std::move(logger));
}

const Log&Log::instance(std::unique_ptr<ALogger> logger)
{
    static Log log{std::move(logger)};
    return log;
}

void Log::log(const LogData::Type type, const LogData& logData) const
{
    if (m_logger) {
        m_logger->log(type, logData);
    }
}

void Log::diagnostic(const LogData& logData)
{
    Log::instance().log(LogData::Diagnostic, logData);
}

void Log::error(const LogData& logData)
{
    Log::instance().log(LogData::Error, logData);
}

Log::Log(std::unique_ptr<ALogger> logger)
    : m_logger(std::move(logger))
{}
