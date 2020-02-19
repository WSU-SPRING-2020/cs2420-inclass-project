#include <iostream>
#include <string>
#include "stack.h"
#include "queue.h"

using namespace std;

int main(){
  string name = "Abdulmalek";

  cs2420::Stack<char> s;

  for(char c : name){
    s.push(c);
  }

  while(!s.empty()){
    cout << s.pop();
  }
  cout << endl;

  return 0;
}