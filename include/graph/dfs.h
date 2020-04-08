#ifndef _CS2420_DFS_GRAPH_H
#define _CS2420_DFS_GRAPH_H
#include "graph.h"
#include <algorithm>

namespace cs2420 {
enum class VColor { WHITE, GREY, BLACK };
struct VertexAttr {
  VColor color = VColor::WHITE;
  int strime = 0;
  int ftime = 0;
};

class DepthFirstSearch {
public:
  DepthFirstSearch(Graph& g) : g(g), attr(new VertexAttr[g.V()]{}){
    for(int v = 0; v < g.V(); v++){
      if(attr[v].color == VColor::WHITE){
        dfs(v);
      }
    }
  }

  std::vector<int> preOrder() { return pre; }
  std::vector<int> postOrder() { return post; }
  std::vector<int> topologicalOrder() { 
    if(!g.directed()) throw std::runtime_error("Graph must be directed");
    
    std::vector<int> t = post;
    std::reverse(t.begin(), t.end());
    return t;
   }

  ~DepthFirstSearch() { delete [] attr; }
private:
  Graph& g;
  VertexAttr* attr;
  std::vector<int> pre, post;

  void dfs(int u){
    static int time = 0;

    attr[u].strime = ++time;
    attr[u].color = VColor::GREY;
    pre.push_back(u);
    for(int v : g.adjList(u)){
      if(attr[v].color == VColor::WHITE){
        dfs(v);
      }
    }
    attr[u].color = VColor::BLACK;
    attr[u].ftime = ++time;
    post.push_back(u);
  }

};

}

#endif