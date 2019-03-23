#ifndef H_ED39819A_A400_4A1C_80F9_04C8BB39D587
#define H_ED39819A_A400_4A1C_80F9_04C8BB39D587

#include "AFileStream.hpp"

class FileStreamFromArgs: public AFileStream
{
public:
    explicit FileStreamFromArgs(const std::vector<std::string>& files);
    void run() override;

private:
    const std::vector<std::string>& m_files;
};

#endif // H_ED39819A_A400_4A1C_80F9_04C8BB39D587
