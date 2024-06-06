#include <exception>
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>

/*
This is an implementation of a Binary-Search-Tree(BST) using templates.
The Tree class has the following methods:
    - 'insert' which adds a new node to the tree.

    - 'inorder' which traverses the tree inorder:
          left sub-tree -> root -> right sub-tree

    - 'preorder' which traverses the tree preorder:
          root -> left sub-tree -> right sub-tree

    - 'postorder' which traverses the tree postorder:
          left sub-tree -> right sub-tree -> root

    - 'remove' which removes a given item from the tree.

    - 'search' which searches and returns the node that holds a given item.
    The method throws a NodeNotFoundException exception when no node is found.

    - 'searchParentAndChild' is a private helper method that returns a tuple
    containing the node that holds a given item and its parent.The method throws
    a NodeNotFoundException exception when no node is found.

    - 'deleteTree' is a private helper method that deletes the tree recursively.


The Node class has getters and setters for the value it holds

   The tree used in the tests has the following structure
                        50
                      /    \
                    30      70
                  /   \    /  \
                20    40  60  80 

*/

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

public: // both pointers are public for faster development
  Node* lChild; // pointer to the left child
  Node* rChild; // pointer to he right child

  Node(T item) noexcept
    :value(item)
  {}

  //Getter for value
  T getValue() const noexcept { return value; }
  // Setter for value
  void setValue(T item) noexcept { value = item; }
};

template<typename T>
class Tree
{
private:
  Node<T>* root;

  // helper method to delete the tree recursively
  void deleteTree(Node<T>* node) noexcept
  {
    if (node) {
      deleteTree(node->lChild);
      deleteTree(node->rChild);
      delete node;
    }
  }

  // helper method to find the parent of given node and the node it self
  std::tuple<Node<T>*, Node<T>*> searchParentAndChild(T item) const
  {
    // iterate over the tree
    auto tempNode = root;
    while(tempNode != nullptr)
    {
      // if the node's left child is the target child, return the node and the left child 
      if ((tempNode->lChild != nullptr && tempNode->lChild->getValue() == item))
      {
        return std::make_tuple(tempNode, tempNode->lChild);
      }
      
      // if the node's right child is the target child, return the node and the right child 
      if (tempNode->rChild != nullptr && tempNode->rChild->getValue() == item)
      {
        return std::make_tuple(tempNode, tempNode->rChild);
      }

      // if the item is <= the childs value, take the left path
      else if(tempNode->getValue() < item)
      {
        tempNode = tempNode->lChild;
        continue;
      }
      // if the item is > than the childs value, take the right path
      else
      {
        tempNode = tempNode->rChild;
      }
    }

    throw NodeNotFoundException("The request node or its parent could not be found");
  }

public:

  Tree() noexcept
    :root(nullptr)
  {}

  ~Tree() 
  {
    // calling helper method to delete tree
    deleteTree(root);
  }

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
  Node<T>* search(T item) const
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

    throw NodeNotFoundException("The request item could not be foudn");
  }

  // mehtod to remove node from BST
  void remove(T item) noexcept
  {
    try {
      // search for the node and its parent
      Node<T> *node, *parent;
      std::tie(parent, node) = searchParentAndChild(item);
      
      // If the node is a leaf node, delete the node
      if (node->lChild == nullptr && node->rChild == nullptr) // this one works
      {
        // if the node is the left child of the parent delete
        if (parent->lChild == node)
        {
          parent->lChild = nullptr;
          delete node;
          return;
        }
        // if the node is the right child of the parent delete
        else 
        {
          parent->rChild = nullptr;
          delete node;
          return;
        }
      }
      // If the node has a single left child, copy the child and delete the node
      else if (node->rChild == nullptr && node->lChild != nullptr)
      {
        // if the node is the left child of the parent, delete it and replace it
        if (parent->lChild == node)
        {
        auto deleteme = node;
        node = node->lChild;
        parent->lChild = node;
        delete deleteme;
        return;
        }
        // if the node is the right child of the parent, delete it and replace it
        else
        {
        auto deleteme = node;
        node = node->lChild;
        parent->rChild = node;
        delete deleteme;
        return;
        }
      }
      // If the node has a single right child, copy the child and delete the node
      else if (node->lChild == nullptr && node->rChild != nullptr)
      {
        // if the node is the left child of the parent, delete it and replace it
        if (parent->lChild == node)
        {
        auto deleteme = node;
        node = node->rChild;
        parent->lChild = node;
        delete deleteme;
        return;
        }
        else
        {
        // if the node is the right child of the parent, delete it and replace it
        auto deleteme = node;
        node = node->rChild;
        parent->rChild = node;
        delete deleteme;
        return;
        }
      }
      // else delete the node with both children and replace it with the inorder successor
      else
      {
        auto succParent = node;
        auto succ = node->rChild;

        // Find the inorder successor
        while(succ->lChild != nullptr)
        {
          succParent = succ;
          succ = succ->lChild;
        }

        // copy the inorder successor's item to node to be replaced
        node->setValue(succ->getValue());

        // delete the inorder successor
        if (succParent->lChild == succ)
          succParent->lChild = succ->rChild;
        else 
          succParent->rChild = succ->rChild;

        delete succ;
      }
    } catch(NodeNotFoundException exception) 
    {
      std::cout << exception.what() << std::endl;
      return;
    }
  }

  // overloaded inorder traversal method with no args
  // for easier use by the user
  void inorder() const noexcept
  {
    Node<T>* node = root;

    // if the list is empty, notify the user
    if (node == nullptr)
    {
      std::cout<< "The tree is empty, cant inorder traverse it" << std::endl;
      return;
    }
    // call the recursive traverse method and pass the root
    inorder(node);
  }

  // overloaded recursive inorder traversal method
  // left sub-tree -> root -> right sub-tree
  void inorder(Node<T>* node) const noexcept
  {
    // if the current is null, return
    if (node == nullptr)
      return;

    // continue recursively with left child
    inorder(node->lChild);
    std::cout << " " << node->getValue() << "\n";
    // continue recursively with right child
    inorder(node->rChild);
  }

  // overloaded preorder traversal method with no args
  // for easier use by the user
  void preorder() const noexcept
  {
    // if the list is empty, notify the user
    if (root == nullptr)
    {
      std::cout<< "The tree is empty, cant preorder traverse it" << std::endl;
      return;
    }

    // call the recursive traverse method and pass the root
    preorder(root);
  }

  // overloaded recursive preorder traversal method
  // root -> left sub-tree -> right sub-tree
  void preorder(Node<T>* node) const noexcept
  {
    // if a leaf is reached, return
    if (node == nullptr)
      return;

    std::cout << " " << node->getValue() << "\n";

    preorder(node->lChild); // traverse the left sub-tree
    preorder(node->rChild); // traverse the right sub-tree
  }

  // overloaded postorder traversal method with no args
  // for easier use by the user
  void postorder() const noexcept
  {

    // if the list is empty, notify the user
    if (root == nullptr)
    {
      std::cout<< "The tree is empty, cant postorder traverse it" << std::endl;
      return;
    }

    // call the recursive traverse method and pass the root
    postorder(root);
  }

  // overloaded recursive postorder traversal method
  // left sub-tree -> right sub-tree -> root
  void postorder(Node<T>* node) const noexcept
  {
    // if a leaf ist reached, return
    if (node == nullptr)
      return;

    postorder(node->lChild); // traverse the left sub-tree
    postorder(node->rChild); // traverse the left sub-tree

    std::cout << " " << node->getValue() << "\n";
  }
};

int main()
{
  Tree<int>* tree = new Tree<int>();
  tree->insert(50);
  tree->insert(30);
  tree->insert(20);
  tree->insert(40);
  tree->insert(70);
  tree->insert(60);
  tree->insert(80);

  /* The tree has the following structure
            50
          /    \
        30      70
      /   \    /  \
    20    40  60  80 */

  std::cout << "\nCreated tree with 7 nodes" << "\n" << "Displaying BST inorder" << std::endl;
  tree->inorder();
  
  std::cout << "\nDisplaying BST preorder" << std::endl;
  tree->preorder();

  std::cout << "\nDisplaying BST postorder" << std::endl;
  tree->postorder();

  std::cout << "\nSearching for node with value 80" << std::endl;
  std::cout << "Found node with value: " << tree->search(80)->getValue() << std::endl; //TODO should be in try catch
  
  std::cout << "\nDeleting node with value 70(remove case: 2 children)" << std::endl;
  tree->remove(70);
  tree->inorder();

  std::cout << "\nDeleting node with value 60(remove case: 1 child)" << std::endl;
  tree->remove(60);
  tree->inorder();
  
  std::cout << "\nDeleting node with value 20(remove case: 0 children)" << std::endl;
  tree->remove(20);
  tree->inorder();

  delete tree;
  return 0;
}
