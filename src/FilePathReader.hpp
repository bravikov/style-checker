#ifndef H_D68A79D7_51F3_46E1_8F6B_D02D83122A4D
#define H_D68A79D7_51F3_46E1_8F6B_D02D83122A4D

#include <string>

class AFileStreamReader;

class FilePathReader
{
public:
    explicit FilePathReader(AFileStreamReader* fileStream);
    bool next();
    std::string filePath() const;

private:
    AFileStreamReader* m_fileStream{nullptr};
    std::string m_filePath;
};

#endif // H_D68A79D7_51F3_46E1_8F6B_D02D83122A4D
