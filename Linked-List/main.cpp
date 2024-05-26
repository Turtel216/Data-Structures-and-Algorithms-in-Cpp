#include <iostream>

using namespace std;

template <typename T>
class Node 
{
private:
  T payload;

public:
  Node* next;

  Node() noexcept
  {
    next = nullptr;
  }

  Node(T data) noexcept
    :payload(data) 
  {
    next = nullptr;
  }

  ~Node() noexcept { delete next; }

  void setPayload(T data) noexcept { payload = data; }
  T getPayload() noexcept { return payload; }
};


template <typename T>
class LinkedList
{
private:
  Node<T>* head;

public:

  LinkedList() noexcept{ head = nullptr; }
  LinkedList(Node<T>* head) noexcept{ this->head = head; }

  ~LinkedList() noexcept
  {
    Node<T> *next = head;
    
    while(next != nullptr)
    {
      Node<T> *deleteMe = next;
      next = next->next;  // save pointer to the next node
      delete deleteMe;    // delete current node
    }
  }

  void insertNode(T data) noexcept
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

  void printList() noexcept
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
      cout << tempNode->getPayload() <<endl;;
      tempNode = tempNode->next; // created segmantatio fault error
    }
  }

  // Deletes all notes from head to the number of nodes the offset defines
  void deleteNodes(int nodeOffset) noexcept
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
  void deleteNodeByPayload(T data) noexcept
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

  // Deletes all nodes with the specified payload value
  void deleteAllNodesByPayload(T data) noexcept
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
    int numberOfDeletedNotes = 0;
    while(currentNode != nullptr)
    {
      // if current node is a match, delete it and skip to next loop iteration
      if(currentNode->getPayload() == data)
      {
        prevNode->next = currentNode->next;

        delete currentNode;
        currentNode = prevNode->next;
    
        // count how many nodes have been deleted so far
        numberOfDeletedNotes++;
        continue;
      }

      prevNode = currentNode;
      currentNode = currentNode->next;
    }

    cout << numberOfDeletedNotes << (numberOfDeletedNotes == 1 ? " has been deleted" : " have been deleted") << endl;
  }

  void removeDuplicatesOfSorted() noexcept
  {
    // if head points to null the list is empty
    if(head == nullptr)
    {
      cout << "List empty." << endl;
      return;
    }

    // Handle deleting the head node
    if(head->getPayload() == head->next->getPayload())
    {
      Node<T>* deleteMe = head;
      head = head->next;
      delete deleteMe;
    }

    Node<T>* currentNode = head->next;
    Node<T>* prevNode = head;
    int duplicatesDeletedCounter = 0;

    // Iterate over the list
    while(currentNode != nullptr && currentNode->next != nullptr)
    {
      // If the current node has the same value as the next node, delete the current node and continue
      if(currentNode->getPayload() == currentNode->next->getPayload())
      {
        prevNode->next = currentNode->next;
        delete currentNode;
        currentNode = prevNode->next;
        
        duplicatesDeletedCounter++;
        continue;
      }

      prevNode = currentNode;
      currentNode = currentNode->next;
    }

    cout << "Number of deleted duplicates: " << duplicatesDeletedCounter << endl;

  }

  void removeDuplicates() noexcept
  {
    // if head points to null the list is empty
    if(head == nullptr)
    {
      cout << "List empty." << endl;
      return;
    }

    Node<T>* tempNode1, *tempNode2, *tempNode3;
    tempNode1 = head;

    // Iterate over list one by one
    while(tempNode1 != nullptr && tempNode1->next != nullptr)
    {
      tempNode2 = tempNode1;

      // Compare eleemnts
      while(tempNode2->next != nullptr)
      {
        // If duplicate then delete it 
        if(tempNode1->getPayload() == tempNode2->next->getPayload())
        {
          auto deleteme = tempNode2->next;
          tempNode2->next = tempNode2->next->next;
          delete deleteme;
        }
        else
          tempNode2 = tempNode2->next;
      }

      tempNode1 = tempNode1->next;
    }
  }

  void sort(bool(*comparator)(T, T)) noexcept
  {
    //TODO
  }

  //Overloaded equal operator, returns true if the lists are equal 1-1
  bool operator==(LinkedList<T>& other) const noexcept
  {
    // If one of the list's heads points to empty, return false since they are both empty
    if(this->head == nullptr)
    {
      cout << "The list on the left side of the == operator is empty";
      return false;
    }

    if(other.head == nullptr)
    {
      cout << "The list on the right side of the == operator is empty";
      return false;
    }

    int otherLength = 0;
    int thisLength = 0;

    Node<T>* thisTemp = this->head;
    Node<T>* otherTemp = other.head;

    //Count the length of the one list
    while(thisTemp != nullptr)
    {
      thisTemp = thisTemp->next;
      thisLength++;
    }

    //Count the length of the other list
    while(otherTemp != nullptr)
    {
      otherTemp = otherTemp->next;
      otherLength++;
    }

    cout << "The lenght of this: " << thisLength << " The length of the other: " << otherLength << endl;

    // If list are not of equal length, return false
    if(thisLength != otherLength)
    {
      cout << "List are not of equal length: " << thisLength << "!=" << otherLength << endl;
      return false;
    }

    //Reset both temporary node pointers to starting position
    thisTemp = this->head;
    otherTemp = other.head;

    while(thisTemp != nullptr && otherTemp != nullptr)
    {
      // if the two nodes are not of equal value, return false
      if(thisTemp->getPayload() != otherTemp->getPayload())
      {
        cout << thisTemp->getPayload() << " != " << otherTemp->getPayload() << endl;
        return false;
      }

      cout << thisTemp->getPayload() << " == " << otherTemp->getPayload() << endl;

      thisTemp = thisTemp->next;
      otherTemp = otherTemp->next;
    }

    // the two list are equal 1-1, return true
    return true;
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
  list1->insertNode(8);
  list1->insertNode(8);
  list1->insertNode(8);
  list1->insertNode(8);

  list1->printList();

  cout << "deleting all notes with an offset of 3" << endl;
  list1->deleteNodes(3);
  list1->printList();

  cout << "deleting all notes with paylod of 3" << endl;
  list1->deleteNodeByPayload(3);
  list1->printList();

  cout << "deleting all notes with a value of 8" << endl;
  list1->deleteAllNodesByPayload(8);
  list1->printList();

  delete list1;

  LinkedList<int>* list2 = new LinkedList<int>();
  list2->insertNode(1);
  list2->insertNode(2);
  list2->insertNode(3);
  list2->insertNode(4);
  list2->insertNode(5);
  list2->insertNode(6);
  list2->insertNode(8);
  list2->insertNode(8);
  list2->insertNode(8);
  list2->insertNode(8);

  cout << "Created list2: " << endl;
  list2->printList();

  cout << "deleting all duplicates of sorted list" << endl;
  list2->removeDuplicatesOfSorted();
  list2->printList();
  delete list2;

  LinkedList<int>* list3 = new LinkedList<int>();
  list3->insertNode(1);
  list3->insertNode(2);
  list3->insertNode(3);

  LinkedList<int>* list4 = new LinkedList<int>();
  list4->insertNode(1);
  list4->insertNode(2);
  list4->insertNode(3);

  if(*list3 == *list4)
    cout << "\nList3 and list4 are equal" << endl;

  cout << "Removing node number 1 from list3" << endl;
  list3->deleteNodeByPayload(1);

  if(!(*list3 == *list4))
    cout << "\nList3 and list4 are no logner equal " << endl;

  list3->insertNode(1);
  cout << "added number to list 1 at a diffrent point" << endl;

  if(!(*list3 == *list4))
    cout << "\nList3 and list4 are no logner equal 1-1" << endl;

  delete list3;
  delete list4;

  LinkedList<int>* list5 = new LinkedList<int>();
  list5->insertNode(1);
  list5->insertNode(2);
  list5->insertNode(3);
  list5->insertNode(4);
  list5->insertNode(5);
  list5->insertNode(6);
  list5->insertNode(8);
  list5->insertNode(8);
  list5->insertNode(8);
  list5->insertNode(8);

  cout << "Created list5: " << endl;
  list2->printList();

  cout << "deleting all duplicates of unsorted list" << endl;
  list5->removeDuplicates();
  list5->printList();
  delete list5;
  return 0;
}
