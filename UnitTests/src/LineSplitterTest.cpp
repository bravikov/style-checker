#define BOOST_TEST_MODULE LineSplitterTest
#include <boost/test/included/unit_test.hpp>

#include "LineSplitter.hpp"
#include "LineEnding.hpp"
#include "TextLine.hpp"

BOOST_AUTO_TEST_CASE(EofInitializationTest)
{
    LineSplitter lineSplitter1{""};
    BOOST_TEST(lineSplitter1.eof() == true);

    LineSplitter lineSplitter2{"test"};
    BOOST_TEST(lineSplitter2.eof() == false);
}

BOOST_AUTO_TEST_CASE(EofAfter1LineWithoutEnding)
{
    LineSplitter lineSplitter{"test"};
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == true);
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == true);
}

BOOST_AUTO_TEST_CASE(EofAfter1LineWithEnding)
{
    LineSplitter lineSplitter{"test\n"};
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == true);
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == true);
}

BOOST_AUTO_TEST_CASE(EofAfter2LineWithoutEnding)
{
    LineSplitter lineSplitter{"test1\ntest2"};
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == false);
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == true);
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == true);
}

BOOST_AUTO_TEST_CASE(EofAfter2LineWithEnding)
{
    LineSplitter lineSplitter{"test1\ntest2\n"};
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == false);
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == true);
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == true);
}

BOOST_AUTO_TEST_CASE(EofAfter2LineWithEnding2)
{
    LineSplitter lineSplitter{"test1\r\ntest2\r\n"};
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == false);
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == true);
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == true);
}

BOOST_AUTO_TEST_CASE(EofAndOnlyLineEnding)
{
    LineSplitter lineSplitter{"\n"};
    BOOST_TEST(lineSplitter.eof() == false);
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == true);
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == true);
}

BOOST_AUTO_TEST_CASE(EofAndOnlyLineEnding2)
{
    LineSplitter lineSplitter{"\r\n"};
    BOOST_TEST(lineSplitter.eof() == false);
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == true);
    lineSplitter.getNextLine();
    BOOST_TEST(lineSplitter.eof() == true);
}

BOOST_AUTO_TEST_CASE(EmptyLine)
{
    LineSplitter lineSplitter{""};
    BOOST_TEST(lineSplitter.eof() == true);

    const auto line1 = lineSplitter.getNextLine();
    BOOST_TEST(line1.text() == "");
    BOOST_TEST(line1.ending() == LineEnding::none);

    const auto line2 = lineSplitter.getNextLine();
    BOOST_TEST(line2.text() == "");
    BOOST_TEST(line2.ending() == LineEnding::none);
}

BOOST_AUTO_TEST_CASE(LineWithoutEnding)
{
    LineSplitter lineSplitter{"test"};
    const auto line1 = lineSplitter.getNextLine();
    BOOST_TEST(line1.text() == "test");
    BOOST_TEST(line1.ending() == LineEnding::none);
    const auto line2 = lineSplitter.getNextLine();
    BOOST_TEST(line2.text() == "");
    BOOST_TEST(line2.ending() == LineEnding::none);
}

BOOST_AUTO_TEST_CASE(LineWithEnding1)
{
    LineSplitter lineSplitter{"test\n"};
    const auto line1 = lineSplitter.getNextLine();
    BOOST_TEST(line1.text() == "test");
    BOOST_TEST(line1.ending() == LineEnding::lf);
    const auto line2 = lineSplitter.getNextLine();
    BOOST_TEST(line2.text() == "");
    BOOST_TEST(line2.ending() == LineEnding::none);
}

BOOST_AUTO_TEST_CASE(LineWithEnding2)
{
    LineSplitter lineSplitter{"test\r\n"};
    const auto line1 = lineSplitter.getNextLine();
    BOOST_TEST(line1.text() == "test");
    BOOST_TEST(line1.ending() == LineEnding::crlf);
    const auto line2 = lineSplitter.getNextLine();
    BOOST_TEST(line2.text() == "");
    BOOST_TEST(line2.ending() == LineEnding::none);
}

BOOST_AUTO_TEST_CASE(OnlyLineEnding)
{
    LineSplitter lineSplitter{"\n"};
    const auto line1 = lineSplitter.getNextLine();
    BOOST_TEST(line1.text() == "");
    BOOST_TEST(line1.ending() == LineEnding::lf);
    const auto line2 = lineSplitter.getNextLine();
    BOOST_TEST(line2.text() == "");
    BOOST_TEST(line2.ending() == LineEnding::none);
}

BOOST_AUTO_TEST_CASE(OnlyLineEnding2)
{
    LineSplitter lineSplitter{"\r\n"};
    const auto line1 = lineSplitter.getNextLine();
    BOOST_TEST(line1.text() == "");
    BOOST_TEST(line1.ending() == LineEnding::crlf);
    const auto line2 = lineSplitter.getNextLine();
    BOOST_TEST(line2.text() == "");
    BOOST_TEST(line2.ending() == LineEnding::none);
}

BOOST_AUTO_TEST_CASE(ComplexTest)
{
    LineSplitter lineSplitter{" Line1 \n Line2 \r\n Line3 \n\r Line4 "};

    const auto line1 = lineSplitter.getNextLine();
    BOOST_TEST(line1.text() == " Line1 ");
    BOOST_TEST(line1.ending() == LineEnding::lf);

    const auto line2 = lineSplitter.getNextLine();
    BOOST_TEST(line2.text() == " Line2 ");
    BOOST_TEST(line2.ending() == LineEnding::crlf);

    const auto line3 = lineSplitter.getNextLine();
    BOOST_TEST(line3.text() == " Line3 ");
    BOOST_TEST(line3.ending() == LineEnding::lfcr);

    const auto line4 = lineSplitter.getNextLine();
    BOOST_TEST(line4.text() == " Line4 ");
    BOOST_TEST(line4.ending() == LineEnding::none);
}
