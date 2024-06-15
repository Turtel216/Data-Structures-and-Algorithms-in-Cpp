#include <array>
#include <iostream>

/*
A simple implementation of the selection sort algorithm
*/

// Method for sorting the integer array
void selectionSort(std::array<int, 5> &arr) noexcept;

// Helper method to display the array
void display_array(std::array<int, 5> &arr) noexcept;

int main()
{
  std::array<int, 5> arr_test = {2, 7, 1, 3, 4};

  std::cout << "The unsorted array is : ";
  display_array(arr_test);

  std::cout << "\nThe sorted array is : ";
  selectionSort(arr_test);
  display_array(arr_test);

  std::cout << "" << std::endl;

  return 0;
}

// Method for sorting the integer array
void selectionSort(std::array<int, 5> &arr) noexcept
{
  int tmp; // variable to help swap 2 values
  // loop over the array
  for (int i = 0; i < arr.size(); i++)
  {
    // at each index check if the following indexes
    // are smaller than the current ones
    for (int j = i + 1; j < arr.size(); j++)
    {
      // if one of the following indexes is
      // smaller than the current one, swap the two values
      if (arr[j] < arr[i]) 
      {
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
      }
    }
  }
}

// Helper method to display the array
void display_array(std::array<int, 5> &arr) noexcept
{
  for (int i = 0; i < arr.size(); i++) std::cout << arr[i] << " ";
}
