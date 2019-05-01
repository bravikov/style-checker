cmake_minimum_required(VERSION 3.10)

project(StyleChecker VERSION 0.0.1)


set(TEXT_FILES
    CONTRIBUTING.md
    LICENSE.md
    README.md
    TODO.md
)

add_executable(style-checker
    ${TEXT_FILES}
    src/main.cpp
    src/AFileStreamReader.hpp
    src/AFileStream.hpp
    src/AFileStream.cpp
    src/FileStreamFromInput.hpp
    src/FileStreamFromInput.cpp
    src/FilePathReader.hpp
    src/FilePathReader.cpp
    src/FileStreamHandler.hpp
    src/FileStreamHandler.cpp
    src/FileStreamFromArgs.hpp
    src/FileStreamFromArgs.cpp
    src/Configuration.hpp
    src/Configuration.cpp
    src/LineEnding.hpp
    src/LineEnding.cpp
    src/Tree.hpp
    src/LineSplitter.hpp
    src/LineSplitter.cpp
    src/TextLine.hpp
    src/TextLine.cpp
    src/Diagnostics.hpp
    src/Diagnostics.cpp
    src/Algorithm.hpp

    src/Log/ALogger.hpp
    src/Log/ConsoleLogger.hpp
    src/Log/ConsoleLogger.cpp
    src/Log/LogData.hpp
    src/Log/LogData.cpp
    src/Log/Log.hpp
    src/Log/Log.cpp
)

set_property(TARGET style-checker PROPERTY CXX_STANDARD 17)
target_compile_options(style-checker PRIVATE -Werror -Wall -Wextra -Wpedantic)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(style-checker Threads::Threads)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED program_options)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(style-checker ${Boost_LIBRARIES})

target_link_libraries(style-checker stdc++fs)

add_subdirectory(UnitTests)
