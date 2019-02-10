#include "LineEnding.hpp"

#include <iostream>
#include <map>

std::vector<LineEnding*> LineEnding::m_lineEndings;

const LineEnding LineEnding::lf("\n");
const LineEnding LineEnding::crlf{"\r\n"};
const LineEnding LineEnding::cr{"\r"};
const LineEnding LineEnding::lfcr{"\n\r"};

LineEnding::LineEnding(const char *charSequence)
    : m_charSequence{charSequence}
{
    LineEnding::m_lineEndings.push_back(this);
}

std::size_t LineEnding::size() const
{
    return m_charSequence.size();
}

char LineEnding::operator[](const std::size_t position) const
{
    return m_charSequence[position];
}

std::string LineEnding::escapedView() const
{
    const std::map<char, std::string> replaces{
        {'\n', "\\n"},
        {'\r', "\\r"},
    };

    std::string v;
    v.reserve(m_charSequence.size());
    for (const char& c: m_charSequence) {
        v += replaces.at(c);
    }
    return v;
}

const std::vector<LineEnding*>& LineEnding::collection()
{
    const auto& a = LineEnding::m_lineEndings;
    return a;
}

bool LineEnding::operator==(const LineEnding& other) const
{
    return this == &other;
}

std::ostream& operator<<(std::ostream& os, const LineEnding& le)
{
    return os << le.escapedView();
}
