#include <fstream>
#include <iostream>
#include <string>

#define _nl "\n"

// Z algorithm
void getZ(std::string str, int Z[]);

// prints all occurences of pattern
void search(std::string text, std::string pattern);

int main() {
  // The pattern which will be searched
  std::string pattern = "Ring";

  // The text which will be searched
  std::string input = "The Ring of power";

  std::cout << "Searching for pattern: '" << pattern << "' in '" << input << "'"
            << _nl;

  std::cout << "The results are: " << _nl;

  search(input, pattern);

  return 0;
}

// Z algorithm
void getZ(std::string str, int Z[]) {
  int n = str.length();
  int L, R, k;
  L = R = 0;

  for (int i = 1; i < n; ++i) {
    if (i > R) {
      L = R = i;

      while (R < n && str[R - L] == str[R])
        ++R;

      Z[i] = R - L;
      --R;
    } else {
      k = i - L;

      if (Z[k] < R - i + 1)
        Z[i] = Z[k];

      else {
        L = i;
        while (R < n && str[R - L] == str[R])
          ++R;

        Z[i] = R - L;
        --R;
      }
    }
  }
}

// prints all occurences of pattern
void search(std::string text, std::string pattern) {
  std::string concat = pattern + "$" + text;
  int _length = concat.length();

  int Z[_length];
  getZ(concat, Z);

  for (int i = 0; i < _length; ++i) {
    // if Z[i] is equal to pattern length, print the pattern
    if (Z[i] == pattern.length())
      std::cout << "Pattern found at index " << i - pattern.length() - 1 << _nl;
  }
}
