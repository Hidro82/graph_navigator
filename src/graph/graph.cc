#include <iostream>
#include <fstream>  
#include "bits/stdc++.h"
#include "graph.h"
#include "../libs/matrix/s21_matrix_oop.hpp"

Graph::Graph() {};

Graph::Graph(const std::string &filename) {LoadGraphFromFile(filename);}

Graph::~Graph() {};

const std::vector<std::vector<int>>& Graph::getGraph() const noexcept {
  return graph;
}

const GraphType& Graph::getType() const noexcept {
  return type;
}

void Graph::LoadGraphFromFile(const std::string &filename) {
  if (filename == "")
    throw std::invalid_argument("path is empty");
  graph.clear();
  parseFile(readFile(filename));
  checkGraphType();
}

void Graph::ExportGraphToDot(const std::string &filename) {
  std::ofstream outFile(filename);
  outFile << "graph Matrix adjacency {\n\tnode [shape=circle, color=black];\n";
  std::string edge = type == GraphType::UnweightedDirected || type == GraphType::UnweightedDirected ? 
                     " -> " : " -- ";
  int offset = type == GraphType::WeightedUndirected || type == GraphType::UnweightedUndirected;

  if (type == GraphType::WeightedDirected || type == GraphType::WeightedUndirected) {
    for (int i = 0; i < (int)graph.size(); ++i) {
      for (int k = i + offset; k < (int)graph.at(i).size(); ++k) {
        outFile << "\t" << i + 1 << edge << k + 1 << " [weight=" << graph.at(i).at(k) << "];\n";
      }
    }
  } else {
    for (int i = 0; i < (int)graph.size(); ++i) {
      for (int k = i + offset; k < (int)graph.at(i).size(); ++k) {
        outFile << "\t" << i + 1 << edge << k + 1 << ";\n";
      }
    }
  }
  outFile << "}";
  outFile.close();
}

std::vector<std::string> Graph::readFile(const std::string &filePath) const {
  std::fstream file(filePath);
  if (!file.is_open())
    throw std::invalid_argument("file didn't open: " + filePath);
  std::string line;
  std::vector<std::string> fileData;
  while (getline(file, line)) {
    fileData.push_back(line);
  }
  file.close();
  return fileData;
}

void Graph::parseFile(const std::vector<std::string> &fileData) {
  if (!fileData.size())
    throw std::invalid_argument("read file is empty");
  std::stringstream stream(fileData.at(0));
  std::string value;
  getline(stream, value);
  int size = stoi(value);
  graph.reserve(size);
  auto writeLine = [&](const std::string& line, std::vector<int>& graphLine)->void {
    for (int i = 0, count = 0; i < (int)line.length() && count < size; ++i) {
      if (line.at(i) == ' ') continue;
      std::string value;
      while ((i < (int)line.length()) && line.at(i) != ' ') value += line.at(i++);
      graphLine.push_back(atoi(value.c_str()));
      ++count;
    }
  };
  for (int i = 1; i < (int)fileData.size() && i < size + 1; ++i) {
    std::vector<int> vec;
    writeLine(fileData.at(i), vec);
    graph.push_back(vec);
  }
}

void Graph::checkGraphType() {
  S21Matrix matrix;
  matrix.SetMatrix(graph, graph.size(), graph.size());
  S21Matrix matrixT = matrix.Transpose();
  bool weighted = false;
  bool directed = !(matrix == matrixT); 
  for (int i = 0; i < (int)graph.size(); ++i) {
    for (int k = 0; k < (int)graph.at(i).size(); ++k) {
      if (matrix(i, k) > 1) {
        weighted = true;
        break;
      }
    }
  }
  if (weighted && directed) {
    // printf("Weighted Directed\n");
    type = GraphType::WeightedDirected;
  }
  else if (!weighted && directed) {
    // printf("Unweighted Directed\n");
    type = GraphType::UnweightedDirected;
  }
  else if (weighted && !directed) {
    // printf("Weighted Undirected\n");
    type = GraphType::WeightedUndirected;
  }
  else if (!weighted && !directed) {
    // printf("Unweighted Undirected\n");
    type = GraphType::UnweightedUndirected;
  }
}
