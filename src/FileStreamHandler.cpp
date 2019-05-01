#include "FileStreamHandler.hpp"

#include "FilePathReader.hpp"
#include "AFileStreamReader.hpp"

#include <iostream>

FileStreamHandler::FileStreamHandler(AFileStreamReader *fileStreamReader,
                                     const size_t maxThreadCount,
                                     DiagList diagnostics
)
    : m_fileStreamReader(fileStreamReader)
    , m_maxThreadCount(maxThreadCount)
    , m_diagnostics(diagnostics)
{
    for (size_t t = 0; t < m_maxThreadCount; t++) {
        std::thread handlerThread(&FileStreamHandler::handler, this);
        handlerThread.detach();
        m_threadCount++;
    }
}

void FileStreamHandler::wait()
{
    while(m_threadCount != 0) {
        std::this_thread::yield();
    }
}

bool FileStreamHandler::diagnosticsSuccess() const
{
    return m_diagnosticsSuccess;
}

void FileStreamHandler::handler()
{
    if (!m_fileStreamReader) {
        return;
    }

    FilePathReader filePathReader{m_fileStreamReader};

    while(filePathReader.next() || !m_fileStreamReader->ended()) {
        const std::string filePath = filePathReader.filePath();
        if (filePath.empty()) {
            std::this_thread::yield();
            continue;
        }

        for (const auto& diagnostic: *m_diagnostics) {
            if (!diagnostic->check(filePath)) {
                m_diagnosticsSuccess = false;
            }
        }
    }

    m_threadCount--;
}
