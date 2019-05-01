#include "Diagnostics.hpp"

#include "LineSplitter.hpp"
#include "TextLine.hpp"

#include "Log/Log.hpp"

#include "Algorithm.hpp"

#include <boost/format.hpp>
#include <fstream>
#include <filesystem>

namespace Diagnostics {

    void File::Reader::addDiagnostic(
            std::shared_ptr<Diagnostics::FileContent::Base> diagnostic
    ) {
        m_diagnostics.push_back(diagnostic);
    }

    bool File::Reader::check(const std::string& filePath) const
    {
        std::ifstream file{filePath, std::ios_base::binary};
        if (!file.is_open()) {
            Log::error({"File is not opened.", filePath});
            return false;
        }

        std::string fileContent;

        try {
            const auto fileSize = std::filesystem::file_size(filePath);
            fileContent.reserve(fileSize);
        } catch(const std::filesystem::filesystem_error& e) {
            Log::error({e.what(), filePath});
            return false;
        }

        bool success = true;

        char readBuffer[1024];

        while (!file.eof()) {
            file.read(readBuffer, sizeof readBuffer);

            const size_t readCount
                = file.gcount() >= 0 ? static_cast<size_t>(file.gcount()) : 0;

            fileContent.append(readBuffer, readCount);

            if (file.bad()) {
                Log::error({"File handling error.", filePath});
                success = false;
                break;
            }
        }

        if (!success) {
            return false;
        }

        file.close();

        const FileContent::FileContentWithMeta fileContentWithMeta{
            fileContent, filePath};

        for (auto& diagnostic: m_diagnostics) {
            if (!diagnostic->check(fileContentWithMeta)) {
                success = false;
            }
        }

        return success;
    }

    bool Line::Ascii::check(const TextLineWithMeta& textLine) const
    {
        bool success = true;
        uint32_t columnNumber = 0;
        for (const char& c: textLine.textLine().text()) {
            columnNumber++;
            const bool ascii = (0x20 <= c && c <= 0x7E) ||
                               find(c).in('\t', '\n', '\r');
            if (!ascii) {
                success = false;
                Log::diagnostic({"Non-ASCII character.", textLine.fileName(),
                                 textLine.lineNumber(), columnNumber});
            }
        }
        return success;
    }

    FileContent::FileContentWithMeta::FileContentWithMeta(
            const std::string& fileContent,
            const std::string& fileName
    )
        : m_fileContent(fileContent)
        , m_fileName(fileName)
    {}

    const std::string& FileContent::FileContentWithMeta::fileContent() const
    {
        return m_fileContent;
    }

    const std::string& FileContent::FileContentWithMeta::fileName() const
    {
        return m_fileName;
    }

    bool Line::Utf8::check(const TextLineWithMeta& /*textLine*/) const
    {
        return false;
    }

    bool FileContent::Empty::check(
            const FileContent::FileContentWithMeta& fileContent) const
    {
        if (fileContent.fileContent().empty()) {
            Log::diagnostic({"File is empty.", fileContent.fileName()});
            return false;
        }
        return true;
    }

    void FileContent::Splitter::addDiagnostic(
            std::shared_ptr<Line::Base> diagnostic)
    {
        m_diagnostics.push_back(diagnostic);
    }

    bool FileContent::Splitter::check(
            const FileContent::FileContentWithMeta& fileContent) const
    {
        LineSplitter splitter{fileContent.fileContent()};

        bool success = true;

        for (uint32_t lineNumber = 1; !splitter.eof(); lineNumber++) {
            const auto line = splitter.getNextLine();

            TextLineWithMeta textLine{line, fileContent.fileName(), lineNumber};

            for (auto& diagnostic: m_diagnostics) {
                if (!diagnostic->check(textLine)) {
                    success = false;
                }
            }
        }

        return success;
    }

    Line::Ending::Ending(const LineEnding& lineEnding)
        : m_lineEnding_(lineEnding)
    {}

    bool Line::Ending::check(const TextLineWithMeta& textLine) const
    {
        const TextLine line = textLine.textLine();
        if (line.ending() != m_lineEnding_) {
            const auto message = boost::format("Line ending is %1%.")
                                 % line.ending().name();
            Log::diagnostic({message.str(), textLine.fileName(),
                             textLine.lineNumber()});
            return false;
        }

        return true;
    }

    Line::Length::Length(const uint32_t limit)
        : m_limit(limit)
    {}

    bool Line::Length::check(const TextLineWithMeta& textLine) const
    {
        const auto size = textLine.textLine().text().size();
        if (size > m_limit) {
            const auto message = boost::format("String too long (%1%).") % size;
            Log::diagnostic({message.str(), textLine.fileName(),
                             textLine.lineNumber()});
            return false;
        }

        return true;
    }

} // Diagnostics namespace
