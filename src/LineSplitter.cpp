#include "LineSplitter.hpp"
#include "LineEnding.hpp"
#include "TextLine.hpp"

void LineSplitter::initializeLineEndingTree(LineEndingTree& tree)
{
    const auto& lineEndings = LineEnding::collection();
    for (const LineEnding* lineEnding: lineEndings)
    {
        LineEndingTree* node = &tree;
        for (const char key: lineEnding->view()) {
            LineEndingTree* child = node->getChild(key);
            if (child == nullptr) {
                child = node->addChild(key, nullptr);
            }
            node = child;
        }
        node->setData(lineEnding);
    }
}

LineSplitter::LineSplitter(const std::string_view text)
    : m_text{text}
    , m_iterator{text.begin()}
    , m_eof{m_iterator == m_text.end()}
{}

TextLine LineSplitter::getNextLine()
{
    auto setEofIfEnd = [this] {
        if (m_iterator == m_text.end()) {
            m_eof = true;
        }
    };

    const LineEndingTree& tree = getLineEndingTree();
    const auto lineBegin = m_iterator;
    for (; m_iterator != m_text.end(); ++m_iterator) {
        const LineEndingTree* child = tree.getChild(*m_iterator);
        if (!child) {
            continue;
        }
        const auto lineEnd = m_iterator;
        for (++m_iterator; m_iterator != m_text.end(); ++m_iterator) {
            const LineEndingTree* tempChild = child->getChild(*m_iterator);
            if (tempChild) {
                child = tempChild;
                continue;
            }
            const LineEnding* lineEnding = child->getData();
            if (lineEnding) {
                const std::string line{lineBegin, lineEnd};
                return TextLine{line, *lineEnding};
            }
            break;
        }
        setEofIfEnd();
        const LineEnding* lineEnding = child->getData();
        if (lineEnding) {
            const std::string line{lineBegin, lineEnd};
            return TextLine{line, *lineEnding};
        }
        break;
    }
    setEofIfEnd();
    const auto lineEnd = m_iterator;
    const std::string line{lineBegin, lineEnd};
    return TextLine{line};
}

bool LineSplitter::eof() const
{
    return m_eof;
}

const LineSplitter::LineEndingTree& LineSplitter::getLineEndingTree()
{
    static LineEndingTree lineEndingTree{nullptr, nullptr};
    static std::once_flag lineEndingTreeInitFlag;
    std::call_once(lineEndingTreeInitFlag,
                   LineSplitter::initializeLineEndingTree,
                   lineEndingTree);
    return lineEndingTree;
}
