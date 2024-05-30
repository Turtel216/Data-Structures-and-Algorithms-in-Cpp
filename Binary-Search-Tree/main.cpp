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
  void setValue(T item) noexcept { value = item; }
};

template<typename T>
class Tree
{
private:
  Node<T>* root;

  void traverseRecursively(Node<T>* node)
  {
    if (node != nullptr)
    {
      traverseRecursively(node->lChild);
      std::cout << " " << node->getValue() << "\n";
      traverseRecursively(node->rChild);
    }

  }

public:

  Tree() noexcept
    :root(nullptr)
  {}

  // Method to insert a new node into the tree
  void insert(T item) noexcept //TODO does not work!
  {
    // If the tree is empty set the new node as the root
    if (root == nullptr)
    {
      root = new Node<T>(item);
      return;
    }

    // Traverse the tree until a null child is found
    auto tempNode = root;
    while (tempNode != nullptr)
    {
      // if the item is <= the childs value, take the left path
      if (tempNode->getValue() <= item)
      {
        tempNode = tempNode->lChild;
        continue;
      }
      // if the item is > the childs value, take the right path
      else if (tempNode->getValue() > item)
      {
        tempNode = tempNode->rChild;
        continue;
      }
    }

    tempNode = new Node<T>(item); // causes bug!!!!
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
      else
      {
        tempNode = tempNode->rChild;
        continue;
      }
    }

    std::cout << "The item with the value of: " << item << " could not be found" << std::endl;
  }

  void remove(T item) noexcept
  {
    //TODO
  }

  // Displays the contents of the tree
  void display() noexcept
  {
    auto tempNode = root;
    // calling the recursive method
    traverseRecursively(tempNode);
  }
};

int main()
{
  Tree<int>* tree = new Tree<int>();
  tree->insert(5);
  tree->insert(2);
  tree->insert(8);
  tree->insert(3);
  tree->insert(4);

  std::cout << "Created tree with 5 nodes" << std::endl;
  tree->display();
  return 0;
}
