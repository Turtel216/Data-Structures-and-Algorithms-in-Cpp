#include <exception>
#include <iostream>

/*
This is a simple implementation of a static queue
using templates. Both enqueue and dequeue have a 
time complexity of O(1) but no alteration of the 
queue size is possible. The Queue class has the
following method:
    - 'add' which adds a new item to the queue
    - 'dequeue' which removes an item from the queue
    and returns it.
    - 'display' which displays the content of the queue
    - 'isEmpty' and 'isFull' which return true if the 
    queue is empty or full respectively

Also if add or dequeue is not possible, the class throws an QueueException
*/

class QueueException : public std::exception
{
private:
  std::string message;

public:
  QueueException(const char* msg)
    : message(msg)
  {}

  const char* what() const throw()
  {
    return message.c_str();
  }
};

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
    // set front to beginning of the queue
    this->size = this->front = 0;

    // set rear to the end of the queue
    this->rear = capacity - 1;
    // allowcate memory for the queue
    this->array =  new T[this->capacity];
  }

  ~Queue() noexcept { delete array; }

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
  void add(T item)
  {
    // If the list is full, throw exception
    if (isFull())
      throw QueueException("The Queue is full, no element can be added");

    rear = (rear + 1) % capacity;
    array[rear] = item;
    size++;
  }

  T dequeue()
  {
    // If the list is empty, throw exception
    if (isEmpty())
      throw QueueException("The queue is empty, no element can be added");

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

  delete queue;

  return 0;
}
