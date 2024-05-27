#include <iostream>

/*
This an implementation of a the Stack data strcucture
using a dynamic array and tempaltes. It has the following methods
  
  - 'push': which adds an element to the stack
  - 'pop': which removes an element from the stack
  - 'printContent': which displays the content of the stack
  - `growArray`: which increases the size of dynamic array
  - `shrinkArray`: which decreases the size of dynamic growArray

Also the '==' operator has been overloead and return true if both 
stacks have the same size
*/



using namespace std;

// Implemented using dynamic array
template <typename T>
class Stack
{
private:

  T* array;
  size_t size;
  int capacity;

  // Increases the size of array
  void growArray() noexcept
  {
    capacity = capacity * 2;

    // Create a new array of double size
    T* temp = new T[capacity];

    // Copy elements of old array to new array
    for(auto i = 0; i < size; i++)
      temp[i] = array[i];

    // delete old array
    delete[] array;

    // Assign new array to class array
    array = temp;
  }

  // Decreases the size of array
  void shrinkArray() noexcept
  {
    //creating new array by half size
    capacity = size;
    T* temp = new T[capacity];

    // Copy elements of old array to new array
    for(auto i = 0; i < size; i++)
      temp[i] = array[i];

    // delete old array
    delete[] array;

    // Assign new array to class array
    array = temp;
  }

public:
  
  // Default constructor which creates a stack with size 1
  Stack() noexcept
  {
    capacity = 1;
    size = 0;
    array = new T[capacity];
  }

  // Constructor with size given by the user
  Stack(int capacity) noexcept
  {
    this->capacity = capacity;
    array = new T[capacity];
    size = 0;
  }

  // Getters
  size_t getSize() const noexcept { return size; }
  int getCapacity() const noexcept { return capacity; }

  // adds a new element to the stack
  void push(T value) noexcept
  {
    // check if the array can store the new element
    if(size == capacity)
      growArray(); // if not, grow the array

    // insert element
    array[size] = value;

    // increment the size
    size++;
  }

  // removes an element from the stack
  void pop() noexcept
  {
    // Replace the last index 0
    array[size - 1] = 0;

    // Decrement the array size
    size--;

    // Reduce if the size is half of its capacity
    if(size == (capacity / 2))
      shrinkArray();
  }

  // displays the content of the stack
  void printContent() noexcept
  {
    for(auto i = 0; i < size; i++)
      cout << array[i] << endl;
  }

  bool isEmpty()
  {
    return size == 0;
  }

  // Retruns true if both stacks have the same size
  bool operator==(Stack<T> &other) const noexcept
  {
    return this->size == other.size;
  }
};

int main () {

  Stack<int> stack;

  stack.push(2);
  stack.push(4);
  stack.push(1);

  cout << "Pushed 3 elements into the stack" << endl;
  stack.printContent();

  stack.pop();
  stack.pop();
  
  cout << "Poped 2 elements from the stack" << endl;
  stack.printContent();

  stack.push(111);

  cout << "Pushed one more element into the stack" << endl;
  stack.printContent();

  Stack<int> stack2;
  
  stack2.push(2);
  stack2.push(3);

  cout << "Created new Stack, which contains 2 elements" << endl;
  stack2.printContent();

  if(stack == stack2)
    cout << "Both stacks have the same size" << endl;

  return 0;
}
