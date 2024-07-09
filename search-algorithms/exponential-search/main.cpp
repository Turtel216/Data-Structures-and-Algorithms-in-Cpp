#include <algorithm>
#include <array>
#include <iostream>
#include <tuple>

// Search algorithm to find range for binary_search
std::tuple<int, bool> exponetial_search(std::array<int, 10>, int size,
                                        int key) noexcept;

// Search algorithms that return false if an error accures and true it doesn't
std::tuple<int, bool> binary_search(std::array<int, 10> arr, int low, int high,
                                    int key) noexcept;

int main() {
  // The sorted array to test the search algo.
  std::array<int, 10> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int item = 2; // the item to be search

  std::cout << "Testing search on array: ";
  for (auto v : arr)
    std::cout << v << " ";

  std::cout << "\nSearching for value: " << item << "\n";

  const auto [result, err] = exponetial_search(arr, arr.size(), item);

  if (err == true)
    std::cout << "\nNo item found" << std::endl;
  else
    std::cout << "\nThe search found the item with the value of: " << result
              << std::endl;
}

// Search algorithm to find range for binary_search. Also returns the result of
// binary_search
std::tuple<int, bool> exponetial_search(std::array<int, 10> arr, int size,
                                        int key) noexcept {
  // Check if the key is on starting index
  if (arr[0] == key)
    return {arr[0], false};

  // find range for binary_search
  int i = 1;
  while (i < size && arr[i] <= key)
    i = i * 2;

  // Search for the item in found range
  return binary_search(arr, i / 2, std::min(i, size - 1), key);
}

// Search algorithm that returns false if an error accures and true it doesn't
std::tuple<int, bool> binary_search(std::array<int, 10> arr, int low, int high,
                                    int key) noexcept {
  // Iterate over the array until the search space is exhausted
  while (low <= high) {
    // get the middle of the current array/sub-array
    int mid = low + (high - low) / 2;

    if (arr[mid] == key)
      return {arr[mid], false}; // return the result and notify the user that
                                // node error accured

    if (arr[mid] < key) // continue with right half
      low = mid + 1;

    else // continue with left half
      high = mid - 1;
  }

  return {0, true}; // Notify the user that no item was found
}
