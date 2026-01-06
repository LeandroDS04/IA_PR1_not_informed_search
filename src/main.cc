/*
  Name: Leandro Delli Santi
  Date: 06/01/2026
  mail: alu0101584003@ull.edu.es
  Description: Logger class definition
*/

#include "graph.h"
#include "logger.h"
#include "search.h"
#include "check_parameters.h"

#include <iostream>

int main(int argc, const char** argv) {
  CheckParameters(argc, argv);

  std::string input_filename = argv[1];
  int algorithm = std::stoi(argv[2]);
  int start_node = std::stoi(argv[3]);
  int end_node = std::stoi(argv[4]);

  std::cout << "--- Configuration ---\n";
  std::cout << "Input File: " << input_filename << "\n";
  std::cout << "Algorithm:  " << (algorithm == 0 ? "DFS" : "BFS") << "\n";
  std::cout << "Start Node: " << start_node << "\n";
  std::cout << "End Node:   " << end_node << "\n";
  std::cout << "---------------------\n";

  Graph graph;

  if (!graph.LoadFromFile(input_filename)) {
    return 1;
  }

  std::cout << graph << std::endl;

  return 0;
}