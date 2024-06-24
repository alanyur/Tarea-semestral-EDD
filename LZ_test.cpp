#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <iomanip>
#include "lz_compression.cpp"

using namespace std;
using namespace std::chrono;

/**
 * @brief Lee las líneas de un archivo y las almacena en un vector de strings.
 * 
 * @param filename Nombre del archivo a leer.
 * @return vector<string> Vector con las líneas del archivo.
 */
vector<string> readLines(const string& filename) {
    ifstream inFile(filename);
    vector<string> lines;
    string line;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            lines.push_back(line);
        }
        inFile.close();
    } else {
        cerr << "No se pudo abrir el archivo de entrada: " << filename << endl;
    }
    return lines;
}

/**
 * @brief Función principal que ejecuta la compresión y descompresión de textos, 
 * mide los tiempos de ejecución y guarda los resultados en un archivo CSV.
 * 
 * @param argc Número de argumentos.
 * @param argv Vector de argumentos.
 * @return int Código de retorno del programa.
 */
int main(int argc, char* argv[]) {
    string inputFilename = "input.txt";
    int numExperiments = 1;

    if (argc > 1) {
        numExperiments = stoi(argv[1]);
    }

    vector<string> lines = readLines(inputFilename);

    if (lines.empty()) {
        cerr << "El archivo de entrada está vacío o no se pudo leer." << endl;
        return 1;
    }

    vector<vector<pair<string, int>>> compressedResults;
    vector<vector<double>> encodeTimes(lines.size(), vector<double>(numExperiments));
    vector<string> decompressedResults;
    vector<vector<double>> decodeTimes(lines.size(), vector<double>(numExperiments));
    vector<int> originalSizes;
    vector<int> compressedSizes;

    for (int i = 0; i < lines.size(); ++i) {
        const auto& text = lines[i];
        originalSizes.push_back(text.size());

        for (int j = 0; j < numExperiments; ++j) {
            auto start = high_resolution_clock::now();
            vector<pair<string, int>> compressed = comprimir(text);
            auto stop = high_resolution_clock::now();
            encodeTimes[i][j] = duration_cast<nanoseconds>(stop - start).count() / 1'000'000.0;
            
            start = high_resolution_clock::now();
            string decodedString = descomprimir(compressed);
            stop = high_resolution_clock::now();
            decodeTimes[i][j] = duration_cast<nanoseconds>(stop - start).count() / 1'000'000.0;

            if (j == 0) {
                decompressedResults.push_back(decodedString);
                compressedResults.push_back(compressed);
                compressedSizes.push_back(compressed.size());
            }
        }
    }

    ofstream outputFile("output_lz.csv");

    if (!outputFile.is_open()) {
        cerr << "No se pudo abrir el archivo de salida." << endl;
        return 1;
    }

    outputFile << "Resultados comprimidos:" << endl;
    for (const auto& compressed : compressedResults) {
        for (const auto& p : compressed) {
            outputFile << "{" << p.first << "," << p.second << "} ";
        }
        outputFile << endl;
    }

    outputFile << endl << "Tiempos de codificación (milisegundos):" << endl;
    outputFile << fixed << setprecision(5);
    for (const auto& times : encodeTimes) {
        for (const auto& time : times) {
            outputFile << time << ";";
        }
        outputFile << endl;
    }

    outputFile << endl << "Resultados descomprimidos:" << endl;
    for (const auto& result : decompressedResults) {
        outputFile << result << endl;
    }

    outputFile << endl << "Tiempos de decodificación (milisegundos):" << endl;
    outputFile << fixed << setprecision(5);
    for (const auto& times : decodeTimes) {
        for (const auto& time : times) {
            outputFile << time << ";";
        }
        outputFile << endl;
    }

    outputFile << endl << "Tamaños originales:" << endl;
    for (const auto& size : originalSizes) {
        outputFile << size << endl;
    }

    outputFile << endl << "Tamaños comprimidos:" << endl;
    for (const auto& size : compressedSizes) {
        outputFile << size << endl;
    }

    outputFile.close();
    return 0;
}
