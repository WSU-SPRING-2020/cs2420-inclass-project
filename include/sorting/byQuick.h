#ifndef _SORTING_BY_QUICK_H
#define _SORTING_BY_QUICK_H
#include "adt.h"
#include <cstdlib>

namespace cs2420 {
  template<typename T>
  class SortByQuick : public SortBy<T> {
  private:
    void sort(int lo, int hi, bool reversed){
      if(lo < hi){
        int m = partition(lo, hi, reversed);
        sort(lo, m-1, reversed);
        sort(m+1, hi, reversed);
      }
    }

    int partition(int lo, int hi, bool reversed){
      int p = rand() % (hi - lo + 1) + lo;
      this->swap(p, hi);
      int i = lo - 1;
      for(int j = lo; j < hi; j++){
        if(this->lessOrGreaterThan(j, hi, reversed)){
          this->swap(++i, j);
        }
      }

      this->swap(i+1, hi);
      return i+1;
    }
  public:
    SortByQuick(Bag<T>& bag) : SortBy<T>(bag) {}
    void sort(bool reversed = false){
      sort(0, this->elements.getSize() - 1, reversed);
    }
  };

}

#endif