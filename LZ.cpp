#include <iostream>
#include <vector>
#include <string>
#include <utility>

class LZ {
public:
    // Compress the input string and return the compressed output
    std::vector<std::pair<int, int>> comprimir(const std::string& input) {
        std::vector<std::pair<int, int>> output;
        int i = 0;

        while (i < static_cast<int>(input.size())) {
            int matchLength = 0;
            int matchPosition = -1;

            // Find the longest match in the previous part of the string
            for (int j = 0; j < i; ++j) {
                int length = 0;
                while (i + length < static_cast<int>(input.size()) && input[j + length] == input[i + length]) {
                    ++length;
                    if (j + length >= i) break; // prevent overlap
                }
                if (length > matchLength) {
                    matchLength = length;
                    matchPosition = j;
                }
            }

            if (matchLength > 0) {
                output.push_back({matchPosition, matchLength});
                i += matchLength;
            } else {
                output.push_back({static_cast<int>(input[i]), 0});
                ++i;
            }
        }

        return output;
    }

    // Decompress the input vector of pairs and return the decompressed string
    std::string descomprimir(const std::vector<std::pair<int, int>>& input) {
        std::string output;

        for (const auto& entry : input) {
            int index = entry.first;
            int length = entry.second;

            if (length == 0) {
                output += static_cast<char>(index);
            } else {
                output += output.substr(index, length);
            }
        }

        return output;
    }
};
