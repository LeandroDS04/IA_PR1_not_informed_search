/*
  Name: Leandro Delli Santi
  Grade: 3rd Year
  mail: alu0101584003@ull.edu.es
  Subject: IA (Artificial Inteligence)
  School: ESIT (Escuela Superior de Ingenieria y Tecnología)
  Theme of the practice: Not informed searching
  Date: 06/01/2026
  File: graph.cc - implementation of the Graph class.
*/

#include "graph.h"

#include <iostream>
#include <iomanip>
#include <fstream>

/**
 * @brief Default constructor for the Graph class. Initializes the number of edges and nodes to zero.
 */
Graph::Graph() : edges_(0), nodes_(0) {}

/**
 * @brief Overloads the output stream operator to print the graph's details.
 * @param stream The output stream.
 * @param graph The graph to print.
 * @return Reference to the output stream.
 */
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

/**
 * @brief Returns the number of nodes in the graph.
 * @return Number of nodes.
 */
int Graph::GetNumNodes() const {
  return nodes_;
}

/**
 * @brief Returns the cost of the edge between two nodes.
 * @param node_a Index of the first node.
 * @param node_b Index of the second node.
 * @return Cost of the edge, or -1.0 if invalid.
 */
double Graph::GetEdgeCost(int node_a, int node_b) const {
  if (node_a < 0 || node_a >= nodes_ || node_b < 0 || node_b >= nodes_) {
    return -1.0;
  }
  return adj_matrix_[node_a][node_b];
}

/**
 * @brief Loads a graph from a file. The file should contain the number of nodes and the adjacency matrix.
 * @param filename Name of the file to load the graph from.
 * @return True if the graph was loaded successfully, false otherwise.
 */
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

