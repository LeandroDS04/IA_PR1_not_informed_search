/*
  Name: Leandro Delli Santi
  Date: 06/01/2026
  mail: alu0101584003@ull.edu.es
  Description: Graph class definition
  file: graph.h
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <iostream>

class Graph {
  public:
    Graph();
    bool LoadFromFile(const std::string& filename);
    int GetNumNodes() const;
    double GetEdgeCost(int node_a, int node_b) const;
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

  private:
    int edges_;
    int nodes_;
    std::vector<std::vector<double>> adj_matrix_;
};

std::ostream& operator<<(std::ostream& os, const Graph& graph);

#endif // GRAPH_H