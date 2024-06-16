#include <array>
#include <iostream>
#include <tuple>

// Search algorithms that also return false if an error accures and true it doesn't
std::tuple<int, bool> binary_search(std::array<int, 10> arr, int low, int high, int key) noexcept
{
  // Iterate over the array until the search space is exhausted
  while (low <= high)
  {
    // get the middle of the current array/sub-array
    int mid = low + (high - low) / 2; 

    if (arr[mid] == key) return {arr[mid], false}; // return the result and notify the user that node error accured

    if (arr[mid] < key) // continue with right half
      low = mid + 1;

    else // continue with left half
      high = mid - 1;
  }

  return {0, true}; // Notify the user that no item was found
}

int main()
{
  // The sorted array to test the search algo.
  std::array<int, 10> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int item = 2; // the to be searched

  std::cout << "Testing search on array: ";
  for (auto v : arr) std::cout << v << " ";

  std::cout << "\nSearching for: " << item << std::endl;

  // Test binary_search
  const auto [result, err] = binary_search(arr, 0, arr.size() - 1, item);

  if (err == true)
    std::cout << "\nNo item found" << std::endl;
  else 
    std::cout << "\nThe search found the item with the value of: " << result << std::endl;
}
