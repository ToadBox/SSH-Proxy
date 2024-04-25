#include <string>

class Logger {
public:
    void info(const std::string& message, bool writeToFile = false);
    void warning(const std::string& message, bool writeToFile = false);
    void error(const std::string& message, bool writeToFile = false);
    void debug(const std::string& message, bool writeToFile = false);
    void critical(const std::string& message, bool writeToFile = false);

private:
    void log(const std::string& prefix, const std::string& message, bool writeToFile);
};