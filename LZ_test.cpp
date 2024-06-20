#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include "LZ.cpp"

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

    LZ lz;

    // Comprimir y obtener los pares ordenados del diccionario
    auto start = high_resolution_clock::now();
    vector<pair<int, int>> compressed = lz.comprimir(text);
    auto stop = high_resolution_clock::now();
    auto encode_duration = duration_cast<microseconds>(stop - start).count();

    // Construir la cadena del resultado de la compresión
    stringstream compressed_result;
    compressed_result << "Resultado de Codificar: ";
    for (const auto& entry : compressed) {
        if (entry.second == 0) {
            compressed_result << "(" << static_cast<char>(entry.first) << ", " << entry.second << ") ";
        } else {
            compressed_result << "(" << entry.first << ", " << entry.second << ") ";
        }
    }
    compressed_result << endl;
    compressed_result << "Tiempo de Codificar: " << encode_duration << " microseconds" << endl;

    // Realizar la descompresión y medir el tiempo
    string decodedString = lz.descomprimir(compressed);

    start = high_resolution_clock::now();
    lz.descomprimir(compressed);
    stop = high_resolution_clock::now();
    auto decode_duration = duration_cast<microseconds>(stop - start).count();

    // Construir la cadena del resultado de la descompresión
    stringstream decompressed_result;
    decompressed_result << "Resultado de Descodificar: " << decodedString << endl;
    decompressed_result << "Tiempo de Descodificar: " << decode_duration << " microseconds" << endl;

    // Imprimir todo junto para facilitar la captura en el archivo por lotes
    cout << compressed_result.str() << decompressed_result.str();

    return 0;
}
