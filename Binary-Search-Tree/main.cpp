#include <iostream>

template<typename T>
class Node 
{
private:
  T value;

public: // both pointers are publac for faster development
  Node* lChild; // pointer to the left child
  Node* rChild; // pointer to he right child

  Node(T item) noexcept
    :value(item)
  {}

  //Getter for value
  T getValue() const noexcept { return value; }
};

template<typename T>
class Tree
{
private:
  Node<T>* root;

public:

  Tree() noexcept
    :root(nullptr)
  {}

  // Method to insert a new node into the tree
  void insert(T item) noexcept
  {
    // If the tree is empty set the new node as the root
    Node<T>* newNode = new Node<T>(item);
    if (root != nullptr)
    {
      root = newNode;
      return;
    }

    // Traverse the tree until a null child is found
    auto tempNode = root;
    while(tempNode != nullptr)
    {
      // if the item is <= the childs value, take the left path
      if(tempNode->getValue() <= item)
      {
        tempNode = tempNode->lChild;
        continue;
      }
      // if the item is > the childs value, take the right path
      else if (tempNode->getValue() > item)
      {
        tempNode = tempNode->rChild;
      }

      // set the new node equal to the correct null child
      tempNode = newNode;
    }

  }

  // searches a specific item from the tree
  Node<T>* search(T item) noexcept
  {
    // Traverse the tree until a null child is found
    auto tempNode = root;
    while(tempNode != nullptr)
    {
      // If the item is found, return the node
      if (tempNode->getValue() == item)
        return tempNode;

      // if the item is <= the childs value, take the left path
      else if(tempNode->getValue() < item)
      {
        tempNode = tempNode->lChild;
        continue;
      }
      // if the item is > the childs value, take the right path
      else if (tempNode->getValue() > item)
      {
        tempNode = tempNode->rChild;
      }
    }

    std::cout << "The item with the value of: " << item << " could not be found" << std::endl;
  }

  void remove(T item) noexcept
  {
    //TODO
  }

  // Displays the contents of the tree
  void display() const noexcept
  {
    //TODO
  }
};

int main()
{
  return 0;
}
