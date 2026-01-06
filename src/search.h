#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"
#include "node.h"
#include <vector>
#include <set>

class Search {
  public:
    Search(const Graph& graph, int start_node, int end_node);
    bool Run(int algorithm_type);
    void PrintProblemInfo() const;

  private:
    const Graph& graph_;
    int start_node_;
    int end_node_;

    bool BFS();
    bool DFS();

    void PrintPath(const std::vector<Node>& closed_list) const;
};

#endif // SEARCH_H 