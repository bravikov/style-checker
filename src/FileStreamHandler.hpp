#ifndef H_0BFCEB97_B801_40F2_B2E5_41B547D6098E
#define H_0BFCEB97_B801_40F2_B2E5_41B547D6098E

#include <thread>
#include <atomic>

class AFileStreamReader;

class FileStreamHandler
{
public:
    FileStreamHandler(
        AFileStreamReader* fileStreamReader,
        const size_t maxThreadCount);

    void wait();

private:
    AFileStreamReader* m_fileStreamReader{nullptr};
    const size_t m_maxThreadCount{1};
    std::atomic_size_t m_threadCount{0};

    void handler();
};

class FileHandler
{
public:
    explicit FileHandler(const std::string& filePath);
};

#endif // H_0BFCEB97_B801_40F2_B2E5_41B547D6098E
