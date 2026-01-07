/*
  Name: Leandro Delli Santi
  Grade: 3rd Year
  mail: alu0101584003@ull.edu.es
  Subject: IA (Artificial Inteligence)
  School: ESIT (Escuela Superior de Ingenieria y Tecnología)
  Theme of the practice: Not informed searching
  Date: 06/01/2026
  File: search.cc - implementation of the Search class.
*/

#include "search.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <deque>

/**
 * @brief Constructs a Search object with a given graph, start node, and end node.
 * @param graph Reference to the graph to be searched.
 * @param start_node Index of the start node.
 * @param end_node Index of the end node.
 */
Search::Search(const Graph& graph, int start_node, int end_node)
  : graph_(graph), start_node_(start_node), end_node_(end_node) {}

/**
 * @brief Prints the contents of a vector of integers to standard output.
 * @param v The vector to print.
 */
void PrintVector(const std::vector<int>& v) {
  if (v.empty()) {
    std::cout << "-";
  } else {
    for (size_t i = 0; i < v.size(); ++i) {
      std::cout << v[i] << (i < v.size() - 1 ? ", " : "");
    }
  }
  std::cout << "\n";
}

/**
 * @brief Prints information about the search problem, including graph size and start/end nodes.
 */
void Search::PrintProblemInfo() const {
  int num_nodes = graph_.GetNumNodes();
  int num_edges = 0;
  for (int i = 0; i < num_nodes; ++i) {
    for (int j = i + 1; j < num_nodes; ++j) {
      if (graph_.GetEdgeCost(i, j) != -1.0) {
        num_edges++;
      }
    }
  }
  std::cout << "Número de nodos del grafo: " << num_nodes << "\n";
  std::cout << "Número de aristas del grafo: " << num_edges << "\n";
  std::cout << "Vértice origen: " << (start_node_ + 1) << "\n";
  std::cout << "Vértice destino: " << (end_node_ + 1) << "\n";
  std::cout << "--------------------------------------------------\n";
}

/**
 * @brief Runs the selected search algorithm (BFS or DFS).
 * @param algorithm_type 1 for BFS, otherwise DFS.
 * @return True if a path is found, false otherwise.
 */
bool Search::Run(int algorithm_type) {
  return (algorithm_type == 1) ? BFS() : DFS();
}

/**
 * @brief Performs Breadth-First Search (BFS) to find a path from start to end node.
 * @return True if a path is found, false otherwise.
 */
bool Search::BFS() {
  std::deque<Node> frontier;
  std::vector<int> generated_history;  
  std::vector<int> inspected_history; 

  Node start(start_node_, -1, 0.0);
  frontier.push_back(start);
  generated_history.push_back(start_node_ + 1);

  std::vector<Node> closed_list(graph_.GetNumNodes(), Node(-1, -2, 0.0));
  closed_list[start_node_] = start; 

  int iteration = 1;
  while (!frontier.empty()) {
    std::cout << "Iteración " << iteration++ << "\n";
    std::cout << "Nodos generados: ";
    PrintVector(generated_history);
    std::cout << "Nodos inspeccionados: ";
    PrintVector(inspected_history);
    std::cout << "--------------------------------------------------\n";

    Node current = frontier.front();
    frontier.pop_front();
    inspected_history.push_back(current.id + 1);

    if (current.id == end_node_) {
      PrintPath(closed_list);
      return true;
    }

    int num_nodes = graph_.GetNumNodes();

    for (int i = 0; i < num_nodes; ++i) {
      double weight = graph_.GetEdgeCost(current.id, i);
      
      if (weight != -1.0 && closed_list[i].father == -2) {
        Node neighbor(i, current.id, current.cost_g + weight);
        closed_list[i] = neighbor;     
        frontier.push_back(neighbor);  
        generated_history.push_back(i + 1); 
      }
    }
  }
  
  std::cout << "No path found.\n";
  return false;
}

/**
 * @brief Performs Depth-First Search (DFS) to find a path from start to end node.
 * @return True if a path is found, false otherwise.
 */
bool Search::DFS() {
  std::deque<Node> frontier;
  std::vector<int> generated_history;
  std::vector<int> inspected_history;

  std::vector<bool> is_generated(graph_.GetNumNodes(), false);

  Node start(start_node_, -1, 0.0);
  frontier.push_back(start);
  
  generated_history.push_back(start_node_ + 1);
  is_generated[start_node_] = true; 

  std::vector<Node> closed_list(graph_.GetNumNodes(), Node(-1, -2, 0.0));
  std::set<int> visited_ids; 

  int iteration = 1;

  while (!frontier.empty()) {
    std::cout << "Iteracion " << iteration++ << "\n";
    std::cout << "Nodos generados: ";
    PrintVector(generated_history);
    std::cout << "Nodos inspeccionados: ";
    PrintVector(inspected_history);
    std::cout << "--------------------------------------------------\n";

    Node current = frontier.back();
    frontier.pop_back();

    if (visited_ids.count(current.id)) {
      continue;
    }

    visited_ids.insert(current.id);
    closed_list[current.id] = current;
    inspected_history.push_back(current.id + 1);

    if (current.id == end_node_) {
      PrintPath(closed_list);
      return true;
    }

    std::vector<int> temp_generated;
    int num_nodes = graph_.GetNumNodes();
    
    for (int i = num_nodes - 1; i >= 0; --i) {
      double weight = graph_.GetEdgeCost(current.id, i);
      
      if (weight != -1.0 && !visited_ids.count(i)) {
        Node neighbor(i, current.id, current.cost_g + weight);
        frontier.push_back(neighbor);
        
        if (!is_generated[i]) {
          temp_generated.push_back(i + 1);
          is_generated[i] = true;
        }
      }
    }
    
    std::reverse(temp_generated.begin(), temp_generated.end());
    for(int id : temp_generated) {
      generated_history.push_back(id);
    }
  }

  std::cout << "No path found.\n";
  return false;
}


/**
 * @brief Prints the path found from start to end node and its total cost.
 * @param closed_list The list of nodes explored during the search.
 */
void Search::PrintPath(const std::vector<Node>& closed_list) const {
  std::vector<int> path;
  int curr_id = end_node_;
  double total_cost = closed_list[end_node_].cost_g;

  while (curr_id != -1) {
    path.push_back(curr_id);
    curr_id = closed_list[curr_id].father;
    if (path.size() > closed_list.size()) break; 
  }

  std::reverse(path.begin(), path.end());

  std::cout << "Camino: ";
  for (size_t i = 0; i < path.size(); ++i) {
    std::cout << (path[i] + 1) << (i < path.size() - 1 ? " - " : "");
  }
  std::cout << "\n--------------------------------------------------";
  std::cout << "\nCosto: " << std::fixed << std::setprecision(2) << total_cost << std::endl;
}