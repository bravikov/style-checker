#ifndef H_7A2432C3_E500_46BD_B691_B13A0B106D18
#define H_7A2432C3_E500_46BD_B691_B13A0B106D18

#include "LineEnding.hpp"
#include <string>

class TextLine
{
public:
    TextLine(const std::string& text, const LineEnding& lineEnding);

    const std::string& text() const;

    const LineEnding& lineEnding() const;

private:
    std::string m_text;
    const LineEnding* m_lineEnding;
};

#endif /* #ifndef H_7A2432C3_E500_46BD_B691_B13A0B106D18 */