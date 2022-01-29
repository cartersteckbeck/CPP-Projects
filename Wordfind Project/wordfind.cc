/******************************************************************************
*
* FILE: wordfind.cc
*
* AUTHOR: Carter Steckbeck
*
* DATE: 2/7/20
*
* DESCRIPTION: Program that takes a dimension of a grid, a grid of letters, and
*              a word as inputs and outputs the grid with each letter of the
*              word uppercased in the grid if the word is found, or outputs not
*              found if the word is not found.
******************************************************************************/

#include <wordgrid.h>

// Function that checks if a row and column are within the grid
bool is_in_grid(wordgrid & grid, int new_row, int new_col)
{
  // If new row and new col are not in the grid, return false
  if ((new_row > static_cast<int>(grid.size()) - 1 || new_col >
      static_cast<int>(grid.size()) - 1) || (new_row < 0 || new_col < 0))
    return false;

  return true;
}

// Function that returns true if the full word is found in the grid given
// a direction, returns false otherwise
bool check_full_word(wordgrid & grid, size_t row, size_t col, std::string word,
                    std::string dir)
{
  // Calculate direction one and direction two from the string dir
  int dir_one = std::stoi(dir.substr(0, dir.find(',')));
  int dir_two = std::stoi(dir.substr(dir.find(',') + 1, dir.length()));

  // Initialize letter count
  int letter_count = 0;

  // Iterates through the whole word, checking in the given direction starting
  // from the second letter in the word
  for (size_t i = 1; i < word.length(); i++){

    // Calculate new row and new col
    int new_row = row + dir_one * i;
    int new_col = col + dir_two * i;

    // If the new_row and new_col are in the grid and grid at new row and
    // new col is the word indexed at i, increased letter_count
      if (is_in_grid(grid, new_row, new_col))
        if (grid.get(new_row, new_col) == word[i]){
          letter_count++;

          // If letter_count is equal to length of word - 1, return true
          if (letter_count == static_cast<int>(word.length()) - 1)
            return true;
        }
  }
  return false;
}

// Function that uppercases each letter of the word in the grid
void to_upper(wordgrid & grid, size_t row, size_t col, std::string word,
              std::string dir)
{
  // Calculate direction one and direction two from the string dir
  int dir_one = std::stoi(dir.substr(0, dir.find(',')));
  int dir_two = std::stoi(dir.substr(dir.find(',') + 1, dir.length()));

  // Iterates through the whole word
  for (size_t i = 0; i < word.length(); i++){

    // If it is the first letter in the word, uppercase word indexed at 0
    if (i == 0)

      // CITATION: http://www.cplusplus.com/reference/cctype/toupper/
      // DESCRIPTION: toupper function that takes a lowercase letter as an
      // argument and returns the uppercase version
      grid.set(row, col, toupper(word[0]));

    // Else, calculate new_row and new_col, then uppercase word indexed at i
    else{
      int new_row = row + dir_one * static_cast<int>(i);
      int new_col = col + dir_two * static_cast<int>(i);
      grid.set(new_row, new_col, toupper(word[i]));
    }
  }
}

// Function that returns true if the word is found, return false otherwise
bool find(wordgrid & grid, std::string word)
{
  // Initialize directions array and the string dir
  std::string directions [8] = {"-1,0","-1,1","0,1","1,1", "1,0", "1,-1",
                                "0,-1", "-1,-1"};
  std::string dir = "0,0";

  // Iterate through the whole grid
  for (size_t i = 0; i < grid.size(); i++)
    for (size_t j = 0; j < grid.size(); j++)

      // If grid at i,j equals the first letter in the word and word is only
      // one letter, call to_upper function and return true
      if (grid.get(i, j) == word[0]){
        if(word.length() == 1){
          to_upper(grid, i, j, word, dir);
          return true;
        }

        // If it is not one letter, iterate through each direction
        for (size_t k = 0; k < 8; k++){
          dir = directions[k];

            // If check_full_word is true given a direction, call to_upper
            // and return true
            if (check_full_word(grid, i, j, word, dir)){
              to_upper(grid, i, j, word, dir);
              return true;
            }
        }
      }
  return false;
}

int main()
{
  size_t dim = 0;  // size of the word grid
  string word = ""; // word to search for
  bool found = false;  // whether the word is found in the grid.
  string one_row = ""; // dim characters (one row) read from stdin
  string all_rows = ""; // dim x dim characters

  std::cin >> dim;  // Read the dimension

  // Read each row and append to the string of all rows
  for (size_t r = 0; r < dim ; r = r + 1) {
    std::cin >> one_row;
    all_rows += one_row;
  }

  wordgrid grid(dim, all_rows);  // create the grid from that data
  std::cin >> word; // read the word

  // Calls find, which will return true or false
  found = find(grid, word);

  // If found is true, output FOUND! and the grid, otherwise output NOT FOUND!
  if (found) {
    std::cout << "FOUND!" << std::endl;
    std::cout << grid;
  }
  else
    std::cout << "NOT FOUND!" << std::endl;

  return 0;
}
