#include <iostream>
#include <fstream>
#include "graph/graph.h"
#include "graph/digraph.h"

using namespace std;

int main(){

  cs2420::Graph ug(14);
  ifstream in("../src/resources/tinyUG.txt");
  in >> ug;
  cout << ug;
  in.close();

  cout << "\n\n\n\n";

  cs2420::Digraph dg(13);
  ifstream in2("../src/resources/tinyDG.txt");
  in2 >> dg;
  cout << dg;
  in2.close();
  

  return 0;
}