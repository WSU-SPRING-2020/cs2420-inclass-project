#ifndef _CS2420_SORTING_BY_HEAP_H_
#define _CS2420_SORTING_BY_HEAP_H_
#include "adt.h"

namespace cs2420 {
  template<typename T>
  class SortByHeap : public SortBy<T> {
  public:
    SortByHeap(Bag<T>& bag) : SortBy<T>(bag){}
    void sort(bool reversed = false){
      buildHeap(reversed);
      for(int i = this->elements.getSize()  - 1; i > 0; i--){
        this->swap(0, i);
        heapify(0, i, reversed);
      }
    }
  private:
    void buildHeap(bool reversed){
      for(int i = this->elements.getSize() / 2 - 1; i >= 0; i--){
        heapify(i, this->elements.getSize(), reversed);
      }
    }

    void heapify(int p, int hsz, bool reversed){
      int left = 2 * p + 1;
      int right = left + 1;
      int largest = p;
      if(left < hsz && this->lessOrGreaterThan(p , left, reversed)) {
        largest = left;
      }

      if(right < hsz && this->lessOrGreaterThan(largest , right, reversed)) {
        largest = right;
      }

      if(largest != p){
        this->swap(p, largest);
        heapify(largest, hsz, reversed);
      }
    }
  };

}

#endif