#ifndef _STACK_H_
#define _STACK_H_

#include "linked_list/doubly.h"

namespace cs2420 {

template <typename T>
class StackADT {
public:
  virtual void push(T e) = 0;
  virtual T pop() = 0;
  virtual T top() const = 0;
  virtual void clear() = 0;
  virtual bool empty() const = 0;
  virtual ~StackADT(){}
};

template<typename T>
class Stack : public StackADT<T>, private List<T>{
public:
  Stack(): List<T>(){}
  void push(T e) { this->add_front(e); }
  T pop() {
    if(this->sz == 0) throw std::runtime_error("Empty stack.");
    T e = this->front->info;
    this->remove_front();

    return e;
  }

  T top() const {
    if(empty()) throw std::runtime_error("Empty stack.");
  
    return this->front->info;
  }

  void clear() {
    List<T>::clear();
  }

  bool empty() const {
    return this->sz == 0;
  }
};

}

#endif
