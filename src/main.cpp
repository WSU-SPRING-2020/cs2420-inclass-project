#include <iostream>
#include <string>
#include "smart_bag.h"

using namespace std;

int main(){
  SmartBag<string> b1;
  b1.add("Hello");
  b1.add("World1");


  cout << b1 << endl;


  return 0;
}