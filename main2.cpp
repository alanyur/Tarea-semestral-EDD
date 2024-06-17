#include <chrono>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

#include "LZ2.cpp"
#include "Huffman2.cpp"
#include "LZ78.cpp"

using namespace std;
using namespace std::chrono;

int main() {
    string text = "tangananica-tanganana";
    
    // Huffman Coding
    cout << "|----HUFFMAN----|" << endl;
    HuffmanCoding huffman;
    auto start = chrono::high_resolution_clock::now();
    string encodedString = huffman.codificar(text);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Encoded String: " << encodedString << endl;
    cout << "Encoding Time: " << duration.count() << " microseconds" << endl;

    string decodedString = huffman.decodificar(encodedString);
    cout << "Decoded String: " << decodedString << endl;

    cout << "|------LZ------|" << endl;
    // LZW Compression
    LZWCompression lz;
    start = chrono::high_resolution_clock::now();
    cout << "Compression: ";
    lz.comprimir(text);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Compression Time: " << duration.count() << " microseconds" << endl;

    lz.descomprimir();

    // LZ78
    LZ78 lz78;
    start = chrono::high_resolution_clock::now();
    std::vector<std::pair<int, char>> compressed = lz78.compress(text);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Compression Time: " << duration.count() << " microseconds" << endl;
    std::string decompressed = lz78.decompress(compressed);

    // Print the compressed output
    std::cout << "Compressed: ";
    for (const auto& entry : compressed) {
        std::cout << "(" << entry.first << ", " << entry.second << ") ";
    }
    std::cout << std::endl;

    // Print the decompressed output
    std::cout << "Decompressed: " << decompressed << std::endl;


    return 0;
}
