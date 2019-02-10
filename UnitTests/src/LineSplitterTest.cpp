#define BOOST_TEST_MODULE LineSplitterTest
#include <boost/test/included/unit_test.hpp>

#include "LineSplitter.hpp"
#include "LineEnding.hpp"
#include "TextLine.hpp"

BOOST_AUTO_TEST_CASE(SimpleTest)
{
    LineSplitter lineSplitter{"line1\nline2\n"};
    const auto line1 = lineSplitter.getNextLine();
    //BOOST_TEST(line1.text() == "line1");
    const auto& lineEnding{line1.lineEnding()};
    BOOST_TEST(lineEnding == LineEnding::crlf);
}
