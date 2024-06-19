#include <cctype>
#include <chrono>
#include <cstring>
#include <fstream>
#include <string>
#include <iostream>


// Get the string which to be compressed
std::string getInput();

// Calculate the % compression of the input
double evaluateOutput(std::string &input, std::string &output) noexcept;

// The RLE compression algorithm
std::string rle_compression(std::string input);

// The RLE decompression algorithm
std::string rle_decompression(std::string input) noexcept;

// Checks if the compression was lossless
inline bool assert_lossless(std::string &input, std::string &output) noexcept;

// Display the perfomance of the compression algorithm 
void display_compression_performance(std::string &input, std::string &output, std::chrono::microseconds calc_time) noexcept;

// display the perfomance of the decompression algorithm 
void display_decompression_performance(std::string &input, std::string &output, std::chrono::microseconds) noexcept;

int main () 
{
  // Testing the Algorithm

  auto input = getInput();
  std::string mock_input = "aaafghjkmmldzsawwwwsqqqtiddhgiwqpppphdkeqwuuuuq";

  std::cout << "Testing compression on a mock_input with intentional duplicates\n"
    <<"Note the calculation time is set to 1, it is doesn't represant the actual time\n\n";

  auto start = std::chrono::high_resolution_clock::now();
  std::string mock_output = rle_compression(mock_input);
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

  std::cout << "The input string is: " << mock_input << "\n\nThe compressed string is: " << mock_output << "\n";

  display_compression_performance(mock_input, mock_output, duration);

  std::cout << "\n\n\nTesting decompression on a mock_input\n"
    <<"Note the calculation time is set to 1, it is doesn't represant the actual time\n\n";

  std::string mock_decompression = rle_decompression(mock_output);

  std::cout << "The decompressed string is: " << mock_decompression << "\n";

  display_decompression_performance(mock_input, mock_decompression, duration);

  std::cout << "\n\n\nTesting compression on the randomly generated data\n";

  start = std::chrono::high_resolution_clock::now();
  std::string output = rle_compression(input);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

  display_compression_performance(input, output, duration);

  std::cout << "\n\n\nTesting decompression on randomly generated data\n\n";

  start = std::chrono::high_resolution_clock::now();
  std::string decompressed = rle_decompression(output);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

  display_decompression_performance(input, decompressed, duration);
  return 0;
}

// The RLE compression algorithm
std::string rle_compression(std::string str)
{ 

  std::string::iterator it = str.begin() + 1;; // iterator needed to traverse string
  int duplicates = 0; // keeping track of duplicate count
  std::string::iterator first_duplicate; // keeps the track of the first of an array of duplicates
  char prev_char =  *str.begin(); // set prev to the begin of the string
  int current_length = 0; // keeps track of the characters that have been traversed

  // Traverse the string 
  while (it <= str.end())
  {
    current_length++;
    if (*it == prev_char) // If a new duplicate is found, push it onto the stack
    {
      // if the current char is the first duplicate, save it
      if (duplicates == 0) first_duplicate = it - 1;
      // add duplicate
      duplicates++;
      // set prev_char to current char
      prev_char = *it;
      // set iterator to next char
      it++;
      continue;
    }
    // case: the previous character is != the currect and the vector is not empty
    // replace and remove duplicates
    else if (*it != prev_char && duplicates != 0)
    {
      // add previous duplicate
      duplicates++;
      // Replace the first duplicate with the number of duplicates
      str.replace(first_duplicate, first_duplicate, std::to_string(duplicates));

      // Revaluate new iterator
      current_length -= duplicates - 1;
      it = str.begin() + current_length;

      // Erase the rest of the duplicates
      str.erase(it, it + duplicates - 1);

      // Reset iterator, accounting for str manipulation
      current_length++;
      it = str.begin() + current_length;

      // Set prev_char
      prev_char = *(it - 1);

      // Reset duplicates counter
      duplicates = 0;
      continue;
    }

    // set the previous char equal to the current char
    prev_char = *it;
    // Set iterator to next char
    it++;
  }

  // Return the now compressed string
  return str;
}

// The RLE decompression algorithm
std::string rle_decompression(std::string str) noexcept 
{
  std::string::iterator it = str.begin();
  int current_length = 0; // keeping track of current position on string
  
  // iterate over input string 
  while (it <= str.end())
  {
    // if the current char is a digit,
    // replace the digit with digit*number of the next char
    if (isdigit(*it))
    {
      // convert char to int
      int digit = *it - '0';
      // set current char to the next character
      *it = *(it + 1);
      // reinitialise the iterator
      it = str.begin() + current_length;
      // append the extra chars
      str.insert(it + 1, digit - 2, *it);
      // adjust the lenght
      current_length += digit -1;
      // reinitialise iterator
      it = str.begin() + current_length;
      continue;
    }
    current_length++;
    // set iterator to next char
    it++;
  }
  
  // return the now decompress string
  return str;
}

// Get the string which will be compressed
std::string getInput()
{
  // Open the input.txt file
  std::ifstream inputFile("input.txt");
  std::string inputString; // Variable to store the input value

  // Iterate over the file and save each character
  while(std::getline (inputFile, inputString)) continue;

  // Close file stream
  inputFile.close();

  return inputString;
}

// Calculate the % compression of the input
double evaluateOutput(std::string &input, std::string &output) noexcept
{
  // Get the length of both strings
  double size_input = static_cast<double>(input.length());
  double size_output = static_cast<double>(output.length());

  // Return the in % of the compression
  return ((size_input - size_output) / size_input) * 100;
}

// Checks if the compression was lossless
inline bool assert_lossless(std::string &input, std::string &output) noexcept { return input == output; }

// Display the perfomance of the compression algorithm 
void display_compression_performance(std::string &input, std::string &output, std::chrono::microseconds calc_time) noexcept
{
  std::cout << "\nDisplaying the RLEs compression perfomance: " << "\n";

  std::cout << "\nThe lenght of the input string is: " << input.length()
    << "\nThe length of the output string is: " << output.length() << "\n";

  std::cout << "\nThe compression achieved by the algorithm is: " << evaluateOutput(input, output) << "%" << "\n";

  std::cout << "\nIt took the algorithm " << calc_time.count() << "microseconds to compress the string" << std::endl;
}

// Display the perfomance of the decompression algorithm 
void display_decompression_performance(std::string &input, std::string &output, std::chrono::microseconds calc_time) noexcept
{
  std::cout << "Displaying the RLEs decompression perfomance: " << "\n";

  std::cout << "\nThe lenght of the input string is: " << input.length()
    << "\nThe length of the output string is: " << output.length() << "\n";

  std::cout << (assert_lossless(input, output) ? "\nThe compression was lossless"
    : "\nThe compression was not lossless") << "\n";

  std::cout << "It took the algorithm " << calc_time.count()  << "microseconds to decompression the string" << std::endl;
}



