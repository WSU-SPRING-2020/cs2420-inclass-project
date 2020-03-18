#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include "sorting/byBubble.h"
#include "sorting/bySelection.h"
#include "sorting/byMerge.h"
#include "sorting/byQuick.h"
#include "sorting/byHeap.h"

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

  b = original;
  cs2420::SortByMerge<int> sbm { b };
  sbm.sort();
  cout << setw(25) << "Sorted by Merge: " << b << endl;

  b = original;
  cs2420::SortByQuick<int> sbq { b };
  sbq.sort();
  cout << setw(25) << "Sorted by Quick: " << b << endl;

  b = original;
  cs2420::SortByHeap<int> sbh { b };
  sbh.sort();
  cout << setw(25) << "Sorted by Heap: " << b << endl;

  return 0;
}