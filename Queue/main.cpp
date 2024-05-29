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

  int getFront() const noexcept { return front; }
  int getRear() const noexcept { return rear; }
  size_t getSize() const noexcept { return size; }
};
