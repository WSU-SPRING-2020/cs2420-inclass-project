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
class ListIterator {
private:
  Node<T>* current = nullptr;
public:
  ListIterator(Node<T>* node): current(node){}
  T operator*(){
    return current->info;
  }
  ListIterator<T>& operator++(){
    current = current->next;
    return *this;
  }

  bool operator==(ListIterator<T>& rhs){
    return current == rhs.current;
  }

  bool operator!=(ListIterator<T>& rhs){
    return current != rhs.current;
  }

  operator bool() const{
    return current;
  }
};

template<typename T>
class List{
public:
  List(){}
  List(const List<T>& lst) {
    Node<T>* current = lst.front;
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

  List<T>& add_front(T info){
    front = new Node<T>(info, front);
    if(!back){
      back = front;
    }

    sz++;
    return *this;
  }

  bool remove_front(){
    if(front == back){
      if(!front){
        return false;
      }

      delete front;
      front = back = nullptr;
    } else{
      auto tmp = front;
      front = front->next;
      delete tmp;
    }

    sz--;
    return true;
  }

  bool remove_back(){
    if(front == back){
      if(!front){
        return false;
      }

      delete back;
      front = back = nullptr;
    } else{
      auto pred = front;
      while(pred->next != back){
        pred = pred->next;
      }

      pred->next = nullptr;
      delete back;
      back = pred;
    }

    sz--;
    return true;
  }

  bool remove(T info){
    if(!front){
      return false;
    }else if(front->info == info){
      auto tmp = front;
      front = front->next;
      delete tmp;
      sz--;
      return true;
    } else {
      auto pred = front;
      auto current = front->next;
      while(current){
        if(current->info == info){
          pred->next = current->next;
          if(!pred->next){
            back = pred;
          }

          delete current;
          sz--;
          return true;
        }

        pred = current;
        current = current->next;
      }
    }

    return false;
  }


  ListIterator<T> find(T info){
    auto current = front;
    while(current){
      if(current->info == info){
        return ListIterator<T>(current);
      }

      current = current->next;
    }

    return ListIterator<T>(nullptr);
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