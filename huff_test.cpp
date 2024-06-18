#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include "huff_codification.cpp"

using namespace std;
using namespace std::chrono;

string readFile(const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        stringstream buffer;
        buffer << inFile.rdbuf();
        inFile.close();
        return buffer.str();
    } else {
        cerr << "No se pudo abrir el archivo de entrada: " << filename << endl;
        return "";
    }
}

int main() {
    string inputFilename = "input.txt";
    string text = readFile(inputFilename);

    if (text.empty()) {
        cerr << "El archivo de entrada está vacío o no se pudo leer." << endl;
        return 1;
    }

    HuffmanCoding huffman;
    string encodedString = huffman.codificar(text);

    auto start = high_resolution_clock::now();
    huffman.codificar(text);
    auto stop = high_resolution_clock::now();
    auto encode_duration = duration_cast<microseconds>(stop - start).count();
    cout << "Resultado de Codificar:" << encodedString << endl;
    cout << "Tiempo de Codificar:" << encode_duration << endl;

    string decodedString = huffman.decodificar(encodedString);

    start = high_resolution_clock::now();
    huffman.decodificar(encodedString);
    stop = high_resolution_clock::now();
    auto decode_duration = duration_cast<microseconds>(stop - start).count();
    cout << "Resultado de Descodificar:" << decodedString << endl;
    cout << "Tiempo de Descodificar:" << decode_duration << endl;

    return 0;
}
