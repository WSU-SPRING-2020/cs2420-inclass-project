#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include "sorting/byBubble.h"
#include "sorting/bySelection.h"

using namespace std;
int random(int min, int max){
  static default_random_engine en;
  static uniform_int_distribution dist {min, max};
  return dist(en);
}

int main() {
  const int MAX_SIZE = 15;
  Bag<int> original;
  for(int i = 0 ; i < MAX_SIZE; i++){
    original.add(random(1, 99));
  }

  cout << setw(25) << "Original: " << original << endl;
  Bag<int> b = original;
  cs2420::SortByBubble<int> sbb { b };
  sbb.sort();
  cout << setw(25) << "Sorted by Bubble: " << b << endl;

  cout << setw(25) << "Original: " << original << endl;

  b = original;
  cs2420::SortBySelection<int> sbs { b };
  sbs.sort();
  cout << setw(25) << "Sorted by Selection: " << b << endl;
  return 0;
}