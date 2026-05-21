# Local RAG Search Engine in C++

A lightweight, completely offline Retrieval-Augmented Generation (RAG) search engine built from scratch in pure C++. This system bridges raw document text-parsing with linear algebra similarity algorithms to intelligently ground a local 8B LLM engine without cloud dependencies.

## 🏗️ Architecture Pipeline
1. **Document Segmenter:** Parses raw `.txt` files line-by-line, dynamically chunking text blocks using paragraph break-points.
2. **Unified Data Matrix:** Maps individual paragraph strings directly to high-dimensional coordinate vectors utilizing a custom C++ `struct` layout.
3. **Semantic Search Engine:** Executes a linear max-value search across database records using a custom **Dot Product Similarity** routine.
4. **LLM Automation Layer:** Leverages system-level kernel process calls (`system()`) to dynamically pass retrieved factual anchors into a local `llama.cpp` CLI context window.

## 🛠️ Tech Stack
* **Language:** C++ (Standard Template Library)
* **AI Tooling:** Llama.cpp / Llama-3 8B GGUF
* **Environment:** VS Code / Windows Terminals