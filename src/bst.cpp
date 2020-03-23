#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include "tree/bst.h"

using namespace std;

int random(int min, int max){
  static default_random_engine en;
  static uniform_int_distribution dist {min, max};
  return dist(en);
}

template<typename T>
void showNode(const cs2420::Node<T>* node, int depth){
  if(node){
    for(int i = 0; i < depth; i++) { std::cout << "  "; }
    std::cout << node->info << std::endl;
  }
}

int main(){
  cs2420::BST<int> bt;

  cout << bt.size() << endl;

  for(int i = 0; i < 17; i++){
    int r = random(1, 99);
    if(!bt.search(r)) { bt.insert(r); }
  }
  cout << "\n===========\n" << endl;
  bt.traverse(cs2420::Traversal::IN_ORDER, showNode);
  cout << "\n===========\n" << endl;

  cout << bt.search(20) << endl;
  cout << bt.search(79) << endl;
  cout << bt.search(17) << endl;
  cout << "\n===========\n" << endl;
  bt.traverse(cs2420::Traversal::IN_ORDER, showNode);
  cout << "\n===========\n" << endl;

  bt.remove(70);
  cout << "\n===========\n" << endl;
  bt.traverse(cs2420::Traversal::IN_ORDER, showNode);
  cout << "\n===========\n" << endl;

  bt.remove(3);
  cout << "\n===========\n" << endl;
  bt.traverse(cs2420::Traversal::IN_ORDER, showNode);
  cout << "\n===========\n" << endl;
  
  cout << bt.size() << endl;

  return 0;
}