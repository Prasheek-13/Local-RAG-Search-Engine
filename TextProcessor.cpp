#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// This removes the need to type std:: everywhere
using namespace std;

int main() {
    // 1. Open the knowledge base file
    ifstream file("knowledge.txt");
    
    if (!file.is_open()) {
        cerr << "Error: Could not find or open knowledge.txt!" << endl;
        return 1;
    }

    vector<string> chunks;
    string line;
    string current_chunk = "";

    cout << "Reading and chunking file..." << endl;

    // 2. Read the file line-by-line
    while (getline(file, line)) {
        // If we hit an empty line, a paragraph just ended
        if (line.empty()) {
            if (!current_chunk.empty()) {
                chunks.push_back(current_chunk);
                current_chunk = ""; // Clear buffer for next chunk
            }
        } else {
            // Append line to current chunk, adding a space if it's not the start
            if (!current_chunk.empty()) {
                current_chunk += " ";
            }
            current_chunk += line;
        }
    }

    // Catch the last paragraph if file didn't end with an empty line
    if (!current_chunk.empty()) {
        chunks.push_back(current_chunk);
    }

    file.close();

    // 3. Print out the results to verify it works!
    cout << "\nSuccess! Total text chunks generated: " << chunks.size() << "\n";
    cout << "=========================================\n";
    
    for (size_t i = 0; i < chunks.size(); ++i) {
        cout << "Chunk [" << i << "]: " << chunks[i] << "\n\n";
    }

    return 0;
}