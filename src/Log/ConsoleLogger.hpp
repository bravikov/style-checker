#pragma once
#ifndef H_B6D8F117_11F5_4E9D_9214_40803259F3FC
#define H_B6D8F117_11F5_4E9D_9214_40803259F3FC

#include "ALogger.hpp"

#include <mutex>
#include <unordered_map>
#include <thread>

class ConsoleLogger: public ALogger
{
public:
    void log(LogData::Type type, const LogData& logData) override;

private:
    mutable std::mutex m_logMutex;
    std::unordered_map<std::thread::id, size_t> m_threads;
};

#endif /* #ifndef H_B6D8F117_11F5_4E9D_9214_40803259F3FC */
