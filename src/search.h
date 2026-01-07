/*
  Name: Leandro Delli Santi
  Grade: 3rd Year
  mail: alu0101584003@ull.edu.es
  Subject: IA (Artificial Inteligence)
  School: ESIT (Escuela Superior de Ingenieria y Tecnología)
  Theme of the practice: Not informed searching
  Date: 06/01/2026
  File: search.h - declaration of the Search class.
*/

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