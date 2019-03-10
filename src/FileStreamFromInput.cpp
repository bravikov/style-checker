#include "FileStreamFromInput.hpp"

#include <iostream>
#include <string>

void FileStreamFromInput::run()
{
    for (std::string path; std::getline(std::cin, path);) {
        if (!path.empty()) {
            addFile(path);
        }
    }
    setEnd();
}
