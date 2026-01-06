/*
  Name: Leandro Delli Santi
  Grade: 3rd Year
  Subject: IA (Artificial Inteligence)
  School: ESIT (Escuela Superior de Ingenieria y Tecnología)
  Theme of the practice: Not informed searching
  Date: 26/09/2025
  File: check_parameters.cc - definition of the function CheckParameters.
*/

#include "check_parameters.h"

#include <iostream>
#include <cstdlib>

void CheckParameters(const int argc, const char** argv) {
  if (argc < 2) {
    std::cerr <<  "$ ./pr1_IA_lds\n"
                  "How to use it: ./pr1_IA_lds filein.txt fileout.txt <algorithm> <node_begin> <node_objetive>\n"
                  "Try ./pr1_IA_lds --help for more information.\n";
    std::exit(1);
  }
  std::string first_arg{argv[1]};
  if (first_arg == "--help") {
    std::cout << kHelpMessage;
    std::exit(0);
  }
  if (argc > 6) {
    std::cerr <<  "$ ./pr1_IA_lds\n"
                  "How to use it: ./pr1_IA_lds filein.txt fileout.txt <algorithm> <node_begin> <node_objetive>\n"
                  "Try ./pr1_IA_lds --help for more information.\n";
    std::exit(1);
  }
}