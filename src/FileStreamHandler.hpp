#ifndef H_0BFCEB97_B801_40F2_B2E5_41B547D6098E
#define H_0BFCEB97_B801_40F2_B2E5_41B547D6098E

#include "Diagnostics.hpp"

#include <thread>
#include <atomic>

class AFileStreamReader;

class FileStreamHandler
{
public:
    using Diag = std::shared_ptr<Diagnostics::File::Base>;
    using DiagList = std::shared_ptr<std::list<Diag>>;

    FileStreamHandler(AFileStreamReader* fileStreamReader,
                      const size_t maxThreadCount,
                      DiagList diagnostics);

    void wait();

    bool diagnosticsSuccess() const;

private:
    AFileStreamReader* m_fileStreamReader{nullptr};
    const size_t m_maxThreadCount{1};
    std::atomic_size_t m_threadCount{0};
    DiagList m_diagnostics;
    bool m_diagnosticsSuccess = true;

    void handler();
};

#endif // H_0BFCEB97_B801_40F2_B2E5_41B547D6098E
