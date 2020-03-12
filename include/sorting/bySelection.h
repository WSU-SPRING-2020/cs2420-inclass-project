#ifndef _SORTING_BY_SELECTION_H
#define _SORTING_BY_SELECTION_H
#include "adt.h"

namespace cs2420 {
  template<typename T>
  class SortBySelection : public SortBy<T> {
  public:
    SortBySelection(Bag<T>& bag) : SortBy<T>(bag) {}
    void sort(bool reversed = false){
      for(int i = 0; i < this->elements.getSize(); i++){
        this->swap(i, this->findMinOrMax(i, this->elements.getSize(), reversed));
      }
    }
  };

}

#endif