#include <iostream>
#include "linked_list/doubly.h"
using namespace std;

int main(){
  cs2420::List<int> lst { 2,3,5,7 };

  cout << lst << endl;

  lst.add_back(11).add_front(1);

  if(lst.find(17)){
    cout << "found" << endl;
  } else {
    cout << "not found" << endl;
  }

  for(int v : lst){
    cout << ": " << v << endl;
  }

  for(auto it = lst.begin(); it != lst.end(); ++it){
    cout << ":::   " << *it << endl;
  }
  return 0;
}