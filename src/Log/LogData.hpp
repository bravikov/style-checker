#pragma once
#ifndef H_41CE4231_AB99_4BCF_92FA_5353A32A4A4F
#define H_41CE4231_AB99_4BCF_92FA_5353A32A4A4F

#include <optional>
#include <thread>

struct LogData
{
    enum Type {Diagnostic, Error};

    static const std::string& typeName(Type type);

    LogData(
        const std::string& message,
        const std::optional<std::string>& fileName = std::nullopt,
        const std::optional<uint32_t>& lineNumber = std::nullopt,
        const std::optional<uint32_t>& columnNumber = std::nullopt
    );

    std::string message;
    std::optional<std::string> fileName;
    std::optional<uint32_t> lineNumber;
    std::optional<uint32_t> columnNumber;
};

#endif /* #ifndef H_41CE4231_AB99_4BCF_92FA_5353A32A4A4F */
