#include "TextLine.hpp"

#include <stdexcept>

TextLine::TextLine(const std::string& text, const LineEnding& ending)
    : m_text{text}
    , m_ending{ending}
{
}

const std::string& TextLine::text() const
{
    return m_text;
}

const LineEnding& TextLine::ending() const
{
    return m_ending;
}

TextLine::operator bool() const noexcept
{
    return !m_text.empty() || m_ending == LineEnding::none;
}

TextLineWithMeta::TextLineWithMeta(const TextLine& textLine,
                                   const std::string& fileName,
                                   const uint32_t lineNumber)
    : m_textLine(textLine)
    , m_fileName(fileName)
    , m_lineNumber(lineNumber)
{}

const TextLine&TextLineWithMeta::textLine() const
{
    return m_textLine;
}

const std::string& TextLineWithMeta::fileName() const
{
    return m_fileName;
}

uint32_t TextLineWithMeta::lineNumber() const
{
    return m_lineNumber;
}
