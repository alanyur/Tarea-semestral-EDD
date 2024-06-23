#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "huff_codification.cpp"

/**
 * @brief Lee las líneas del archivo de entrada y crea un vector de strings para luego poder procesarlas
 * @param filename Nombre del archivo a leer.
 * @return Vector de strings que contiene las líneas del archivo.
 */
std::vector<std::string> readLines(const std::string& filename) {
    std::ifstream inFile(filename);
    std::vector<std::string> lines;
    std::string line;
    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            lines.push_back(line);
        }
        inFile.close();
    } else {
        std::cerr << "No se pudo abrir el archivo de entrada: " << filename << std::endl;
    }
    return lines;
}

/**
 * @brief Punto de entrada principal del programa.
 * @param argc Número de argumentos de línea de comandos.
 * @param argv Argumentos de línea de comandos.
 * @return Código de estado de la ejecución del programa.
 */
int main(int argc, char* argv[]) {
    std::string inputFilename = "input.txt";
    int numExperiments = 1;

    if (argc > 1) {
        numExperiments = std::stoi(argv[1]);
    }

    std::vector<std::string> lines = readLines(inputFilename);

    if (lines.empty()) {
        std::cerr << "El archivo de entrada está vacío o no se pudo leer." << std::endl;
        return 1;
    }

    HuffmanCoding huffman;

    std::vector<std::string> encodedResults;
    std::vector<std::vector<double>> encodeTimes(lines.size(), std::vector<double>(numExperiments));
    std::vector<std::string> decodedResults;
    std::vector<std::vector<double>> decodeTimes(lines.size(), std::vector<double>(numExperiments));
    std::vector<size_t> originalSizes;
    std::vector<size_t> encodedSizes;
    //std::vector<size_t> decodedSizes;
    
    for (int i = 0; i < lines.size(); ++i) {
        std::string text = lines[i];
        std::string encodedString;
        originalSizes.push_back(text.size() * sizeof(char));
        for (int j = 0; j < numExperiments; ++j) {
            // Medir tiempo de codificación
            auto start = std::chrono::high_resolution_clock::now();
            encodedString = huffman.codificar(text);
            auto stop = std::chrono::high_resolution_clock::now();
            encodeTimes[i][j] = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() / 1e9;
        }
        encodedResults.push_back(encodedString);
        encodedSizes.push_back(encodedString.size() * sizeof(char));
        for (int j = 0; j < numExperiments; ++j) {
            // Medir tiempo de decodificación
            auto start = std::chrono::high_resolution_clock::now();
            std::string decodedString = huffman.decodificar(encodedString);
            auto stop = std::chrono::high_resolution_clock::now();
            decodeTimes[i][j] = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() / 1e9;
        }
        std::string decodedString = huffman.decodificar(encodedString);
        decodedResults.push_back(decodedString);
        //decodedSizes.push_back(decodedString.size() * sizeof(char));
    }
    for (int i = 0; i < lines.size(); ++i) {
        std::cout << "Original Size: " << originalSizes[i] << " bytes" << std::endl;
        std::cout << "Encoded Size: " << encodedSizes[i] << " bytes" << std::endl;
        //std::cout << "Tamaño decodificado: " << decodedSizes[i] << " bytes" << std::endl;
    }

    std::cout << "Compressed Results" << std::endl;
    for (const auto& result : encodedResults) {
        std::cout << result << std::endl;
    }

    std::cout << std::endl << "Encode Times (seconds)" << std::endl;
    std::cout << std::scientific << std::setprecision(3);
    for (const auto& times : encodeTimes) {
        for (const auto& time : times) {
            std::cout << time << ";";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << "Decompressed Results" << std::endl;
    for (const auto& result : decodedResults) {
        std::cout << result << std::endl;
    }

    std::cout << std::endl << "Decode Times (seconds)" << std::endl;
    std::cout << std::scientific << std::setprecision(3);
    for (const auto& times : decodeTimes) {
        for (const auto& time : times) {
            std::cout << time << ";";
        }
        std::cout << std::endl;
    }

    return 0;
}
