#include "TextLine.hpp"


TextLine::TextLine(const std::string& text, const LineEnding& lineEnding)
    : m_text(text)
    , m_lineEnding(&lineEnding)
{
}

const std::string& TextLine::text() const
{
    return m_text;
}

const LineEnding& TextLine::lineEnding() const
{
    return *m_lineEnding;
}
