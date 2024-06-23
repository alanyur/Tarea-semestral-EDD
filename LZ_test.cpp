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

    LZ lz;

    vector<string> compressedResults;
    vector<vector<double>> encodeTimes(lines.size(), vector<double>(numExperiments));
    vector<string> decompressedResults;
    vector<vector<double>> decodeTimes(lines.size(), vector<double>(numExperiments));
    vector<size_t> originalSizes;
    vector<size_t> compressedSizes;

    // Procesar cada línea
    for (int i = 0; i < lines.size(); ++i) {
        const auto& text = lines[i];
        originalSizes.push_back(text.size());

        for (int j = 0; j < numExperiments; ++j) {
            auto start = high_resolution_clock::now();
            vector<pair<int, int>> compressed = lz.comprimir(text);
            auto stop = high_resolution_clock::now();
            encodeTimes[i][j] = duration_cast<nanoseconds>(stop - start).count() / 1'000'000.0;
            if (j == 0) {
                stringstream compressed_result;
                for (const auto& entry : compressed) {
                    if (entry.second == 0) {
                        compressed_result << "(" << static_cast<char>(entry.first) << " / " << entry.second << ") ";
                    } else {
                        compressed_result << "(" << entry.first << " / " << entry.second << ") ";
                    }
                }
                compressedResults.push_back(compressed_result.str());
                compressedSizes.push_back(compressed_result.str().size());
            }
            start = high_resolution_clock::now();
            string decodedString = lz.descomprimir(compressed);
            stop = high_resolution_clock::now();
            decodeTimes[i][j] = duration_cast<nanoseconds>(stop - start).count() / 1'000'000.0; // Convertir a segundos

            if (j == 0) {
                decompressedResults.push_back(decodedString);
            }
        }
    }
    cout << "Compressed Results" << endl;
    for (const auto& result : compressedResults) {
        cout << result << endl;
    }

    cout << endl << "Encode Times (seconds)" << endl;
    cout << fixed << setprecision(5); 
    for (const auto& times : encodeTimes) {
        for (const auto& time : times) {
            cout << time << ";";
        }
        cout << endl;
    }

    cout << endl << "Decompressed Results" << endl;
    for (const auto& result : decompressedResults) {
        cout << result << endl;
    }

    cout << endl << "Decode Times (seconds)" << endl;
    cout << fixed << setprecision(5);
    for (const auto& times : decodeTimes) {
        for (const auto& time : times) {
            cout << time << ";";
        }
        cout << endl;
    }
    cout << endl << "Size of Original Data (bytes)" << endl;
    for (size_t i = 0; i < lines.size(); ++i) {
        cout << "Line " << i + 1 << ": "
             << "Original: " << originalSizes[i] << " bytes, "<< endl;
    }
    cout << endl << "Size of Compressed Data (bytes)" << endl;
    for (size_t i = 0; i < lines.size(); ++i) {
        cout << "Line " << i + 1 << ": "
             << "Compressed: " << compressedSizes[i] << " bytes, "<< endl;
    }
    return 0;
}
