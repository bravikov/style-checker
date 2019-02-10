#include "AFileStream.hpp"

std::string AFileStream::getNextFilePath()
{
    std::lock_guard<std::mutex> queueGuard{m_queueMutex};
    if (m_queue.empty()) {
        return std::string{};
    }
    const std::string filePath{m_queue.front()};
    m_queue.pop();
    return filePath;
}

bool AFileStream::ended() const
{
    return m_end;
}

void AFileStream::addFile(const std::string &filePath)
{
    std::lock_guard<std::mutex> queueGuard{m_queueMutex};
    m_queue.push(filePath);
}

void AFileStream::setEnd()
{
    m_end = true;
}
