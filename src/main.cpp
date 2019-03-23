#include "FileStreamFromInput.hpp"
#include "FileStreamFromArgs.hpp"
#include "FileStreamHandler.hpp"
#include "Configuration.hpp"
#include "AFileStream.hpp"

#include <iostream>
#include <string>
#include <memory>

int main(int argc, char* argv[])
{
    StyleChecker::Configuration configuration{argc, argv};

    if (configuration.help()) {
        std::cout << configuration.helpMessage();
        return 1;
    }

    std::unique_ptr<AFileStream> fileStream;

    if (const auto& files = configuration.files(); files.empty()) {
        fileStream = std::make_unique<FileStreamFromInput>();
    }
    else {
        fileStream = std::make_unique<FileStreamFromArgs>(files);
    }

    FileStreamHandler fileStreamHandler{fileStream.get(), configuration.jobs()};
    fileStream->run();
    fileStreamHandler.wait();

    return 0;
}
