#ifndef _SORTING_BY_MERGE_H
#define _SORTING_BY_MERGE_H
#include "adt.h"

namespace cs2420 {
  template<typename T>
  class SortByMerge : public SortBy<T> {
  private:
    void sort(T* aux, int lo, int hi, bool reversed){
      if(hi <= lo) return;

      int mid = (lo + hi)/ 2;
      sort(aux, lo, mid, reversed);
      sort(aux, mid+1, hi, reversed);

      merge(aux, lo, mid, hi, reversed);
    }

    void merge(T* aux, int lo, int mid, int hi, bool reversed){
      int i = lo; 
      int j = mid + 1;
      for(int k = lo; k <= hi; k++){
        if(i > mid) aux[k] = this->elements[j++];
        else if( j > hi) aux[k] = this->elements[i++];
        else if (this->lessOrGreaterThan(i, j, reversed)){
          aux[k] = this->elements[i++];
        }else{
          aux[k] = this->elements[j++];
        }
      }

      for(int i = lo; i <= hi; i++){
        this->elements[i] = aux[i];
      }
    }
  public:
    SortByMerge(Bag<T>& bag) : SortBy<T>(bag) {}
    void sort(bool reversed = false){
      T* aux = new T[this->elements.getSize()];
      sort(aux, 0, this->elements.getSize() - 1, reversed);
      delete [] aux;
    }
  };

}

#endif