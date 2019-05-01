#ifndef H_9ED4EDBC_6B7C_11E9_9B15_D050992FEDBB
#define H_9ED4EDBC_6B7C_11E9_9B15_D050992FEDBB

#include "TextLine.hpp"
#include "LineEnding.hpp"

#include <string>
#include <memory>
#include <list>

namespace Diagnostics
{
    template<typename Subject>
    class Base
    {
    public:
        virtual ~Base() {}
        virtual bool check(const Subject& subject) const = 0;
    };

    namespace Line
    {
        class Base: public Diagnostics::Base<TextLineWithMeta> {};

        class Ending: public Base
        {
        public:
            explicit Ending(const LineEnding& lineEnding);
            bool check(const TextLineWithMeta& textLine) const override;

        private:
            const LineEnding& m_lineEnding_;
        };

        class Length: public Base
        {
        public:
            explicit Length(const uint32_t limit);
            bool check(const TextLineWithMeta& textLine) const override;

        private:
            uint32_t m_limit;
        };

        class Ascii: public Base
        {
        public:
            bool check(const TextLineWithMeta& textLine) const override;
        };

        class Utf8: public Base
        {
        public:
            bool check(const TextLineWithMeta& textLine) const override;
        };

    } // Line namespace

    namespace FileContent
    {
        class FileContentWithMeta
        {
        public:
            FileContentWithMeta(const std::string& fileContent,
                                const std::string& fileName);
            const std::string& fileContent() const;
            const std::string& fileName() const;

        private:
            const std::string& m_fileContent;
            const std::string& m_fileName;
        };

        class Base: public Diagnostics::Base<FileContentWithMeta> {};

        class Empty: public Base
        {
        public:
            bool check(const FileContentWithMeta& fileContent) const override;
        };

        class Splitter: public Base
        {
        public:
            void addDiagnostic(std::shared_ptr<Line::Base> diagnostic);
            bool check(const FileContentWithMeta& fileContent) const override;

        private:
            std::list<std::shared_ptr<Line::Base>> m_diagnostics;
        };
    } // FileContent namespace

    namespace File
    {
        class Base: public Diagnostics::Base<std::string> {};

        class Reader: public Base
        {
        public:
            void addDiagnostic(std::shared_ptr<FileContent::Base> diagnostic);
            bool check(const std::string& filePath) const override;

        private:
            std::list<std::shared_ptr<FileContent::Base>> m_diagnostics;
        };
    } // File namespace
} // Diagnostic namespace

#endif // H_9ED4EDBC_6B7C_11E9_9B15_D050992FEDBB
