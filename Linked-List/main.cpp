#include <iostream>

using namespace std;

template <typename T>
class Node 
{
private:
  T payload;

public:
  Node* next;

  Node(T data) noexcept
    :payload(data) 
  {
    next = nullptr;
  }

  void setPayload(T data) { payload = data; }
  T getPayload() { return payload; }
};


template <typename T>
class LinkedList
{
private:
  Node<T>* head;

public:

  LinkedList() { head = nullptr; }

  ~LinkedList()
  {
    Node<T> *next = head;
    
    while(next != nullptr)
    {
      Node<T> *deleteMe = next;
      next = next->next;  //save pointer to the next node
      delete deleteMe;    // delete current node
    }
  }

  void insertNode(T data)
  {
    Node<T>* newNode = new Node(data);

    // if head is null se new node as head
    if(head == nullptr)
    {
      head = newNode;
      return;
    }

    // iterate over all nodes until the and is reached
    Node<T>* tempNode = head;
    while(tempNode->next != nullptr)
    {
      tempNode = tempNode->next;
    }

    // place newNode at the end of the list
    tempNode->next = newNode;
  }

  void printList()
  {
    Node<T>* tempNode = head;

    // if the head points to null the list is empty
    if(head == nullptr)
    {
      cout << "List empty" << endl;
      return;
    }

    // iterate over the list and print each payload
    while(tempNode != nullptr)
    {
      cout << tempNode->getPayload() << " ";
      tempNode = tempNode->next;
    }
  }

  // Deletes all notes from head to the number of nodes the offset defines
  void deleteNodes(int nodeOffset)
  {
    Node<T> *tempNode1 = head, *tempNode2 = nullptr;
    int listLength = 0;   // Length of the linked list

    // if the head points to null the list is empty
    if(head == nullptr)
    {
      cout << "List empty." << endl;
      return;
    }

    // Iterate over the list and count its length
    while(tempNode1 != nullptr)
    {
      tempNode1 = tempNode1->next;
      listLength++;
    }

    // if the offset is greater then the length print out of range 
    if(listLength > nodeOffset)
    {
      cout << "Index out of range" << endl;
      return;
    }

    tempNode1 = head;

    // if the offset is 1 delete the head and assign the next node as the new head
    if(nodeOffset == 1)
    {
      head = head->next;
      delete tempNode1;
      return;
    }

    // delete as many nodes as the offset deffines.
    while(nodeOffset-- > 1)
    {
      tempNode2 = tempNode1;

      tempNode1 = tempNode1->next;

      delete tempNode1;
    }
  }

  void deleteNodeByPayload(T data)
  {
    // if head points to null the list is empty
    if(head == nullptr)
    {
      cout << "List empty." << endl;
      return;
    }

    // Handle deleting the head node
    if(head->getPayload() == data)
    {
      Node<T>* deleteMe = head;
      head = head->next;
      delete deleteMe;
    }

    Node<T>* prevNode = head;
    Node<T>* currentNode = head->next;
    while(currentNode != nullptr)
    {
      // if current node is a match, delete it
      if(currentNode->getPayload() == data)
      {
        prevNode->next = currentNode->next;
        currentNode = prevNode->next;
        delete currentNode;
        return;
      }

      prevNode = currentNode;
      currentNode = currentNode->next;
    }

    cout << "Node with specified payload could not be found" << endl;
  }

  void sort(bool(*comparator)(T, T))
  {
    //TODO
  }
};


// Temporery test function
bool compareInts(int a, int b)
{
  return a<b;
}

int main () {

  delete node1;
  delete node2;
  delete node3;
  
  delete list;

  return 0;
}
