#include "FileStreamHandler.hpp"

#include "FilePathReader.hpp"
#include "AFileStreamReader.hpp"
#include "LineSplitter.hpp"

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
    m_threadCount++;

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
    LineSplitter splitter{""};

    std::ifstream file{filePath, std::ios_base::binary};
    if (!file.is_open()) {
        return;
    }

    std::string fileContent;

    try {
        const std::uintmax_t fileSize = std::filesystem::file_size(filePath);
        fileContent.reserve(fileSize);
    } catch(std::filesystem::filesystem_error& e) {
        std::cerr << e.what() << std::endl;
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
            std::cerr << "File handling error. File: '" << filePath << "'."
                      << std::endl;
            error = true;
            break;
        }
    }

    if (error) {
        return;
    }

    file.close();

    /* Check line ending */

    //LineSplitter splitter{fileContent};


    /*for (const char& c: fileContent) {

    }*/

    /* Check ASCII */
    AsciiTextChecker asciiTextChecker;
    for (const char& c: fileContent) {
        if (!asciiTextChecker.check(c)) {
            std::cerr << "Non-ASCII character in the file (" << filePath << ")"
                      << std::endl;
        }
    }

    /* Check indent*/
}
