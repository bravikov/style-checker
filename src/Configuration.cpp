#include "Configuration.hpp"

#include <boost/program_options.hpp>
namespace BoostPO = boost::program_options;

#include <iostream>
#include <filesystem>

StyleChecker::Configuration::Configuration(const int argc,
                                           const char * const argv[])
    : m_programName{argv[0]}
{
    BoostPO::options_description optionsDescription{"Options"};
    optionsDescription.add_options()
            ("help,h", "produce help message")
            ("jobs,j", BoostPO::value<size_t>(&m_jobs)->default_value(1),
             "specifies the number of jobs to run simultaneously")
            ;

    std::ostringstream ss;
    optionsDescription.print(ss);
    m_optionsHelp = ss.str();

    BoostPO::options_description hiddenOptionsDescription("Hidden options");
    hiddenOptionsDescription.add_options()
            ("input-file", BoostPO::value<std::vector<std::string>>(),
                "input file")
            ;

    BoostPO::positional_options_description positionalOprionsDescription;
    positionalOprionsDescription.add("input-file", -1);

    BoostPO::options_description allOptionsDescription;
    allOptionsDescription
            .add(optionsDescription)
            .add(hiddenOptionsDescription);

    BoostPO::variables_map optionsMap;

    BoostPO::store(
        BoostPO::command_line_parser(argc, argv)
                .options(allOptionsDescription)
                .positional(positionalOprionsDescription).run(),
        optionsMap
    );
    BoostPO::notify(optionsMap);

    if (optionsMap.count("help")) {
        m_help = true;
    }
}

std::string StyleChecker::Configuration::helpMessage() const
{
    std::ostringstream ss;
    ss << "Usage:" << std::endl;
    const std::string programName
            = std::filesystem::path(m_programName).filename().native();
    const std::string arguments{" [options] [file ...]"};
    ss << "  " << programName << arguments << std::endl;
    ss << m_optionsHelp;
    return ss.str();
}

bool StyleChecker::Configuration::help() const
{
    return m_help;
}

size_t StyleChecker::Configuration::jobs() const
{
    return m_jobs;
}
