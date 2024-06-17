#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Función de compresión LZW
vector<int> comprimir(string input) {
    // Crear un diccionario y inicializar con símbolos individuales
    unordered_map<string, int> dictionary;
    for (int i = 0; i < 256; i++) {
        dictionary[string(1, i)] = i;
    }

    string current;
    vector<int> compressed;
    int dictSize = 256;

    for (char c : input) {
        string next = current + c;
        if (dictionary.find(next) != dictionary.end()) {
            current = next;
        } else {
            compressed.push_back(dictionary[current]);
            dictionary[next] = dictSize++;
            current = string(1, c);
        }
    }

    if (!current.empty()) {
        compressed.push_back(dictionary[current]);
    }

    return compressed;
}

// Función de descompresión LZW
string descomprimir(vector<int> compressed) {
    // Crear un diccionario e inicializar con símbolos individuales
    unordered_map<int, string> dictionary;
    for (int i = 0; i < 256; i++) {
        dictionary[i] = string(1, i);
    }

    int dictSize = 256;
    string current(1, compressed[0]);
    string result = current;
    string entry;

    for (int i = 1; i < compressed.size(); i++) {
        int k = compressed[i];
        if (dictionary.find(k) != dictionary.end()) {
            entry = dictionary[k];
        } else if (k == dictSize) {
            entry = current + current[0];
        } else {
            cerr << "Error: código inválido en la descompresión: " << k << endl;
            return "";
        }

        result += entry;
        dictionary[dictSize++] = current + entry[0];
        current = entry;
    }

    return result;
}

class LZWCompression {
public:
    vector<int> compressed;

    void comprimir(string text) {
        compressed = ::comprimir(text);
        for (int code : compressed) {
            cout << code << " ";
        }
        cout << endl;
    }

    void descomprimir() {
        string decompressed = ::descomprimir(compressed);
        cout << "Decompressed String: " << decompressed << endl;
    }
};
