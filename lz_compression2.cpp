#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <string>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool is_end_of_word;
    std::string value;

    TrieNode() : is_end_of_word(false) {}
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(const std::string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->is_end_of_word = true;
        node->value = word;
    }

    bool search(const std::string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }
        return node->is_end_of_word;
    }

    std::string getValue(const std::string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            node = node->children[ch];
        }
        return node->value;
    }
};

// Function to compress using Trie
std::vector<std::pair<int, std::string>> compress(const std::string& input) {
    Trie trie;
    std::vector<std::pair<int, std::string>> compressed;
    std::string current_sequence;
    int index = 0;

    for (char ch : input) {
        current_sequence += ch;
        if (!trie.search(current_sequence)) {
            trie.insert(current_sequence);
            if (current_sequence.length() > 1) {
                compressed.push_back({index, current_sequence});
            } else {
                compressed.push_back({index, std::string(1, ch)});
            }
            current_sequence = "";
            index++;
        }
    }

    // If there's any remaining sequence
    if (!current_sequence.empty()) {
        compressed.push_back({index, current_sequence});
    }

    return compressed;
}

// Function to decompress using Trie
std::string decompress(const std::vector<std::pair<int, std::string>>& compressed) {
    Trie trie;
    std::string decompressed;
    std::string current_sequence;

    for (const auto& pair : compressed) {
        current_sequence = pair.second;
        if (!trie.search(current_sequence)) {
            trie.insert(current_sequence);
            decompressed += current_sequence;
        }
    }

    return decompressed;
}

int main() {
    std::ifstream input_file("input.txt");
    std::string input((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    input_file.close();

    auto compressed = compress(input);

    std::cout << "Compressed: ";
    for (const auto& pair : compressed) {
        std::cout << "(" << pair.first << ", " << pair.second << ")";
    }
    std::cout << std::endl;

    std::string decompressed = decompress(compressed);
    std::cout << "Decompressed: " << decompressed << std::endl;

    return 0;
}
