#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
/*
This source file is used to generate random test data and save it 
to the input.txt file
*/

// Converts integer into ASCII char
char intToAlphabet(int i)
{
  return static_cast<char>('A' - 1 + i);
}


// Generates a 1000000 character string
std::string gen_test_string()
{
  srand(42);

  // String to be returned
  std::string temp = "";

  // Generate 1000000 char strings and save them to the temp variable
  for(int i = 0; i < 100000; i++)
  {
    temp = temp + intToAlphabet(1 + (rand() % (26 - 1 + 1)));
  }

  // return the result
  return temp;
}

int main () {
  // Open the input.txt file
  std::ofstream inputFile("input.txt");

  // Generate the input string and save it to input.txt
  inputFile << gen_test_string();

  // Close the file stream
  inputFile.close();

  std::cout << "Generated test data and saved it in input.txt" << std::endl;
  return 0;
}
