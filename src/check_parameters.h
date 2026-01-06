/*
  Name: Leandro Delli Santi
  Grade: 3rd Year
  mail: alu0101584003@ull.edu.es
  Subject: IA (Artificial Inteligence)
  School: ESIT (Escuela Superior de Ingenieria y Tecnología)
  Theme of the practice: Not informed searching
  Date: 06/01/2026
  File: check_parameters.h - declaration of the constant message and the function CheckParameters.
*/

#ifndef CHECK_PARAMETERS_H_
#define CHECK_PARAMETERS_H_

#include <string>

const std::string kHelpMessage =
  "./pr1_IA_lds [--help] filein.txt fileout.txt <algorithm> <node_begin> <node_objetive>\n"
  "  - input_file: The file where the data is taken from\n"
  "  - output_file: The file where the results are written\n"
  "  - Algorithm: 0 for DFS, 1 for BFS\n"
  "  - Begin: The node where the search starts\n"
  "  - Objetive: The node where the search ends\n";

void CheckParameters(const int, const char**);

#endif