#pragma once
#ifndef H_2C6AFAD6_F9B8_40DB_9188_128AC927A1E2
#define H_2C6AFAD6_F9B8_40DB_9188_128AC927A1E2

#include <string>
#include <memory>
#include "LogData.hpp"

class ALogger;

class Log
{
public:
    static void initialize(std::unique_ptr<ALogger> logger);

    static void diagnostic(const LogData& logData);
    static void error(const LogData& logData);

private:
    static const Log& instance(std::unique_ptr<ALogger> = nullptr);

    void log(const LogData::Type type, const LogData& logData) const;

    explicit Log(std::unique_ptr<ALogger> logger);

    std::unique_ptr<ALogger> m_logger;

    Log(const Log& other) = delete;
    Log(Log&& other) = delete;
    Log& operator=(const Log& other) = delete;
    Log&& operator=(Log&& other) = delete;
};

#endif /* #ifndef H_2C6AFAD6_F9B8_40DB_9188_128AC927A1E2 */
