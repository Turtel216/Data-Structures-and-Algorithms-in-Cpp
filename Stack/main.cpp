#include <iostream>

using namespace std;

// Implemented using dynamic array
template <typename T>
class Stack
{
private:

  T* array;
  size_t size;
  int capacity;

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
  size_t getSize() { return size; }
  int getCapacity() { return capacity; }

  // Method to grow the Array
  void growArray()
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

  // Method to shrink the Array
  void shrinkArray()
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

  void printContent()
  {
    for(auto i = 0; i < size; i++)
      cout << array[i] << endl;
  }

  bool isEmpty()
  {
    return size == 0;
  }
};

int main () {
  
  return 0;
}
