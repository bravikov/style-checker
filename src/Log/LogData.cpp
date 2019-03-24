#include "LogData.hpp"

#include <unordered_map>
#include <type_traits>

LogData::LogData(
    const std::string& message,
    const std::optional<std::string>& fileName,
    const std::optional<uint32_t>& lineNumber,
    const std::optional<uint32_t>& columnNumber
)
    : message(message)
    , fileName(fileName)
    , lineNumber(lineNumber)
    , columnNumber(columnNumber)
{}

const std::string& LogData::typeName(const Type type)
{
    using Key = std::underlying_type<Type>::type;
    static const std::unordered_map<Key, std::string> names{
        {Diagnostic, "diagnostic"},
        {Error, "error"},
    };

    return names.at(type);
}
