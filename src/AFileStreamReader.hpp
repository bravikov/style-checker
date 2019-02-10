#ifndef H_4767D95E_38D2_42B4_A584_3B9D43A3C106
#define H_4767D95E_38D2_42B4_A584_3B9D43A3C106

#include <string>

class AFileStreamReader
{
public:
    virtual ~AFileStreamReader() = default;
    virtual std::string getNextFilePath() = 0;
    virtual bool ended() const = 0;
};

#endif // H_4767D95E_38D2_42B4_A584_3B9D43A3C106
