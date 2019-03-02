#ifndef H_4610B2FF_7CC0_4412_A3AB_ED31B50BB20B
#define H_4610B2FF_7CC0_4412_A3AB_ED31B50BB20B

#include <string_view>
#include <vector>

class LineEnding
{
public:
    std::size_t size() const;
    char operator[](const std::size_t position) const;
    std::string_view view() const;
    std::string escaped() const;

    static const LineEnding none;
    static const LineEnding lf; // Unix-like
    static const LineEnding crlf; // Windows
    static const LineEnding cr;
    static const LineEnding lfcr;

    static const std::vector<LineEnding*>& collection();

    bool operator==(const LineEnding& other) const;

private:
    explicit LineEnding(const char* charSequence);
    LineEnding(const LineEnding& other) = delete;
    LineEnding(LineEnding&& other) = delete;
    LineEnding& operator=(const LineEnding& other) = delete;
    LineEnding& operator=(LineEnding&& other) = delete;
    std::string_view m_chars;
    static std::vector<LineEnding*> m_lineEndings;
};

std::ostream& operator<<(std::ostream& os, const LineEnding& le);

#endif /* H_4610B2FF_7CC0_4412_A3AB_ED31B50BB20B */
