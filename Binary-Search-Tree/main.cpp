#include <iostream>

template<typename T>
class Node 
{
private:
  T value;

public: // both pointers are public for faster development
  Node* lChild; // pointer to the left child
  Node* rChild; // pointer to he right child
};

template<typename T>
class Tree
{
private:
  Node<T>* root;
};

int main()
{
  return 0;
}
