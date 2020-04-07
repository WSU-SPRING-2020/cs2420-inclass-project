#ifndef _CS2420_DIGRAPH_H
#define _CS2420_DIGRAPH_H
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <sstream>
#include "graph.h"

namespace cs2420 {

class Digraph : public Graph {
protected:
  int *indegree;

public:
  Digraph(int v) : Graph(v), indegree(new int[v]{}){}

  void addEdge(int v, int w){
    Graph::addEdge(v, w);
    indegree[w]++;
  }

  virtual void removeEdge(int v, int w){
    Graph::removeEdge(v, w);
    indegree[w]--;
  }

  int inDegree(int v){
    return indegree[v];
  }
  int outDegree(int v){
    return adj[v].size();
  }

  int degree(int v){
    return inDegree(v) + outDegree(v);
  }

  ~Digraph() { delete[] indegree; }

};

}

#endif