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

    //Getter for value
    T getValue() const noexcept { return value; }
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

  // helper method to find the parent of given node
  Node<T>* searchParent(T item) const
  {
    // iterate over the tree
    auto tempNode = root;
    while(tempNode != nullptr)
    {
      // if one of the node's children is the target children, return the node 
      if ((tempNode->lChild != nullptr && tempNode->lChild->getValue() == item) ||
          (tempNode->rChild != nullptr && tempNode->rChild->getValue() == item)) 
      {
        return tempNode; // Found parent node
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

    std::cout << "The parent of the item with the value of: " << item << " could not be found" << std::endl;
    throw NodeNotFoundException("The request item could not be foudn");
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

  // DOES NOT WORK!!!
  void remove(T item) noexcept
  {
    try {
      // search for the node 
      auto node = search(item); // throws exception if node is not found!!!
      
      auto parent = searchParent(node->getValue()); // throws exception if node is not found!!!
      
      std::cout << "\nThe node that will be delted has the value of: " << node->getValue()
        << "\n It has a lChild == nullptr is: " << (node->lChild == nullptr)
        << "\n It has a rChild == nullptr is: " << (node->rChild == nullptr)
        << "\n and the parent has a value of: " << parent->getValue()
        << "\n\n The value of the parent's left child is: " << parent->lChild->getValue()
        << std::endl;

      // If the node is a leaf node, delete the node
      if (node->lChild == nullptr && node->rChild == nullptr)
      {
        if (parent->lChild == node)
        {
          parent->lChild = nullptr;
          delete node;
          return;
        }
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
        auto deleteme = node;
        node = node->lChild;
        delete deleteme;
        return;
      }
      // If the node has a single right child, copy the child and delete the node
      else if (node->lChild == nullptr && node->rChild != nullptr)
      {
        auto deleteme = node;
        node = node->rChild;
        delete deleteme;
        return;
      }
      // else delete the node with both children and replace it with the inorder successor
      else 
      {
        Node<T>* succParent = parent;        Node<T>* succ = node->rChild;
        while(succ->lChild != nullptr)
        {
          succParent = succ;
          succ = succ->lChild;
        }

        node->setValue(succ->getValue());

        if (succParent->lChild == succ)
          succParent->lChild = succ->rChild;
        else 
          succParent->rChild = succ->rChild;

        std::cout << "Value of the deleted node is: " << node->getValue()
          << "\n The value of the succ is: " << succ->getValue()
          << "\n The Value of the succParent is: " << succParent->getValue()
          << std::endl;

        delete node;
      }
    } catch(NodeNotFoundException exception) 
    {
      exception.what();
      return;
    }
  }

  // overloaded inorder traversal method with no args
  // for easier use by the user
  void inorder()
  {
    Node<T>* node = root;

    if (node == nullptr)
    {
      std::cout<< "The tree is empty, cant inorder traverse it" << std::endl;
      return;
    }
    // call the recursive traverse method and pass the root
    inorder(node);
  }

  // overloaded recursive inorder traversal method
  void inorder(Node<T>* node)
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

  void preorder()
  {
    Node<T>* node = root;

    if (node == nullptr)
    {
      std::cout<< "The tree is empty, cant preorder traverse it" << std::endl;
      return;
    }

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
    {
      std::cout<< "The tree is empty, cant postorder traverse it" << std::endl;
      return;
    }

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
  tree->insert(50);
  tree->insert(30);
  tree->insert(20);
  tree->insert(40);
  tree->insert(70);
  tree->insert(60);
  tree->insert(80);

  std::cout << "Created tree with 7 nodes" << "\n" << "Displaying BST inorder" << std::endl;
  tree->inorder();
  
  std::cout << "Displaying BST preorder" << std::endl;
  tree->preorder();

  std::cout << "Displaying BST postorder" << std::endl;
  tree->postorder();

  std::cout << "Searching for node with value 80" << std::endl;
  std::cout << "Found node with value: " << tree->search(80)->getValue() << std::endl; //TODO should be in try catch
  
  std::cout << "Deleting node with value 20" << std::endl;
  tree->remove(20);
  tree->inorder();
  
  return 0;
}
