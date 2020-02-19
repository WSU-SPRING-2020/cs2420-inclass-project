#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "linked_list/doubly.h"

namespace cs2420 {

template <typename T>
class QueueADT {
public:
  virtual void enqueue(T e) = 0;
  virtual T dequeue() = 0;
  virtual T peek() const = 0;
  virtual void clear() = 0;
  virtual bool empty() const = 0;
  virtual ~QueueADT(){}
};

template<typename T>
class Queue : public QueueADT<T>{
private:
  List<T> lst;
public:
  Queue(): lst(List<T>()){}

  void enqueue(T e) { lst.add_back(e); }
  T dequeue() {
    if(empty()) throw std::runtime_error("Empty queue.");

    auto front = lst.begin();
    T e = *front;
    lst.remove_front();

    return e;
  }

  T peek() const {
    if(empty()) throw std::runtime_error("Empty queue.");

    auto front = lst.begin();
    return *front;
  }

  void clear() {
    lst.clear();
  }

  bool empty() const {
    return lst.empty();
  }
};

}

#endif
