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

  void insertNode(T data)
  {
    Node<T>* newNode = new Node(data);

    if(head == nullptr)
    {
      head = newNode;
      return;
    }

    Node<T>* tempNode = head;
    while(tempNode->next != nullptr)
    {
      tempNode = tempNode->next;
    }

    tempNode->next = newNode;
  }

  void printList()
  {
    Node<T>* tempNode = head;

    if(head == nullptr)
    {
      cout << "List empty" << endl;
      return;
    }

    while(tempNode != nullptr)
    {
      cout << tempNode->data << " ";
      tempNode = tempNode->next;
    }
  }

  void deleteNode(T nodeOffset)
  {
    Node<T> *tempNode1 = head, *tempNode2 = nullptr;
    int listLength = 0;

    if(head == nullptr)
    {
      cout << "List empty." << endl;
      return;
    }

    while(tempNode1 != nullptr)
    {
      tempNode1 = tempNode1->next;
      listLength++;
    }

    if(listLength < nodeOffset)
    {
      cout << "Index out of range" << endl;
      return;
    }

    tempNode1 = head;

    if(nodeOffset == 1)
    {
      head = head->next;
      delete tempNode1;
      return;
    }

    while(nodeOffset-- > 1)
    {
      tempNode2 = tempNode1;

      tempNode1 = tempNode1->next;

      delete tempNode1;
    }
  }

  void sort(bool(*comparator)(T, T))
  {
    //TO stuff
  }
};


bool compareInts(int a, int b)
{
  return a<b;
}

int main () {

  return 0;
}
