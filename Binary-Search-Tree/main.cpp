#include <exception>
#include <iostream>
#include <ostream>
#include <string>

//TODO comment out traverse methods

// Exception for when a specified node could not be found
class NodeNotFoundException : std::exception
{
private:
  std::string message;

public:
  NodeNotFoundException(const char* msg) noexcept
    : message(msg)
  {}

  const char* what() const throw()
  {
    return message.c_str();
  }
};

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

  ~Node() { delete value; }

  //Getter for value
  T getValue() const noexcept { return value; }
  void setValue(T item) noexcept { value = item; }
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

  ~Tree() { delete[] root; }

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
        // If the left child is empty, insert the new item there
        if (tempNode->lChild == nullptr)
        {
          tempNode->lChild = new Node<T>(item);
          return;
        }

        tempNode = tempNode->lChild;
      }
      // if the item is > the childs value, take the right path
      else
      {
        // If the right child is empty, insert the new item there
        if (tempNode->rChild == nullptr)
        {
          tempNode->rChild = new Node<T>(item);
          return;
        }

        tempNode = tempNode->rChild;
      }
    }
  }

  // searches a specific item from the tree
  Node<T>* search(T item)
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

    throw NodeNotFoundException("The request item could not be foudn");
  }

  void remove(T item) noexcept
  {
    // search for the node 
    auto node = search(item);

    // If the node is a lead node, delete the node
    if (node->lChild == nullptr && node->rChild == nullptr)
    {
      delete node;
      return;
    }
    // If the node has a single left child, copy the child and delete the node
    else if (node->lChild == nullptr)
    {
      auto deleteme = node;
      node = node->lChild;
      delete node;
      return;
    }
    // If the node has a single right child, copy the child and delete the node
    else if (node->rChild == nullptr)
    {
      auto deleteme = node;
      node = node->rChild;
      delete node;
      return;
    }
    // else delete the node with both children and replace it with the inorder successor
    else 
    {
      //TODO
    }
  }

  void inorder()
  {
    Node<T>* node = root;

    if (node == nullptr)
      return;

    inorder(node->lChild);
    std::cout << " " << node->getValue() << "\n";
    inorder(node->rChild);
  }

  void inorder(Node<T>* node)
  {
    if (node == nullptr)
      return;

    inorder(node->lChild);
    std::cout << " " << node->getValue() << "\n";
    inorder(node->rChild);
  }

  void preorder()
  {
    Node<T>* node = root;

    if (node == nullptr)
      return;

    std::cout << " " << node->getValue() << "\n";

    preorder(node->lChild);
    preorder(node->rChild);
  }

  void preorder(Node<T>* node)
  {
    if (node == nullptr)
      return;

    std::cout << " " << node->getValue() << "\n";

    preorder(node->lChild);
    preorder(node->rChild);
  }

  void postorder()
  {
    Node<T>* node = root;

    if (node == nullptr)
      return;

    postorder(node->lChild);
    postorder(node->rChild);

    std::cout << " " << node->getValue() << "\n";
  }

  void postorder(Node<T>* node)
  {
    if (node == nullptr)
      return;

    postorder(node->lChild);
    postorder(node->rChild);
    
    std::cout << " " << node->getValue() << "\n";
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

  std::cout << "Created tree with 5 nodes" << "\n" << "Displaying BST inorder" << std::endl;
  tree->inorder();
  
  std::cout << "Displaying BST preorder" << std::endl;
  tree->preorder();

  std::cout << "Displaying BST postorder" << std::endl;
  tree->postorder();

  std::cout << "Searching for node with value 8" << std::endl;
  std::cout << "Found node with value: " << tree->search(8)->getValue() << std::endl; //TODO should be in try catch
  
  return 0;
}
