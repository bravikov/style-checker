cmake_minimum_required(VERSION 3.10)

project(UnitTests)

set(STYLE_CHECKER_SRC_DIR ../src)

set(STYLE_CHECKER_SRC
    ${STYLE_CHECKER_SRC_DIR}/LineSplitter.cpp
    ${STYLE_CHECKER_SRC_DIR}/LineSplitter.hpp
    ${STYLE_CHECKER_SRC_DIR}/LineEnding.cpp
    ${STYLE_CHECKER_SRC_DIR}/LineEnding.hpp
    ${STYLE_CHECKER_SRC_DIR}/TextLine.hpp
    ${STYLE_CHECKER_SRC_DIR}/TextLine.cpp
)

add_executable(unit-tests
    ${STYLE_CHECKER_SRC}
    src/LineSplitterTest.cpp
)

set_property(TARGET unit-tests PROPERTY CXX_STANDARD 17)
target_compile_options(unit-tests PRIVATE -Werror -Wall -Wextra -Wpedantic)

include_directories(
    ../src
)
