#ifndef _DOUBLY_LINKED_LIST_H_
#define _DOUBLY_LINKED_LIST_H_
#include <initializer_list>

namespace cs2420 {

template<typename T>
struct Node {
  T info;
  Node<T>* next;
  Node<T>* prev;

  Node(T info): info(info), next(nullptr), prev(nullptr){}
  Node(T info, Node<T>* nxt, Node<T>* prv): info(info), next(nxt), prev(prv){}
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
    auto node = new Node<T>(info, nullptr, back);
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
    auto node = new Node<T>(info, front, nullptr);
    if(front){
      front->prev = node;
      front = node;
    } else {
      back = front = node;
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
      front->prev = nullptr;
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
      auto pred = back->prev;
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
      front->prev = nullptr;
      delete tmp;
      sz--;
      return true;
    } else {
      auto current = front->next;
      while(current){
        if(current->info == info){

          if(current == back){
            back = current->prev;
          } else {
            current->next->prev = current->prev;
          }
            
          current->prev->next = current->next;
          delete current;
          sz--;
          return true;
        }

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

  ListIterator<T> begin(){return ListIterator<T>(front); }
  ListIterator<T> end(){return ListIterator<T>(back->next); }

  friend std::ostream& operator<<(std::ostream& out,  const List<T>& lst){
    auto current = lst.front;
    while(current){
      out << current->info << " ";

      current = current->next;
    }

    return out;
  }
  bool empty() const { return sz == 0; }
  unsigned size() const { return sz; }
  
  void clear(){ removeAll(); }
  ~List(){
    removeAll();
  }

protected:
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