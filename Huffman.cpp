#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>

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

struct compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return (l->frequency > r->frequency);
    }
};

class HuffmanCoding {
public:
    unordered_map<char, string> huffmanCode;
    HuffmanNode* root;

    HuffmanCoding() : root(nullptr) {}

    ~HuffmanCoding() {
        freeTree(root);
    }

    string codificar(const string& text) {
        root = buildHuffmanTree(text);
        generateCodes(root, "");
        return encode(text);
    }

    string decodificar(const string& encodedString) {
        return decode(encodedString);
    }

private:
    HuffmanNode* buildHuffmanTree(const string& text) {
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

    void generateCodes(HuffmanNode* root, const string& str) {
        if (!root) return;

        if (root->data != '$')
            huffmanCode[root->data] = str;

        generateCodes(root->left, str + "0");
        generateCodes(root->right, str + "1");
    }

    string encode(const string& text) {
        stringstream encodedStream;
        for (char ch : text) {
            encodedStream << huffmanCode[ch];
        }
        return encodedStream.str();
    }

    string decode(const string& encodedString) {
        string decodedString = "";
        HuffmanNode* current = root;
        for (char ch : encodedString) {
            if (ch == '0')
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
