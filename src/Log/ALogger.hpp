#pragma once
#ifndef H_BF23225E_F533_492F_978F_2B5C831893E6
#define H_BF23225E_F533_492F_978F_2B5C831893E6

#include "LogData.hpp"

class ALogger
{
public:
    virtual ~ALogger() = default;
    virtual void log(LogData::Type type, const LogData& logData) = 0;
};

#endif /* #ifndef H_BF23225E_F533_492F_978F_2B5C831893E6 */
