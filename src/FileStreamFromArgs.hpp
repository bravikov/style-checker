#ifndef H_ED39819A_A400_4A1C_80F9_04C8BB39D587
#define H_ED39819A_A400_4A1C_80F9_04C8BB39D587

#include "AFileStream.hpp"

class FileStreamFromArgs: public AFileStream
{
public:
    FileStreamFromArgs(const char* argv[], const size_t count);
    void run() override;
};

#endif // H_ED39819A_A400_4A1C_80F9_04C8BB39D587
