#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>

/**
 * @brief Nodo del un árbol de Huffman.
 */
struct HuffmanNode {
    char data;
    int frequency; 
    HuffmanNode* left; 
    HuffmanNode* right; 

    /**
     * @brief Constructor del nodo de Huffman.
     * @param data Carácter almacenado en el nodo.
     * @param frequency Frecuencia del carácter.
     */
    HuffmanNode(char data, int frequency) {
        left = right = nullptr;
        this->data = data;
        this->frequency = frequency;
    }
};

/**
 * @brief Comparador para la cola de prioridad de nodos de Huffman.
 */
struct compare {
    /**
     * @brief Operador de comparación.
     * @param l Nodo de Huffman izquierdo.
     * @param r Nodo de Huffman derecho.
     * @return Verdadero si la frecuencia del nodo izquierdo es mayor que la del derecho.
     */
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return (l->frequency > r->frequency);
    }
};

/**
 * @brief Clase para la codificación y decodificación Huffman.
 */
class HuffmanCoding {
public:
    std::unordered_map<char, std::string> huffmanCode;
    HuffmanNode* root;

    /**
     * @brief Constructor de HuffmanCoding.
     */
    HuffmanCoding() : root(nullptr) {}

    /**
     * @brief Destructor de HuffmanCoding.
     */
    ~HuffmanCoding() {
        freeTree(root);
    }

    /**
     * @brief Codifica un texto utilizando el algoritmo de Huffman.
     * @param text Texto a codificar.
     * @return Texto codificado.
     */
    std::string codificar(const std::string& text) {
        root = buildHuffmanTree(text);
        generateCodes(root, "");
        return encode(text);
    }

    /**
     * @brief Decodifica un texto codificado con el algoritmo de Huffman.
     * @param encodedString Texto codificado.
     * @return Texto decodificado.
     */
    std::string decodificar(const std::string& encodedString) {
        return decode(encodedString);
    }

private:
    /**
     * @brief Construye el árbol de Huffman a partir del texto dado.
     * @param text Texto para construir el árbol.
     * @return Raíz del árbol de Huffman.
     */
    HuffmanNode* buildHuffmanTree(const std::string& text) {
        std::unordered_map<char, int> freq;
        for (char ch : text) {
            freq[ch]++;
        }

        std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, compare> minHeap;
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

    /**
     * @brief Genera los códigos Huffman a partir del árbol de Huffman ya construido.
     * @param root Raíz del árbol de Huffman desde donde buscaremos al arbol.
     * @param str Cadena que representa el código actual.
     */
    void generateCodes(HuffmanNode* root, const std::string& str) {
        if (!root) return;

        if (root->data != '$')
            huffmanCode[root->data] = str;

        generateCodes(root->left, str + "0");
        generateCodes(root->right, str + "1");
    }

    /**
     * @brief Recorre el string text asignando la codificacion correspondiente.
     * @param text Texto a codificar.
     * @return Texto codificado.
     */
    std::string encode(const std::string& text) {
        std::stringstream encodedStream;
        for (char ch : text) {
            encodedStream << huffmanCode[ch];
        }
        return encodedStream.str();
    }

    /**
     * @brief Decodifica el texto codificado utilizando el arbol.
     * @param encodedString Texto codificado.
     * @return Texto decodificado.
     */
    std::string decode(const std::string& encodedString) {
        std::string decodedString = "";
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

    /**
     * @brief Libera la memoria del arbol.
     * @param node Nodo actual del arbol.
     */
    void freeTree(HuffmanNode* node) {
        if (node == nullptr) return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }
};
