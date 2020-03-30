#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

namespace cs2420 {
  template <typename T>
  struct Node {
    T info;
    int height;
    Node *left;
    Node *right;
    Node(T info) : info(info), height(0), left(nullptr), right(nullptr) {}
    
    friend std::ostream& operator<<(std::ostream& out, const Node<T>&node){
      for(int i = 0; i < node.height; i++){
        out << "   ";
      }
      if(node.left || node.right) {
        out << "  " << node.info << std::endl;
      } else {
        out << "  " <<  node.info << std::endl;
      }
      return out;
    }
  };

  template <typename T>
  class AVLTree {
  public:
    AVLTree() : root(nullptr) {}
    AVLTree(const AVLTree<T> &bt) { copy(root, bt.root); }
    AVLTree<T> &operator=(AVLTree<T> &bt){
      if (this != &bt) {
        destroy(root);
        copy(root, bt.root);
      }

      return *this;
    }

    bool empty() const { return root == nullptr; }
    int height() const { return height(root); }
    int height(const Node<T> *node) const { return node ? node->height : 0; }
    int size() const { return size(root); }
    int size(const Node<T>* node) const {
      return node ? 1 + size(node->left) + size(node->right) : 0;
    }
    void preorderTraversal(std::ostream& out) const { 
      preorderTraversal(out, root); 
    }
    void inorderTraversal(std::ostream& out) const { 
      inorderTraversal(out, root); 
    }
    void postorderTraversal(std::ostream& out) const { 
      postorderTraversal(out, root); 
    }
    
    Node<T>* search(T e) const{
      auto current = root;
      while(current){
        if(current->info == e) return current;
        else if(e < current->info) current = current->left;
        else current = current->right;
      }

      return nullptr;
    }  

    void insert(T e){ 
      root = insert(root, e); 
    }
    void remove(T e){ 
      if(search(e)){
        root = remove(root, e); 
      }
    }


    ~AVLTree(){ destroy(root); }
    
  protected:
    Node<T> *root;
    void preorderTraversal(std::ostream& out, const Node<T> *node) const {
      if (node){
        out << *node;
        preorderTraversal(out, node->left);
        preorderTraversal(out, node->right);
      }
    }

    void inorderTraversal(std::ostream& out, const Node<T> *node ) const{
      if(node){
        inorderTraversal(out, node->left);
        out << *node;
        inorderTraversal(out, node->right);
      }
    }
    void postorderTraversal(std::ostream& out, const Node<T> *node) const {
      if(node){
        postorderTraversal(out, node->left);
        postorderTraversal(out, node->right);
        out << *node;
      }
    }

    Node<T>* insert( Node<T>* node, T e){
      if(node == nullptr){
        return new Node<T>(e);
      }else if(e < node->info) {
        node->left = insert(node->left, e);
      }else if(e > node->info) {
        node-> right = insert(node->right, e);
      }else{
        node->info = e;
        return node;
      }

      return balance(node);
    } 
    Node<T>* remove(Node<T>* node, T e){
      if(!node) {
        return node;
      } else if(e < node->info){
        node->left = remove(node->left, e);
      }else if(e > node->info){
        node->right = remove(node->right, e);
      }else {
        if(!node->left || !node->right){ // one or no children
          auto temp = node->left? node->left : node->right;
          if(temp){
            *node = *temp;
          }else{
            temp = node;
            node = nullptr;
          }
          delete temp;
        } else {// Two children
          auto temp = maximum(node->left);
          node->info = temp->info;
          node->left = remove(node->left, temp->info);
        }
      }
      
      if(node) return balance(node);
      else return node;
    }

    Node<T>* balance(Node<T>* node) {
      node->height = 1 + std::max(height(node->left), height(node->right));
      if ((height(node->left) - height(node->right)) < -1) {
        if ((height(node->right->left) - height(node->right->right)) > 0) {
          node->right = rotateRight(node->right);
        }
        
        node = rotateLeft(node);
      } else if ((height(node->left) - height(node->right)) > 1) {
        if ((height(node->left->left) - height(node->left->right)) < 0) {
          node->left = rotateLeft(node->left);
        }
        
        node = rotateRight(node);
      }

      return node;
    }

    Node<T>* rotateRight(Node<T>* x) {
      auto y = x->left;
      x->left = y->right;
      y->right = x;
      x->height = 1 + std::max(height(x->left), height(x->right));
      y->height = 1 + std::max(height(y->left), height(y->right));
      return y;
    }

    Node<T>* rotateLeft(Node<T>* x) {
      auto y = x->right;
      x->right = y->left;
      y->left = x;
      x->height = 1 + std::max(height(x->left), height(x->right));
      y->height = 1 + std::max(height(y->left), height(y->right));
      return y;
    }

    void destroy(Node<T>* &node) {
      if (node){
        destroy(node->left);
        destroy(node->right);

        delete node;
        node = nullptr;
      }
    }
    void copy(Node<T> *&dest, const Node<T> *src) {
      if (src){
        dest = new Node<T>(src->info);
        copy(dest->left, src->left);
        copy(dest->right, src->right);
      } else {
        dest = nullptr;
      }
    }

    const Node<T>* maximum() const { return maximum(root); }
    const Node<T>* maximum(Node<T>* node) const {
      if(node){
        while(node->right){
          node = node->right;
        } 
      }
      return node;
    }
  };
}
#endif