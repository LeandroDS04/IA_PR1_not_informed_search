/*
  Name: Leandro Delli Santi
  Date: 06/01/2026
  mail: alu0101584003@ull.edu.es
  Description: Search class implementation using Node struct.
  file: search.cc
*/

#include "search.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <deque>

Search::Search(const Graph& graph, int start_node, int end_node)
    : graph_(graph), start_node_(start_node), end_node_(end_node) {}

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

void Search::PrintProblemInfo() const {
  int num_nodes = graph_.GetNumNodes();
  int num_edges = 0;
  for (int i = 0; i < num_nodes; ++i) {
      // CAMBIO AQUÍ: j empieza en i + 1
      // Esto evita comparar (0,0) y evita contar (1,0) si ya contaste (0,1)
      for (int j = i + 1; j < num_nodes; ++j) {
          
          // Asumiendo que -1.0 es "no hay camino"
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

bool Search::Run(int algorithm_type) {
  return (algorithm_type == 1) ? BFS() : DFS();
}

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
    std::cout << "Iteracion " << iteration++ << "\n";
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

bool Search::DFS() {
  std::deque<Node> frontier;
  std::vector<int> generated_history;
  std::vector<int> inspected_history;

  // Vector auxiliar para saber SIEMPRE si un nodo ya entró en la lista de generados.
  // Esto evita los duplicados visuales en la tabla.
  std::vector<bool> is_generated(graph_.GetNumNodes(), false);

  Node start(start_node_, -1, 0.0);
  frontier.push_back(start);
  
  generated_history.push_back(start_node_ + 1);
  is_generated[start_node_] = true; // Marcamos el inicial

  // En DFS marcamos visitado al SACAR de la pila
  std::vector<Node> closed_list(graph_.GetNumNodes(), Node(-1, -2, 0.0));
  std::set<int> visited_ids; 

  int iteration = 1;

  while (!frontier.empty()) {
    // --- PASO 1: IMPRIMIR ---
    std::cout << "Iteracion " << iteration++ << "\n";
    std::cout << "Nodos generados: ";
    PrintVector(generated_history);
    std::cout << "Nodos inspeccionados: ";
    PrintVector(inspected_history);
    std::cout << "--------------------------------------------------\n";

    // --- PASO 2: INSPECCIONAR ---
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

    // --- PASO 3: GENERAR ---
    std::vector<int> temp_generated;
    int num_nodes = graph_.GetNumNodes();
    
    // Iteramos inversamente para orden de pila
    for (int i = num_nodes - 1; i >= 0; --i) {
      double weight = graph_.GetEdgeCost(current.id, i);
      
      // Si existe arista y el destino no ha sido cerrado (visitado)
      if (weight != -1.0 && !visited_ids.count(i)) {
        Node neighbor(i, current.id, current.cost_g + weight);
        frontier.push_back(neighbor);
        
        // CORRECCION AQUI:
        // Solo añadimos a la lista visual si NUNCA antes se había generado.
        if (!is_generated[i]) {
            temp_generated.push_back(i + 1);
            is_generated[i] = true;
        }
      }
    }
    
    // Invertimos para orden ascendente visual
    std::reverse(temp_generated.begin(), temp_generated.end());
    for(int id : temp_generated) {
        generated_history.push_back(id);
    }
  }

  std::cout << "No path found.\n";
  return false;
}

void Search::PrintPath(const std::vector<Node>& closed_list) const {
  std::vector<int> path;
  int curr_id = end_node_;
  double total_cost = closed_list[end_node_].cost_g;

  // Backtracking desde el destino hasta el origen usando los padres
  while (curr_id != -1) {
    path.push_back(curr_id);
    curr_id = closed_list[curr_id].father; // Subimos al padre
    
    // Seguridad para evitar bucles infinitos si hubiera error
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