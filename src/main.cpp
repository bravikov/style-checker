#include "FileStreamFromInput.hpp"
#include "FileStreamFromArgs.hpp"
#include "FileStreamHandler.hpp"
#include "Configuration.hpp"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    StyleChecker::Configuration configuration{argc, argv};

    if (configuration.help()) {
        std::cout << configuration.helpMessage();
        return 1;
    }

    FileStreamFromInput fileStream;
    FileStreamHandler fileHandler{&fileStream, configuration.jobs()};
    fileStream.run();
    fileHandler.wait();

    return 0;
}
