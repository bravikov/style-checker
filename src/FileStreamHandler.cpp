#include "FileStreamHandler.hpp"

#include "FilePathReader.hpp"
#include "AFileStreamReader.hpp"
#include "LineSplitter.hpp"
#include "TextLine.hpp"

#include <iostream>

FileStreamHandler::FileStreamHandler(
    AFileStreamReader *fileStreamReader,
    const size_t maxThreadCount
)
    : m_fileStreamReader(fileStreamReader)
    , m_maxThreadCount(maxThreadCount)
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

        FileHandler fileHandler(filePath);
    }

    m_threadCount--;
}

#include "Log/Log.hpp"

#include <boost/format.hpp>
#include <fstream>
#include <filesystem>

class AsciiTextChecker
{
public:
    bool check(const char c)
    {
        return (0x20 <= c && c <= 0x7E) || c == '\t' || c == '\n' || c== '\r';
    }
};

FileHandler::FileHandler(const std::string &filePath)
{
    std::ifstream file{filePath, std::ios_base::binary};
    if (!file.is_open()) {
        Log::error({"File is not opened.", filePath});
        return;
    }

    std::string fileContent;

    try {
        const std::uintmax_t fileSize = std::filesystem::file_size(filePath);
        fileContent.reserve(fileSize);
    } catch(std::filesystem::filesystem_error& e) {
        Log::error({e.what(), filePath});
        return;
    }

    bool error = false;

    char readBuffer[1024];

    while (!file.eof()) {
        file.read(readBuffer, sizeof readBuffer);

        const size_t readCount
            = file.gcount() >= 0 ? static_cast<size_t>(file.gcount()) : 0;

        fileContent.append(readBuffer, readCount);

        if (file.bad()) {
            Log::error({"File handling error.", filePath});
            error = true;
            break;
        }
    }

    if (error) {
        return;
    }

    file.close();

    /* Check empty file */

    if (fileContent.empty()) {
        Log::diagnostic({"File is empty.", filePath});
        return;
    }

    /* Check line ending */

    LineSplitter splitter{fileContent};

    for (size_t lineCounter = 1; !splitter.eof(); lineCounter++) {
        auto line = splitter.getNextLine();
        if (line.lineEnding() != LineEnding::lf) {
            const auto message = boost::format("Line ending is %1%.")
                                 % line.lineEnding().name();
            Log::diagnostic({message.str(), filePath, lineCounter});
        }
    }

    /* Check ASCII */
    AsciiTextChecker asciiTextChecker;
    for (const char& c: fileContent) {
        if (!asciiTextChecker.check(c)) {
            Log::diagnostic({"There is non-ASCII character.", filePath});
        }
    }

    /* Check indent*/
}
