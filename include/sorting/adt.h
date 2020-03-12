#ifndef _SORTING_ADT_H
#define _SORTING_ADT_H
#include "bag.h"

namespace cs2420 {
  template<typename T>
  class SortBy {
  public:
    SortBy(Bag<T>& bag) : elements(bag) {}
    virtual void sort(bool reversed = false) = 0;

  protected:
    Bag<T>& elements;

    virtual int findMinOrMax(int start, int sz, bool reversed){
      int result = start;
      for(int i = start; i < sz; i++){
        if(lessOrGreaterThan(i, result, reversed)){
          result = i;
        }
      }

      return result;
    }
    virtual bool lessOrGreaterThan(int i, int j, bool reversed){
      return (reversed && elements[i] > elements[j]) ||
        (!reversed && elements[i] < elements[j]);
    }

    virtual void swap(int i, int j){
      T tmp = elements[i];
      elements[i] = elements[j];
      elements[j] = tmp;
    }
  };

}

#endif