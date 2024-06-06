#include <cstddef>
#include <iostream>

template<typename T>
class MinHeap
{
private:
  T *array;
  size_t capacity;
  size_t size;

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

  void MinHeapify(size_t index);

  T extractMin() noexcept;

  void decreaseKey(size_t index, T value) noexcept;

  // delete a node of given index
  void deleteKey(size_t index);

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
