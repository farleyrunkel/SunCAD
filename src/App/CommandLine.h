// Copyright [2024] SunCAD

#ifndef APP_COMMANDLINE_H
#define APP_COMMANDLINE_H

#include <iostream>
#include <string>

#include <cxxopts.hpp>

namespace sun 
{
    class CommandLine
    {
    public:
        CommandLine(int argc, char* argv[]);

        bool IsSandboxEnabled() const {
            return _EnableSandbox;
        }
        bool IsWelcomeDialogDisabled() const {
            return _NoWelcomeDialog;
        }
        bool HasPathToOpen() const {
            return !_PathToOpen.empty();
        }
        bool HasScriptToRun() const {
            return !_ScriptToRun.empty();
        }

    private:
        bool _EnableSandbox = false;      // Sandbox mode
        bool _NoWelcomeDialog = false;    // Welcome status
        std::string _PathToOpen;          // Path to open
        std::string _ScriptToRun;         // Script to run

    private:
        cxxopts::Options _Options;
    };
}
#endif // APP_COMMANDLINE_H
