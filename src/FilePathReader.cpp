#include "FilePathReader.hpp"

#include "AFileStreamReader.hpp"

FilePathReader::FilePathReader(AFileStreamReader *fileStream)
    : m_fileStream{fileStream}
{

}

bool FilePathReader::next()
{
    m_filePath = m_fileStream->getNextFilePath();
    return !m_filePath.empty();
}

std::string FilePathReader::filePath() const
{
    return m_filePath;
}
