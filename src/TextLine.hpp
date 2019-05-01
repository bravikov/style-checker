#ifndef H_7A2432C3_E500_46BD_B691_B13A0B106D18
#define H_7A2432C3_E500_46BD_B691_B13A0B106D18

#include "LineEnding.hpp"
#include <string>

class TextLine
{
public:
    explicit TextLine(const std::string& text,
                      const LineEnding& ending = LineEnding::none);

    const std::string& text() const;
    const LineEnding& ending() const;
    explicit operator bool() const noexcept;

private:
    std::string m_text;
    const LineEnding& m_ending{LineEnding::none};
};

struct TextLineWithMeta
{
public:
    TextLineWithMeta(const TextLine& textLine,
                     const std::string& fileName,
                     const uint32_t lineNumber);

    const TextLine& textLine() const;
    const std::string& fileName() const;
    uint32_t lineNumber() const;

private:
    const TextLine& m_textLine;
    const std::string& m_fileName;
    const uint32_t m_lineNumber;
};

#endif /* #ifndef H_7A2432C3_E500_46BD_B691_B13A0B106D18 */
