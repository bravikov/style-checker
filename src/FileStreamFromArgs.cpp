#include "FileStreamFromArgs.hpp"

FileStreamFromArgs::FileStreamFromArgs(const std::vector<std::string>& files):
    m_files(files)
{}

void FileStreamFromArgs::run()
{
    for (const std::string& file: m_files) {
        if (!file.empty()) {
            addFile(file);
        }
    }
    setEnd();
}
