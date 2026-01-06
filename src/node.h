/*
  Name: Leandro Delli Santi
  Date: 06/01/2026
  mail: alu0101584003@ull.edu.es
  Description: Node structure definition
  file: node.h
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