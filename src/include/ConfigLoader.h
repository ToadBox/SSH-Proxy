#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <variant>

class ConfigLoader {
private:
    std::map<std::string, std::map<std::string, std::variant<int, std::string>>> configs;

public:
    ConfigLoader(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        std::string currentClass;
        while (std::getline(file, line)) {
            if (line[0] == '[') {
                currentClass = line.substr(1, line.size() - 2);
            } else {
                std::istringstream is_line(line);
                std::string key;
                if (std::getline(is_line, key, '=')) {
                    std::string value;
                    if (std::getline(is_line, value)) {
                        if (value.find_first_not_of("0123456789") == std::string::npos) {
                            configs[currentClass][key] = std::stoi(value);
                        } else {
                            configs[currentClass][key] = value;
                        }
                    }
                }
            }
        }
    }

    std::variant<int, std::string> getConfig(const std::string& className, const std::string& key) const {
        auto it = configs.find(className);
        if (it != configs.end()) {
            auto it2 = it->second.find(key);
            if (it2 != it->second.end()) {
                return it2->second;
            }
        }
        return "";
    }
};