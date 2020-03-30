#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include "tree/avl_tree.h"

using namespace std;



int main(){
  cs2420::AVLTree<char> avl;
  for(char c = 'A'; c <= 'Z'; c++){
    avl.insert(c);
  }

  cout << "AVL Height: " << avl.height() << endl;
  avl.inorderTraversal(cout);

  return 0;
}