#include <iostream>
#include <fstream>
#include <ctime>

class Logger {
public:
    void info(const std::string& message, bool writeToFile = false) {
        log("\033[32m[INFO] ", message, writeToFile);
    }

    void warning(const std::string& message, bool writeToFile = false) {
        log("\033[33m[WARNING] ", message, writeToFile);
    }

    void error(const std::string& message, bool writeToFile = false) {
        log("\033[31m[ERROR] ", message, writeToFile);
    }

private:
    void log(const std::string& prefix, const std::string& message, bool writeToFile) {
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
                std::cerr << "\033[31m[ERROR] Failed to open log file: " << filename << "\033[0m" << std::endl;
                return;
            }
            logFile << prefix << safeMessage << std::endl;
        }
    }
};