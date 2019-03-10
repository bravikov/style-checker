#include "LineEnding.hpp"

#include <iostream>
#include <map>

std::vector<LineEnding*> LineEnding::m_lineEndings;

const LineEnding LineEnding::none("");
const LineEnding LineEnding::lf("\n");
const LineEnding LineEnding::crlf{"\r\n"};
const LineEnding LineEnding::cr{"\r"};
const LineEnding LineEnding::lfcr{"\n\r"};

LineEnding::LineEnding(const char *charSequence)
    : m_chars{charSequence}
{
    if (m_chars.empty()) {
        return;
    }
    LineEnding::m_lineEndings.push_back(this);
}

std::size_t LineEnding::size() const
{
    return m_chars.size();
}

char LineEnding::operator[](const std::size_t position) const
{
    return m_chars[position];
}

std::string_view LineEnding::view() const
{
    return m_chars;
}

std::string LineEnding::name() const
{
    if (this == &none) {
        return "none";
    }

    const std::map<char, std::string> replaces{
        {'\n', "\\n"},
        {'\r', "\\r"},
    };

    std::string v;
    v.reserve(m_chars.size());
    for (const char& c: m_chars) {
        v += replaces.at(c);
    }
    return v;
}

const std::vector<LineEnding*>& LineEnding::collection()
{
    return LineEnding::m_lineEndings;
}

bool LineEnding::operator==(const LineEnding& other) const
{
    return this == &other;
}

bool LineEnding::operator!=(const LineEnding& other) const
{
    return this != &other;
}


std::ostream& operator<<(std::ostream& os, const LineEnding& le)
{
    return os << le.name();
}
