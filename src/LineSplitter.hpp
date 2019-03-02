#ifndef H_F6329F05_B0D4_4B11_A43D_8A09391A5856
#define H_F6329F05_B0D4_4B11_A43D_8A09391A5856

#include "Tree.hpp"
#include <mutex>

class TextLine;
class LineEnding;

class LineSplitter
{
public:
    explicit LineSplitter(const std::string_view text);

    TextLine getNextLine();
    bool eof() const;

private:
    const std::string_view m_text;
    std::string_view::const_iterator m_iterator;
    bool m_eof = true;

    using LineEndingTree = Tree<char, const LineEnding*>;
    static void initializeLineEndingTree(LineEndingTree& tree);
    static const LineEndingTree& getLineEndingTree();
};

#endif /* #ifndef H_F6329F05_B0D4_4B11_A43D_8A09391A5856 */
