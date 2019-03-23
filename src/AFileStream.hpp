#ifndef H_9661078C_F3C6_4F2F_88DD_12B4EDDD40A8
#define H_9661078C_F3C6_4F2F_88DD_12B4EDDD40A8

#include "AFileStreamReader.hpp"

#include <string>
#include <queue>
#include <mutex>
#include <atomic>

class AFileStream: public AFileStreamReader
{
public:
    virtual void run() = 0;

    std::string getNextFilePath() override;
    bool ended() const override;

protected:
    void addFile(const std::string& filePath);
    void setEnd();

private:
    std::queue<std::string> m_queue;
    std::mutex m_queueMutex;
    std::atomic<bool> m_end{false};
};

#endif // H_9661078C_F3C6_4F2F_88DD_12B4EDDD40A8
