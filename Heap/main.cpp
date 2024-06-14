#include <climits>
#include <iostream>

/*
This is an implementation of a MinHeap. The heap has the following methods:
    - 'insert' inserts new item into the tree and balances the heap 

    - 'deleteAtIndex' deletes item at index

    - 'decreaseAtIndex' given an index and a value smaller than the current
    value at the index, swap the old value with the new

    - 'extractMin' finds the minimum values, returns it and removes it from the heap

    - 'MinHeapify' balances the heap recursively

    - 'swap' a helper method to swap 2 values. NOTE the method uses the XOR gate to swap
    the values which theoreticly uses less memory, but according to various sources on the 
    internet it is slower when executing on x86 CPUs. It is left in to "show off" and because
    I enjoy trying out diffrent implementations across these projects
*/

class MinHeap
{
private:
  int *array; // Array holding the values
  int capacity; // The capacity of the heap
  int size; // The current size of the heap

  // helper method to swap two values using the XOR gate
  void swap(int *x, int *y) noexcept
  {
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
  }

public:

  // Constructor for creating a heap with a specified capacity and size of 0
  MinHeap(int capacity) noexcept
  {
    size = 0;
    this->capacity = capacity;
    array = new int[capacity];
  }

  // Default deconstructor
  ~MinHeap() noexcept { delete[] array; }

  // get the parent of a given idnex
  int getParent(int index) const noexcept { return (index - 1) / 2; }
  // get the left child of a  given index
  int getLeft(int index) const noexcept { return (2 * index + 1); }
  // get the right child of a given index
  int getRight(int index) const noexcept { return (2 * index + 2); }
  // get the root of the heap
  int getMin() const noexcept { return array[0]; }

  // Recursive method to heapify a tree
  void MinHeapify(int index) noexcept
  {
    int left = this->getLeft(index);
    int right = this->getRight(index);
    int smallest = index;

    if(left < size && array[left] < array[index])
      smallest = left;
    if (right < size && array[right] < array[smallest])
      smallest = right;
    if (smallest != index)
    {
      // swap the two values
      swap(&array[index], &array[smallest]);
      MinHeapify(smallest);
    }
  }  

  // Get the minimum value of the heap and remove it 
  int extractMin() noexcept
  {
    if (size <= 0) // case the heap is empty
      return INT_MAX;
    if (size == 1) // case the heap has a single entry
    {
      size--;
      return array[0];
    }

    // Return the minimum value and remove it from the heap
    int root = array[0];
    array[0] =  array[size - 1];
    size--;
    MinHeapify(0);

    return root;
  }

  // Decrease value of node at index to a specific value
  void decreaseAtIndex(int index, int value) noexcept 
  {
    // if the given value is >= the current value notify the user and return
    if (value >= array[index])
    {
      std::cout << "The given value is greater or equal to the current value. The given value must be smaller than the current value"
                << std::endl;
      return;
    }

    // Set the new value at the given index
    array[index] = value;
    // Rebalance the heap
    while(index != 0 && array[getParent(index)] > array[index])
    {
      // swap the two values
      swap(&array[index], &array[getParent(index)]);
      index = getParent(index);
    }  
  }

  // delete a node of given index
  void deleteAtIndex(int index) noexcept
  {
    decreaseAtIndex(index, INT_MIN);
    extractMin();
  }

  // insert new value to the heap
  void insert(int value) noexcept 
  {
    // if the heap is out of capacity notify the user and return
    if(size == capacity)
    {
      std::cout << "Overflow: Could not insert value" << std::endl;
      return;
    }//TODO Still needs to be implemented 


    // increase the heap size 
    size++;
    // insert key at the end 
    int index = size - 1;
    array[index] = value;

    // balance the heap if its not balanced 
    while (index != 0 && array[getParent(index)] > array[index])
    {
      // swap the the values of parent and child and continue
      swap(&array[index], &array[getParent(index)]);
      index = getParent(index);
    }
  }

};

int main()
{
  // The expected test result is: 2 4 1
  MinHeap heap(11);
  heap.insert(3);
  heap.insert(2);
  heap.deleteAtIndex(1);
  heap.insert(15);
  heap.insert(5);
  heap.insert(4);
  heap.insert(45);
  
  std::cout << heap.extractMin() << " ";
  std::cout << heap.getMin() << " ";

  heap.decreaseAtIndex(2, 1);
  std::cout << heap.getMin() << std::endl;

  return 0;
}
