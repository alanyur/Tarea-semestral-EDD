#include <chrono>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

#include "LZ2.cpp"
#include "Huffman2.cpp"

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

    return 0;
}
