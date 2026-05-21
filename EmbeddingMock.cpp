#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// A simple function to calculate the Dot Product of two vectors
// This is exactly how AI search engines figure out if two things are related!
float calculateSimilarity(const vector<float>& vecA, const vector<float>& vecB) {
    float dotProduct = 0.0f;
    for (size_t i = 0; i < vecA.size(); ++i) {
        dotProduct += vecA[i] * vecB[i];
    }
    return dotProduct;
}

int main() {
    // Imagine we have 3 text chunks from yesterday.
    // Let's represent each chunk with a mock 3-dimensional embedding vector.
    // In a real system, this would be 384 dimensions instead of 3!
    
    vector<float> chunk0_vector = {0.15f, 0.88f, 0.02f}; // e.g., IITM info
    vector<float> chunk1_vector = {0.91f, 0.12f, 0.05f}; // e.g., Full-stack development
    
    // Now, imagine the user types a search query: "How to code back-end web apps?"
    // The embedding model turns the user's query into this vector:
    vector<float> query_vector  = {0.85f, 0.18f, 0.01f};

    cout << "--- Day 3: Vector Similarity Mathematical Testing ---" << endl;

    // Calculate similarity between query and Chunk 0
    float simToChunk0 = calculateSimilarity(query_vector, chunk0_vector);
    // Calculate similarity between query and Chunk 1
    float simToChunk1 = calculateSimilarity(query_vector, chunk1_vector);

    cout << "Similarity score with Chunk [0]: " << simToChunk0 << endl;
    cout << "Similarity score with Chunk [1]: " << simToChunk1 << endl;

    // Determine the winner
    if (simToChunk1 > simToChunk0) {
        cout << "\nResult: Query matches Chunk [1] best! Pass Chunk [1] to Llama." << endl;
    } else {
        cout << "\nResult: Query matches Chunk [0] best! Pass Chunk [0] to Llama." << endl;
    }

    return 0;
}