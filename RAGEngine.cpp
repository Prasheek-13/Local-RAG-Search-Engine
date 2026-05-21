#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

struct KnowledgeChunk {
    string text;
    vector<float> embedding;
};

float calculateSimilarity(const vector<float>& vecA, const vector<float>& vecB) {
    float dotProduct = 0.0f;
    for (size_size_t i = 0; i < vecA.size(); ++i) {
        dotProduct += vecA[i] * vecB[i];
    }
    return dotProduct;
}

int main() {
    // 1. READ YOUR TEXTBOOK FILE
    ifstream file("knowledge.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not find or open knowledge.txt!" << endl;
        return 1;
    }

    vector<string> raw_paragraphs;
    string line;
    string current_chunk = "";

    while (getline(file, line)) {
        if (line.empty()) {
            if (!current_chunk.empty()) {
                raw_paragraphs.push_back(current_chunk);
                current_chunk = "";
            }
        } else {
            if (!current_chunk.empty()) current_chunk += " ";
            current_chunk += line;
        }
    }
    if (!current_chunk.empty()) raw_paragraphs.push_back(current_chunk);
    file.close();

    // 2. DATABASE PREPARATION
    vector<KnowledgeChunk> database;
    vector<vector<float>> mock_embeddings = {
        {0.15f, 0.88f, 0.02f}, // Index 0 coordinates
        {0.91f, 0.12f, 0.05f}, // Index 1 coordinates
        {0.45f, 0.50f, 0.70f}  // Index 2 coordinates
    };

    for (size_t i = 0; i < raw_paragraphs.size() && i < mock_embeddings.size(); ++i) {
        KnowledgeChunk k;
        k.text = raw_paragraphs[i];
        k.embedding = mock_embeddings[i];
        database.push_back(k);
    }

    // 3. DYNAMIC USER INPUT TERMINAL
    string user_question;
    cout << "=======================================================" << endl;
    cout << "🤖 LOCAL C++ RAG ENGINE TERMINAL ACTIVE" << endl;
    cout << "=======================================================" << endl;
    cout << "Enter your question: ";
    getline(cin, user_question); // This captures whatever question you type!

    // Simple routing logic simulating real vector conversion layout
    vector<float> query_vector;
    if (user_question.find("iit") != string::npos || user_question.find("IIT") != string::npos) {
        query_vector = {0.15f, 0.85f, 0.05f}; // Routes search to match Chunk 0
    } else if (user_question.find("rag") != string::npos || user_question.find("RAG") != string::npos || user_question.find("ai") != string::npos) {
        query_vector = {0.40f, 0.48f, 0.72f}; // Routes search to match Chunk 2
    } else {
        query_vector = {0.85f, 0.18f, 0.01f}; // Default routes search to match Chunk 1 (Web Dev)
    }

    int best_match_index = -1;
    float highest_score = -1.0f;

    for (size_t i = 0; i < database.size(); ++i) {
        float score = calculateSimilarity(query_vector, database[i].embedding);
        if (score > highest_score) {
            highest_score = score;
            best_match_index = i;
        }
    }

    // 4. INJECT CONTEXT AND TRIGGER LOCAL AI
    if (best_match_index != -1) {
        string retrieved_text = database[best_match_index].text;

        cout << "\n[System] Found relevant context in textbook. Injected into Llama..." << endl;

        string prompt = "Context: " + retrieved_text + " | Question: " + user_question + " Answer the question shortly using only the context provided.";
        
        string command = "cd \"C:\\Users\\prash\\AI_Project\\llama-bin\" && llama-cli -m model.gguf -p \"" + prompt + "\"";

        system(command.c_str());
    }

    return 0;
}