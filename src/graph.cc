/*
  Name: Leandro Delli Santi
  Date: 06/01/2026
  mail: alu0101584003@ull.edu.es
  Description: Graph class definition
  file: graph.cc
*/

#include "graph.h"

#include <iostream>
#include <iomanip>
#include <fstream>

Graph::Graph() : edges_(0), nodes_(0) {}

std::ostream& operator<<(std::ostream& stream, const Graph& graph) {
  stream << "--- Graph Overview ---\n";
  stream << "Nodes: " << graph.nodes_ << std::endl;
  stream << "Edges: " << graph.edges_ << std::endl;
  stream << "Adjacency Matrix:\n";

  for (int i = 0; i < graph.nodes_; ++i) {
    for (int j = 0; j < graph.nodes_; ++j) {
      stream << std::setw(6) << graph.adj_matrix_[i][j] << " ";
    }
   stream << std::endl;
  }

  return stream;
}

int Graph::GetNumNodes() const {
  return nodes_;
}

double Graph::GetEdgeCost(int node_a, int node_b) const {
  if (node_a < 0 || node_a >= nodes_ || node_b < 0 || node_b >= nodes_) {
    return -1.0;
  }
  return adj_matrix_[node_a][node_b];
}

bool Graph::LoadFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Cannot open file " << filename << std::endl;
    return false;
  }

  if (!(file >> nodes_)) return false;

  adj_matrix_.resize(nodes_, std::vector<double>(nodes_));
  for (int i = 0; i < nodes_; ++i) adj_matrix_[i][i] = 0.0;

  edges_ = 0;
  double weight;

  for (int i = 0; i < nodes_ - 1; ++i) {
    for (int j = i + 1; j < nodes_; ++j) {
      if (file >> weight) {
        adj_matrix_[i][j] = weight;
        adj_matrix_[j][i] = weight;
        if (weight != -1.0) edges_++;
      } else {
        return false;
      }
    }
  }
  
  file.close();
  return true;
}

