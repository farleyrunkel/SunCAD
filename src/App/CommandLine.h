// Copyright [2024] SunCAD

#ifndef SRC_APP_COMMANDLINE_H_
#define SRC_APP_COMMANDLINE_H_

#include <iostream>
#include <string>

#include <cxxopts.hpp>

class CommandLine {
 public:
    CommandLine(int argc, char* argv[]);

    bool isSandboxEnabled() const { return mEnableSandbox; }
    bool isWelcomeDialogDisabled() const { return mNoWelcomeDialog; }
    bool hasPathToOpen() const { return !mPathToOpen.empty(); }
    bool hasScriptToRun() const { return !mScriptToRun.empty(); }

 private:
    bool mEnableSandbox = false;      // Sandbox mode
    bool mNoWelcomeDialog = false;    // Welcome status
    std::string mPathToOpen;          // Path to open
    std::string mScriptToRun;         // Script to run

 private:
    cxxopts::Options mOptions;
};

#endif  // SRC_APP_COMMANDLINE_H_
