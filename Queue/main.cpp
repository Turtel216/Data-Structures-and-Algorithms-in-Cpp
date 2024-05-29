#include <iostream>

template <typename T>
class Queue 
{
private:
  T *array;
  int front, rear;
  size_t size;
  size_t capacity;

public:

  Queue(size_t capacity)
  {
    this->capacity = capacity;
    this->size = this->front = 0;

    this->rear = capacity - 1;
    this->array =  new T[this->capacity];
  }

  // Getters
  int getFront() const noexcept { return front; }
  int getRear() const noexcept { return rear; }
  size_t getSize() const noexcept { return size; }

  // Method that returns true if the queue is full
  bool isFull() const noexcept { return this->size == this->capacity; }

  // Method that returns true if the queue is empty
  bool isEmpty() const noexcept { return this->size == 0; }

  void add(T value) noexcept
  {
    // Check if the queue is full
    if (isFull())
    {
      std::cout << "The Queue is full, no element can be added" << std::endl;
      return;
    }

    rear = (rear + 1) % capacity;
    size++;
  }
};
