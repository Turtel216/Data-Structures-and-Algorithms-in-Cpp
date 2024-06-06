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

  size_t getParent(size_t index) const noexcept { return (index - 1) / 2; }
  size_t getLeft(size_t index) const noexcept { return (2 * index + 1); }
  size_t getRight(size_t index) const noexcept { return (2 * index + 2); }
  T extractMin() noexcept;
  void decreaseKey(size_t index, T value) noexcept;
  T getMin() const noexcept { return array[0]; }
  void deleteKey(size_t index);
  void insert(T value) noexcept;
};

int main()
{
  return 0;
}
