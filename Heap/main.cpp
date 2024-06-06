#include <iostream>

template<typename T>
class Node 
{
private:
  T item;

public: // both pointers are public for faster development
  Node<T>* lChild; // pointer to the left child
  Node<T>* rChild; // pointer to the right child

  // Getter for item
  T getItem() const noexcept { return item; }
  // Setter for item 
  void setItem(T &item) noexcept { this->item = item; }

  Node(T value) noexcept
    :item(value)
  {}

  ~Node() noexcept
  {}
};

template<typename T>
class Heap
{
private:
  Node<T>* root;

  // helper method to delete the heap recursively
  void deleteHeap(Node<T>* node) noexcept
  {
    if(node)
    {
      deleteHeap(node->lChild);
      deleteHeap(node->rChild);
      delete node;
    }
  }

public:

  Heap() noexcept
    :root(nullptr)
  {}

  ~Heap() noexcept
  {
    // calling helper method to delete the heap
    deleteHeap(root);
  }

};
int main()
{
  return 0;
}
