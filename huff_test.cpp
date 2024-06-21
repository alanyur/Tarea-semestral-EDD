#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "huff_codification.cpp"

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

    HuffmanCoding huffman;

    vector<string> encodedResults;
    vector<vector<double>> encodeTimes(lines.size(), vector<double>(numExperiments));
    vector<string> decodedResults;
    vector<vector<double>> decodeTimes(lines.size(), vector<double>(numExperiments));
    for (int i = 0; i < lines.size(); ++i) {
        string text = lines[i];
        string encodedString;
        for (int j = 0; j < numExperiments; ++j) {
            // Codificar y medir el tiempo
            auto start = high_resolution_clock::now();
            encodedString = huffman.codificar(text);
            auto stop = high_resolution_clock::now();
            encodeTimes[i][j] = duration_cast<microseconds>(stop - start).count() / 1'000'000.0;
        }
        encodedResults.push_back(encodedString);
        string decodedString = huffman.decodificar(encodedString);
        decodedResults.push_back(decodedString);
    }
    cout << "Compressed Results" << endl;
    for (const auto& result : encodedResults) {
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
    for (const auto& result : decodedResults) {
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

    return 0;
}
