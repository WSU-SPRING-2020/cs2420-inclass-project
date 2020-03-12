#ifndef _SORTING_BY_BUBBLE_H
#define _SORTING_BY_BUBBLE_H
#include "adt.h"

namespace cs2420 {
  template<typename T>
  class SortByBubble : public SortBy<T> {
  public:
    SortByBubble(Bag<T>& bag) : SortBy<T>(bag) {}
    void sort(bool reversed = false){
      for(int i = 0; i < this->elements.getSize() - 1; i++){
        for(int j = 0; j < this->elements.getSize() - i - 1; j++){
          if(this->lessOrGreaterThan(j+1, j, reversed)){
            this->swap(j+1, j);
          }
        }
      }
    }
  };

}

#endif