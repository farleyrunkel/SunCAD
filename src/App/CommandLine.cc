// Copyright [2024] SunCAD

#include "App/CommandLine.h"

#include <iostream>
#include <string>

namespace sun 
{
    CommandLine::CommandLine(int argc, char* argv[])
        : _Options(argv[0], " - Command line options") {
        try {
            // Define mOptions
            _Options.add_options()
                ("sandbox", "Enable sandbox", cxxopts::value<bool>(_EnableSandbox)->default_value("false"))
                ("nowelcome", "Disable welcome", cxxopts::value<bool>(_NoWelcomeDialog)->default_value("false"))
                ("runscript", "Script to run", cxxopts::value<std::string>(_ScriptToRun))
                ("input", "Path to open", cxxopts::value<std::string>(_PathToOpen))
                ("help", "Show help");

            // Parse mOptions
            auto result = _Options.parse(argc, argv);

            // Show help if requested
            if (result.count("help")) {
                std::cout << _Options.help() << std::endl;
                return;  // Use return instead of exit
            }

            // Set path if unmatched arguments exist
            if (!result.unmatched().empty()) {
                _PathToOpen = result.unmatched().at(0);
            }
        } catch (const cxxopts::exceptions::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return;  // Use return instead of exit
        }
    }
}