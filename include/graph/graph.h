#ifndef _CS2420_GRAPH_H
#define _CS2420_GRAPH_H
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <sstream>

namespace cs2420 {

class Graph {
protected:
  const int v;
  int e = 0;
  std::list<int> *adj;

public:
  Graph(int v) : v(v), adj(new std::list<int>[v]{}){}

  int V() { return v; }
  int E() { return e; }
  std::list<int> adjList(int v) { return adj[v]; }
  virtual bool directed(){ return false; }

  virtual void addEdge(int v, int w){
    e++;
    adj[v].push_back(w);
  }

  virtual void removeEdge(int v, int w){
    e--;
    adj[v].remove(w);
  }

  virtual int degree(int v){
    return adj[v].size();
  }

  virtual ~Graph() { delete[] adj; }

  friend void operator>>(std::istream& in, Graph &g){
    std::string line;
    while(std::getline(in, line)){
      if(!line.empty()){
        std::stringstream ss(line);
        int u; ss >> u;
        char sep; ss >> sep;
        int v;
        while(ss >> v){
          g.addEdge(u, v);
        }
      }
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const Graph &g){
    out << g.v << std::endl;
    out << g.e << std::endl;
    for(int v = 0; v < g.v; v++){
      out << v << ": ";
      for(int w : g.adj[v]){
        out << w << " ";
      }
      out << std::endl;
    }

    return out;
  }

};

}

#endif