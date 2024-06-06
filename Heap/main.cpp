#include <climits>
#include <cstddef>
#include <iostream>
#include <linux/limits.h>

template<typename T>
class MinHeap
{
private:
  T *array;
  size_t capacity;
  size_t size;

  // helper method to swap to values
  void swap(T *x, T *y)
  {
    T temp = *x;
    *x = *y;
    *y = temp;
  }

public:

  MinHeap(T capacity) noexcept
  {
    size = 0;
    this->capacity = capacity;
    array = new T[capacity];
  }

  // get the parent of a given idnex
  size_t getParent(size_t index) const noexcept { return (index - 1) / 2; }
  // get the left child of a  given index
  size_t getLeft(size_t index) const noexcept { return (2 * index + 1); }
  // get the right child of a given index
  size_t getRight(size_t index) const noexcept { return (2 * index + 2); }
  // get the root of the heap
  T getMin() const noexcept { return array[0]; }

  // Recursive method to heapify a tree
  void MinHeapify(size_t index) noexcept
  {
    auto left = this->getLeft(index);
    auto right = this->getRight(index);
    auto smallest = index;

    if(left < size && array[left] < array[smallest])
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

  T extractMin() noexcept
  {
    if (size <= 0) // case the heap is empty
      return INT_MAX;
    if (size == 1) // case the heap has a single entry
    {
      size--;
      return array[0];
    }

    // Return the minimum value and remove it from the heap
    T root = array[0];
    array[0] =  array[size - 1];
    MinHeapify(0);

    return root;
  }

  // Decrease value of node at index to a specific value
  void decreaseKey(size_t index, T newValue) noexcept 
  {
    // if the given value is <= the current value notify the user and return
    if (newValue >= array[index])
    {
      std::cout << "The given value is greater or equal to teh current value. The given value must be smaller than the current value"
                << std::endl;
      return;
    }
    array[index] = newValue;
    while(index != 0 && array[this->getParent(index)] > array[index])
    {
      // swap the two values
      array[index] = array[getParent(index)];
      array[getParent(index)] = newValue;
      index = getParent(index);
    }  
  }

  // delete a node of given index
  void deleteAtIndex(size_t index)
  {
    decreaseKey(index, INT_MIN);
    extractMin();
  }

  // insert new value to the heap
  void insert(T value) noexcept 
  {
    // if the heap is out of capacity notify the user and return
    if(size == capacity)
    {
      std::cout << "Overflow: Could not insert value" << std::endl;
      return;
    }

    // increase the heap size 
    size++;
    // insert key at the end 
    size_t index = size - 1;
    array[index] = value;

    // balance the heap if its not balanced 
    while (index != 0 && array[getParent(index)] > array[index])
    {
      // swap the the values of parent and child and continue
      array[index] = array[getParent(index)];
      array[getParent(index)] = value;
      index = getParent(index);
    }
  }

};

int main()
{
  return 0;
}
