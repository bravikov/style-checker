#include "ConsoleLogger.hpp"

#include <iostream>

void ConsoleLogger::log(LogData::Type type, const LogData& logData)
{
    std::lock_guard<std::mutex> logGuard(m_logMutex);

    std::ostream& stream = std::cout;

    const std::thread::id threadId = std::this_thread::get_id();
    if (m_threads.find(threadId) == m_threads.end()) {
        m_threads[threadId] = m_threads.size();
    }

    const char delimiter = ':';

    stream << m_threads[threadId] << delimiter;

    stream << LogData::typeName(type) << delimiter;

    if (logData.fileName) {
        stream << logData.fileName.value() << delimiter;
    }

    if (logData.lineNumber) {
        stream << logData.lineNumber.value() << delimiter;
    }

    if (logData.columnNumber) {
        stream << logData.columnNumber.value() << delimiter;
    }

    stream << " " << logData.message;

    stream << std::endl;
}
