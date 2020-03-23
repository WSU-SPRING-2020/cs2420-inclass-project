#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

namespace cs2420 {
  template <typename T>
  struct Node {
    T info;
    Node *left;
    Node *right;
    Node(T info) : info(info), left(nullptr), right(nullptr) {}
  };

  enum class Traversal { PRE_ORDER, IN_ORDER, POST_ORDER };
  // Implemenation
  template <typename T>
  void copy(Node<T> *&destRoot, const Node<T> *srcRoot){
    if (srcRoot) {
      destRoot = new Node<T>(srcRoot->info);
      copy(destRoot->left, srcRoot->left);
      copy(destRoot->right, srcRoot->right);
    }
    else {
      destRoot = nullptr;
    }
  }

  template <typename T>
  class BST {
  private:
    Node<T> *root;

  public:
    BST(): root(nullptr) {}
    BST(const BST<T> &bt){
      copy(root, bt.root);
    }
    BST<T> &operator=(const BST<T> &bt){
      if (this != &bt) {
        destroy(root);
        copy(root, bt.root);
      }

      return *this;
    }
    void setRoot(Node<T> *node) { this->root = node; }

    bool empty() const { return !root; }

    int size() const { return size(root); }

    void traverse(Traversal type, void (*displayNode)(const Node<T>*, int)) const {
      traverse(type, root, 0, displayNode);
    }

    bool search(T e) const {
      auto current = root;
      while(current){
        if(e == current->info){
          return true;
        }else if(e < current->info){
          current = current->left;
        }else{
          current = current->right;
        }
      }

      return false;
    }  

    void insert(T e){
      if(this->root){
        auto current = this->root;
        Node<T>* parent = nullptr;
        while(current){
          parent = current;
          if(current->info == e){
            throw std::runtime_error("element is already in the list");
          }else if(e < current->info){
            current = current->left;
          }else if(e > current->info){
            current = current->right;
          }
        }

        if(e < parent->info){
          parent->left = new Node<T>(e);
        }else{
          parent->right = new Node<T>(e);
        }
      } else{
        this->root = new Node<T>(e);
      }
    } 

    void remove(T e){
      // Search of the node to be deleted
      auto node = this->root;
      Node<T>* parent = nullptr;
      bool is_left_child = false;
      while(node){
        if(node->info == e){
          break;
        }else {
          parent = node;
          if(e < node->info){
            is_left_child = true;
            node = node->left;
          }else if(e > node->info){
            is_left_child = false;
            node = node->right;
          }
        }
      }

      if(node){
        // Node has no children
        if(!node->left && !node->right) {
          if(is_left_child){
            parent->left = nullptr;
          }else{
            parent->right = nullptr;
          }
        }else if(node->left && !node->right){
          // Node has not right child
          if(is_left_child){
            parent->left = node->left;
          }else{
            parent->right = node->left;
          }
        }else if(!node->left && node->right){
          // Node has no left
          if(is_left_child){
            parent->left = node->right;
          }else{
            parent->right = node->right;
          }
        }else{
          // Node has both left and right children
          // First find maximum on the left side
          auto current = node->left;
          Node<T>* beforeCurrent = nullptr;
          while(current->right){
            beforeCurrent = current;
            current = current->right;
          }

          node->info = current->info;

          if(beforeCurrent){
            beforeCurrent->right = current->left;
          }else{
            node->left = current->left;
          }

          // Node to delete
          node = current;
        }
        
        delete node;
        node = nullptr;
      }
    }

    ~BST(){ destroy(root); }
    void destroy(Node<T> *node){
      if (node) {
        destroy(node->left);
        destroy(node->right);

        delete node;
        node = nullptr;
      }
    }
  private:
    int size(Node<T>* node) const {
      if(node) {
        return 1 + size(node->left) + size(node->right);
      }else{
        return 0;
      }
    }

    void traverse(Traversal type, Node<T>* node, int depth, void (*displayNode)(const Node<T>*, int)) const {
      if(node){
        switch(type){
        case Traversal::PRE_ORDER:
          displayNode(node, depth);
          traverse(type, node->left, depth+1, displayNode);
          traverse(type, node->right, depth+1, displayNode);
          break;
        case Traversal::IN_ORDER:
          traverse(type, node->left, depth+1, displayNode);
          displayNode(node, depth);
          traverse(type, node->right, depth+1, displayNode);
          break;
        case Traversal::POST_ORDER:
          traverse(type, node->left, depth+1, displayNode);
          traverse(type, node->right, depth+1, displayNode);
          displayNode(node, depth);
          break;
        }
      }
    }
  };
}

#endif