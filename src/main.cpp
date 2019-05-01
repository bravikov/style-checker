#include "FileStreamFromInput.hpp"
#include "FileStreamFromArgs.hpp"
#include "FileStreamHandler.hpp"
#include "Configuration.hpp"
#include "AFileStream.hpp"
#include "Log/Log.hpp"
#include "Log/ConsoleLogger.hpp"
#include "Diagnostics.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <list>

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

    Log::initialize(std::make_unique<ConsoleLogger>());

    namespace DiagNs = Diagnostics;
    using DiagPtr = std::shared_ptr<DiagNs::File::Base>;

    auto diagnostics = std::make_shared<std::list<DiagPtr>>();
    auto fileReader = std::make_shared<DiagNs::File::Reader>();
    diagnostics->push_back(fileReader);
    fileReader->addDiagnostic(std::make_shared<DiagNs::FileContent::Empty>());
    auto fileSplitter = std::make_shared<DiagNs::FileContent::Splitter>();
    fileReader->addDiagnostic(fileSplitter);
    fileSplitter->addDiagnostic(
                std::make_shared<DiagNs::Line::Ending>(LineEnding::lf));
    fileSplitter->addDiagnostic(
                std::make_shared<DiagNs::Line::Length>(120));
    fileSplitter->addDiagnostic(std::make_shared<DiagNs::Line::Ascii>());
    fileSplitter->addDiagnostic(std::make_shared<DiagNs::Line::Utf8>());

    FileStreamHandler fileStreamHandler{fileStream.get(), configuration.jobs(),
                                        diagnostics};
    fileStream->run();
    fileStreamHandler.wait();

    if (fileStreamHandler.diagnosticsSuccess()) {
        return 0;
    }
    else {
        return 1;
    }
}
