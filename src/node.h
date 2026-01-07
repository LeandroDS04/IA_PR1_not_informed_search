/*
  Name: Leandro Delli Santi
  Grade: 3rd Year
  mail: alu0101584003@ull.edu.es
  Subject: IA (Artificial Inteligence)
  School: ESIT (Escuela Superior de Ingenieria y Tecnología)
  Theme of the practice: Not informed searching
  Date: 06/01/2026
  File: node.h - declaration of the Node struct.
*/

#ifndef NODE_H
#define NODE_H

struct Node {
  int id;          
  int father;       
  double cost_g;  

  Node(int i, int f, double c) : id(i), father(f), cost_g(c) {}
  
  bool operator==(const Node& other) const {
    return id == other.id;
  }
};

#endif // NODE_H