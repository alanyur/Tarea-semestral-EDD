#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Huffman.cpp"

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
    auto start = high_resolution_clock::now();
    string encodedString = huffman.codificar(text);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << encodedString << " " << duration.count() / 1e6 << endl;

    return 0;
}
