#ifndef H_F6329F05_B0D4_4B11_A43D_8A09391A5856
#define H_F6329F05_B0D4_4B11_A43D_8A09391A5856

#include "Tree.hpp"
#include <mutex>

class TextLine;

class LineSplitter
{
public:
    explicit LineSplitter(const std::string_view text);

    TextLine getNextLine() const;

private:
    const std::string_view m_text;

    static void initializeLineEndingTree(Tree<char>& tree);
    static std::once_flag lineEndingTreeInitFlag;
    static const Tree<char>& getLineEndingTree();
};

#endif /* #ifndef H_F6329F05_B0D4_4B11_A43D_8A09391A5856 */
