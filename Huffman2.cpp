#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <chrono>

using namespace std;

struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int frequency) {
        left = right = nullptr;
        this->data = data;
        this->frequency = frequency;
    }
};

// Comparator to be used in priority queue
struct compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return (l->frequency > r->frequency);
    }
};

class HuffmanCoding {
public:
    unordered_map<char, string> huffmanCode;
    HuffmanNode* root;

    HuffmanCoding() {
        root = nullptr;
    }

    ~HuffmanCoding() {
        freeTree(root);
    }

    string codificar(string text) {
        root = buildHuffmanTree(text);
        generateCodes(root, "", huffmanCode);
        return encode(text, huffmanCode);
    }

    string decodificar(string encodedString) {
        return decode(root, encodedString);
    }

private:
    HuffmanNode* buildHuffmanTree(string text) {
        unordered_map<char, int> freq;
        for (char ch : text) {
            freq[ch]++;
        }

        priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> minHeap;
        for (auto pair : freq) {
            minHeap.push(new HuffmanNode(pair.first, pair.second));
        }

        while (minHeap.size() != 1) {
            HuffmanNode* left = minHeap.top();
            minHeap.pop();
            HuffmanNode* right = minHeap.top();
            minHeap.pop();

            HuffmanNode* top = new HuffmanNode('$', left->frequency + right->frequency);
            top->left = left;
            top->right = right;
            minHeap.push(top);
        }

        return minHeap.top();
    }

    void generateCodes(HuffmanNode* root, string str, unordered_map<char, string>& huffmanCode) {
        if (!root)
            return;

        if (root->data != '$')
            huffmanCode[root->data] = str;

        generateCodes(root->left, str + "0", huffmanCode);
        generateCodes(root->right, str + "1", huffmanCode);
    }

    string encode(string text, unordered_map<char, string>& huffmanCode) {
        stringstream encodedStream;
        for (char ch : text) {
            encodedStream << huffmanCode[ch];
        }
        return encodedStream.str();
    }

    string decode(HuffmanNode* root, string encodedString) {
        string decodedString = "";
        HuffmanNode* current = root;
        for (int i = 0; i < encodedString.size(); i++) {
            if (encodedString[i] == '0')
                current = current->left;
            else
                current = current->right;

            if (!current->left && !current->right) {
                decodedString += current->data;
                current = root;
            }
        }
        return decodedString;
    }

    void freeTree(HuffmanNode* node) {
        if (node == nullptr) return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }
};
