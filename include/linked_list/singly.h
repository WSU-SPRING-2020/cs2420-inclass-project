#ifndef _SINGLY_LINKED_LIST_H_
#define _SINGLY_LINKED_LIST_H_
#include <initializer_list>

namespace cs2420 {

template<typename T>
struct Node {
  T info;
  Node<T>* next;

  Node(T info): info(info), next(nullptr){}
  Node(T info, Node<T>* ptr): info(info), next(ptr){}
};

template<typename T>
class List{
public:
  List(){}
  List(const List<T>& lst) {
    auto current = lst.front;
    while(current){
      add_back(current->info);
      current = current->next;
    }
  }

  List(const std::initializer_list<T>& lst){
    for(auto it = lst.begin(); it != lst.end(); ++it){
      add_back(*it);
    }
  }

  List<T>& operator=(const List<T>& lst) {
    removeAll();
    auto current = lst.front;
    while(current){
      add_back(current->info);
      current = current->next;
    }

    return *this;
  }

  List<T>& add_back(T info){
    auto node = new Node<T>(info);
    if(back){ // list is not empty
      back->next = node;
      back = node;
    }else{
      front = back = node;
    }

    sz++;
    return *this;
  }

  ~List(){
    removeAll();
  }

private:
  unsigned sz = 0;
  Node<T>* front = nullptr;
  Node<T>* back = nullptr;

  void removeAll(){
    auto current = front;
    while(current){
      auto tmp = current;
      current = current->next;
      delete tmp;
    }

    front = nullptr;
    back = nullptr;
    sz = 0u;
  }
};

}


#endif