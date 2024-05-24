#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class IncompleteListException : public runtime_error
{
  string message;
public:
  IncompleteListException(string message):runtime_error(message.c_str())
  {
    this->message = message;
  }
  const char* what() const noexcept override
  {
    return message.c_str();
  }
};

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

  LinkedList() noexcept{ head = nullptr; }
  LinkedList(Node<T>* head) noexcept{ this->head = head; }
  // Throws exception
  LinkedList(Node<T>* nodeList[])
  {
    // Iterate over the list
    for(int i =0; i < nodeList->size(); i++)
    {
      // if the head is empty, initiralise the head
      if(head == nullptr)
        i == 0 ? head = nodeList[i] : throw IncompleteListException
          ("The provided list does not contain a valid 0 index node"); // if the head is not 0 indexed throw exception

      nodeList[i -1]->next = nodeList[i];
    }
  }

  ~LinkedList()
  {
    Node<T> *next = head;
    
    while(next != nullptr)
    {
      Node<T> *deleteMe = next;
      next = next->next;  // save pointer to the next node
      delete deleteMe;    // delete current node
    }
  }

  void insertNode(T data)
  {
    Node<T>* newNode = new Node(data);

    // if head is null set new node as head
    if(head == nullptr)
    {
      head = newNode;
      return;
    }

    // Iterate over all nodes until the end is reached
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

    // Iterate over the list and print each payload
    while(tempNode != nullptr)
    {
      cout << tempNode->getPayload() << " " <<endl;;
      tempNode = tempNode->next; // created segmantatio fault error
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

    // if the offset is greater then the length, print out of range 
    if(listLength < nodeOffset)
    {
      cout << "Offset out of range" << endl;
      return;
    }

    tempNode1 = head;

    // If the offset is 1 delete the head and assign the next node as the new head
    if(nodeOffset == 1)
    {
      head = head->next;
      delete tempNode1;
      return;
    }

    // delete as many nodes as the offset deffines.
    while(nodeOffset-- > 1)
    {
      tempNode2 = head;
      head = head->next;
      delete tempNode2;
    }
  }

  // Deletes node by payload value
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
      return;
    }

    Node<T>* prevNode = head;
    Node<T>* currentNode = head->next;
    while(currentNode != nullptr)
    {
      // if current node is a match, delete it
      if(currentNode->getPayload() == data)
      {
        prevNode->next = currentNode->next;

        cout << "Deleted node with paylod: " << currentNode->getPayload() << endl;
        delete currentNode;
        return;
      }

      prevNode = currentNode;
      currentNode = currentNode->next;
    }

    cout << "Node with specified payload could not be found" << endl;
  }

  // TODO overloaded = operator

  void removeDuplicates(T data)
  {
    // TODO
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
  LinkedList<int>* list1 = new LinkedList<int>();
  list1->insertNode(1);
  list1->insertNode(2);
  list1->insertNode(3);
  list1->insertNode(4);
  list1->insertNode(5);
  list1->insertNode(6);

  list1->printList();

  cout << "deleting all notes with an offset of 3" << endl;
  list1->deleteNodes(3);
  list1->printList();

  cout << "deleting all notes with paylod of 3" << endl;
  list1->deleteNodeByPayload(3);
  list1->printList();

  return 0;
}
