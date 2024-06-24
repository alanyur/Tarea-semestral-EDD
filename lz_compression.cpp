#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

/**
 * @brief Nodo del trie
 */
struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    int position;
    TrieNode() : position(-1) {}
};

/**
 * @brief Inserta un substring
 * 
 * @param root Puntero a la raíz
 * @param text Texto en el cual se inserta el substring
 * @param startPos Posición inicial del substring en el texto
 */
void insertTrie(TrieNode* root, const std::string& text, int startPos) {
    TrieNode* node = root;
    for (int i = startPos; i < text.size(); ++i) {
        if (node->children.find(text[i]) == node->children.end()) {
            node->children[text[i]] = new TrieNode();
        }
        node = node->children[text[i]];
        node->position = startPos;
    }
}

/**
 * @brief Busca el substring más largo que ya apareció en el trie
 * 
 * @param root Puntero a la raíz
 * @param text Texto en el cual se busca el substring
 * @param currentPos Posición desde donde se inicia la búsqueda
 * @return Par que contiene la posición del substring y su longitud
 */
std::pair<int, int> findLongestSubstring(TrieNode* root, const std::string& text, int currentPos) {
    std::pair<int, int> result = {-1, 0}; 
    TrieNode* node = root;
    int length = 0;

    for (int i = currentPos; i < text.size(); ++i) {
        if (node->children.find(text[i]) == node->children.end()) {
            break;
        }
        node = node->children[text[i]];
        length++;
        if (node->position != -1 && node->position < currentPos) {
            result = {node->position, length};
        }
    }

    return result;
}

/**
 * @brief Función de compresión LZ
 * 
 * @param text Texto a comprimir
 * @return Vector de pares
 */
std::vector<std::pair<std::string, int>> comprimir(const std::string& text) {
    TrieNode* root = new TrieNode();
    std::vector<std::pair<std::string, int>> compressed;
    int position = 0;

    while (position < text.size()) {
        std::pair<int, int> match = findLongestSubstring(root, text, position);

        if (match.second > 0) {
            compressed.push_back({std::to_string(match.first), match.second});
            for (int i = 0; i < match.second; ++i) {
                insertTrie(root, text, position + i);
            }
            position += match.second;
        } else {
            compressed.push_back({std::string(1, text[position]), 0});
            insertTrie(root, text, position);
            position++;
        }
    }
    std::function<void(TrieNode*)> deleteTrie = [&](TrieNode* node) {
        for (auto& child : node->children) {
            deleteTrie(child.second);
        }
        delete node;
    };
    deleteTrie(root);

    return compressed;
}

/**
 * @brief Función para descomprimir usando la lista de pares (símbolo, longitud)
 * 
 * @param compressed Vector de pares del texto comprimido
 * @return String que representa el texto original
 */
std::string descomprimir(const std::vector<std::pair<std::string, int>>& compressed) {
    std::string decompressed;
    
    for (const auto& pair : compressed) {
        if (pair.second == 0) {
            decompressed += pair.first; 
        } else {
            int pos = std::stoi(pair.first);
            int len = pair.second;
            std::string substring = decompressed.substr(pos, len);
            decompressed += substring;
        }
    }
    
    return decompressed;
}
