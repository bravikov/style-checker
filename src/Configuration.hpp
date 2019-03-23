#ifndef H_FB522AD0_CD80_4BA0_8980_D876F9415AB0
#define H_FB522AD0_CD80_4BA0_8980_D876F9415AB0

#include <memory>
#include <vector>

namespace boost {
namespace program_options {

class options_description;

}
}

namespace StyleChecker {

class Configuration
{
public:
    Configuration(const int argc, const char* const argv[]);

    std::string helpMessage() const;

    bool help() const;
    size_t jobs() const;
    const std::vector<std::string>& files() const;

private:
    std::string m_programName;
    std::string m_optionsHelp;
    bool m_help{false};
    size_t m_jobs{1};
    std::vector<std::string> m_files;
};

} // namespace StyleChecker

#endif // H_FB522AD0_CD80_4BA0_8980_D876F9415AB0
