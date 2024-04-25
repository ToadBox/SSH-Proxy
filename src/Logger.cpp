#include "Logger.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <thread>
#include <algorithm>

void Logger::info(const std::string& message, bool writeToFile) {
    log("\033[32m[INFO] ", message, writeToFile);
}

void Logger::warning(const std::string& message, bool writeToFile) {
    log("\033[33m[WARNING] ", message, writeToFile);
}

void Logger::error(const std::string& message, bool writeToFile) {
    log("\033[31m[ERROR] ", message, writeToFile);
}

void Logger::debug(const std::string& message, bool writeToFile) {
    log("\033[34m[DEBUG] ", message, writeToFile);
}

void Logger::critical(const std::string& message, bool writeToFile) {
    log("\033[31m[CRITICAL] ", message, writeToFile);
    // Flash the screen red 3 times and exit
    for (int i = 0; i < 3; i++) {
        std::cout << "\033[41m";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "\033[0m";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    exit(1);
}

void Logger::log(const std::string& prefix, const std::string& message, bool writeToFile) {
    std::string safeMessage = message;
    std::replace_if(safeMessage.begin(), safeMessage.end(), [](char c) { return !std::isalnum(c); }, '_');

    std::cout << prefix << safeMessage << "\033[0m" << std::endl;

    if (writeToFile) {
        std::time_t t = std::time(nullptr);
        char date[10];
        std::strftime(date, sizeof(date), "%d-%m-%Y", std::localtime(&t));
        std::string filename = std::string(date) + "-log.txt";

        std::ofstream logFile(filename, std::ios_base::app);
        if (!logFile) {
            std::cerr << "\033[31m[CRITICAL] Failed to open log file: " << filename << "\033[0m" << std::endl;
            return;
        }
        logFile << prefix << safeMessage << std::endl;
    }
}