#include "Configuration.hpp"

#include <boost/program_options.hpp>
namespace bpo = boost::program_options;

#include <iostream>
#include <filesystem>

StyleChecker::Configuration::Configuration(const int argc,
                                           const char * const argv[])
    : m_programName{argv[0]}
{
    bpo::options_description optionsDescription{"Options"};
    optionsDescription.add_options()
            ("help,h", "produce help message")
            ("jobs,j", bpo::value<size_t>(&m_jobs)->default_value(1),
             "specifies the number of jobs to run simultaneously")
            ;

    std::ostringstream ss;
    optionsDescription.print(ss);
    m_optionsHelp = ss.str();

    bpo::options_description hiddenOptionsDescription("Hidden options");
    hiddenOptionsDescription.add_options()
            ("input-file", bpo::value<std::vector<std::string>>(),
                "input file")
            ;

    bpo::positional_options_description positionalOptionsDescription;
    positionalOptionsDescription.add("input-file", -1);

    bpo::options_description allOptionsDescription;
    allOptionsDescription
            .add(optionsDescription)
            .add(hiddenOptionsDescription);

    bpo::variables_map optionsMap;

    bpo::store(
        bpo::command_line_parser(argc, argv)
                .options(allOptionsDescription)
                .positional(positionalOptionsDescription).run(),
        optionsMap
    );
    bpo::notify(optionsMap);

    if (optionsMap.count("help")) {
        m_help = true;
    }

    m_files = optionsMap["input-file"].as<std::vector<std::string>>();
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

const std::vector<std::string>&StyleChecker::Configuration::files() const
{
    return m_files;
}
