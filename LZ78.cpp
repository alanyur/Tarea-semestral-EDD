#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

class LZ78 {
public:
    // Compress the input string and return the compressed output
    std::vector<std::pair<int, char>> compress(const std::string& input) {
        std::unordered_map<std::string, int> dictionary;
        std::vector<std::pair<int, char>> output;

        std::string currentString;
        int dictSize = 1;

        for (char ch : input) {
            currentString += ch;
            if (dictionary.find(currentString) == dictionary.end()) {
                if (currentString.length() == 1) {
                    output.push_back({0, ch});
                } else {
                    std::string prefix = currentString.substr(0, currentString.length() - 1);
                    output.push_back({dictionary[prefix], ch});
                }
                dictionary[currentString] = dictSize++;
                currentString.clear();
            }
        }

        // Handle the last string if it exists
        if (!currentString.empty()) {
            std::string prefix = currentString.substr(0, currentString.length() - 1);
            output.push_back({dictionary[prefix], currentString.back()});
        }

        return output;
    }

    // Decompress the input and return the original string
    std::string decompress(const std::vector<std::pair<int, char>>& input) {
        std::unordered_map<int, std::string> dictionary;
        std::string output;
        int dictSize = 1;

        for (const auto& entry : input) {
            int index = entry.first;
            char ch = entry.second;

            if (index == 0) {
                output += ch;
                dictionary[dictSize++] = std::string(1, ch);
            } else {
                std::string prefix = dictionary[index];
                std::string newString = prefix + ch;
                output += newString;
                dictionary[dictSize++] = newString;
            }
        }

        return output;
    }
};

