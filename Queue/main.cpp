#include <iostream>

template <typename T>
class Queue 
{
private:
  T *array;
  size_t front, rear;
  size_t size;
  size_t capacity;

public:

  Queue(size_t capacity) noexcept
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

  // display the content of the queue
  void display() const noexcept
  {
    if(isEmpty())
      std::cout << "List is empty" << std::endl;

    // Iterate over the list and print each element
    for(int i = front; i <= rear; i++)
      std::cout << array[i] << std::endl;

  }

  // adds a new item to the queue
  void add(T item) noexcept
  {
    // Check if the queue is full
    if (isFull())
    {
      std::cout << "The Queue is full, no element can be added" << std::endl;
      return;
    }

    rear = (rear + 1) % capacity;
    array[rear] = item;
    size++;
  }

  T dequeue()
  {
    if (isEmpty())
    {
      std::cout << "The Queue is empty, no element can be added" << std::endl;
      return 0; //TODO throw exception
    }

    // get front item
    auto item = array[front];
    // set new front
    front = (front + 1) % capacity;
    size--;
    return item;

  }
};


int main()
{
  Queue<int>* queue = new Queue<int>(5);

  queue->add(1);
  queue->add(5);
  queue->add(2);
  queue->add(4);

  std::cout << "Added 4 items to queue" << std::endl;
  queue->display();

  std::cout << "Item in the front of the queue is: " << queue->dequeue() << std::endl;

  std::cout << "The now updated queue is :" << std::endl;
  queue->display();

  return 0;
}
