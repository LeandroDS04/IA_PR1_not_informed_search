/*
  Name: Leandro Delli Santi
  Date: 06/01/2026
  mail: alu0101584003@ull.edu.es
  Description: Logger class definition
*/

#include "graph.h"
#include "search.h"
#include "check_parameters.h"

#include <fstream>
#include <iostream>

int main(int argc, const char** argv) {
  CheckParameters(argc, argv);

  std::ofstream output_file(argv[2]);

  std::string input_filename = argv[1];
  int algorithm = std::stoi(argv[3]);
  int start_node = std::stoi(argv[4]);
  int end_node = std::stoi(argv[5]);

  std::streambuf* cout_buf = std::cout.rdbuf();
  std::cout.rdbuf(output_file.rdbuf());

  Graph graph;

  if (!graph.LoadFromFile(input_filename)) {
    return 1;
  }
  
  Search search(graph, start_node - 1, end_node - 1);
  search.PrintProblemInfo();
  search.Run(algorithm);

  std::cout.rdbuf(cout_buf);

  return 0;
}