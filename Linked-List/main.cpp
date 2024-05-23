#include <iostream>
#include <string>

template <typename T>
class Node 
{
private:
  T payload;

public:
  Node* next;
  Node* previous;

  Node(T data) noexcept
    :payload(data) {}

  void setPayload(T data) { payload = data; }
  T getPayload() { return payload; }
};

template <typename T>
class LinkedList
{
private:
  Node<T>* current;

public:
  void addToList(Node<T>* node)
  {
    if(current == nullptr)
      current = node;

    node->previous = current;
    node->next = nullptr;
  }
};


int main () {
  Node<int>* node1 = new Node(1);
  Node<int>* node2 = new Node(1);
  Node<int>* node3 = new Node(1);

  LinkedList<int>* list = new LinkedList<int>();
  list->addToList(node1);

  return 0;
}
