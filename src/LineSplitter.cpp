#include "LineSplitter.hpp"
#include "LineEnding.hpp"
#include "TextLine.hpp"

LineSplitter::LineSplitter(const std::string_view text): m_text(text)
{
}

TextLine LineSplitter::getNextLine() const
{
    return TextLine("asdf", LineEnding::lf);
}

std::once_flag LineSplitter::lineEndingTreeInitFlag;

void LineSplitter::initializeLineEndingTree(Tree<char> &tree)
{
    const auto& lineEndings = LineEnding::collection();
    for (const LineEnding* lineEnding: lineEndings)
    {
        Tree<char>* node = &tree;
        for (size_t i = 0; lineEnding->size(); ++i) {
            const char key = (*lineEnding)[i];
            Tree<char>* child = node->getChild(key);
            if (child == nullptr) {
                node = child->addChild(key);
            }
            else {
                node = child;
            }
        }
    }
}

const Tree<char>& LineSplitter::getLineEndingTree()
{
    static Tree<char> lineEndingTree;
    std::call_once(LineSplitter::lineEndingTreeInitFlag,
                   &LineSplitter::initializeLineEndingTree,
                   lineEndingTree);
    return lineEndingTree;
}
