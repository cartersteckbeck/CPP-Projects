/************************************************************************
    File: sudoku.cc
    Author: Carter Steckbeck
    Date: 3/7/20
    Assignment: Lab 03 (Sudoku)

    Implementation of a link-list-based stack data structure
************************************************************************/

#include <iostream>
#include <cassert>
#include "sudokuboard.h"
#include "stack.h"

// Function that backtracks if you cannot place any number at a position
void backtrack(sudokuboard &board, stack &s)
{
  // Declare can_place boolean
  bool can_place = false;

  while(!can_place) {

    // Declare col and row by getting the top of the stack, then pop the value
    size_t col = s.top(); s.pop();
    size_t row = s.top(); s.pop();

    // Get the square value at a given row and col, then remove it
    char num = board.get(row, col);
    board.remove(row, col);

    // Iterate through the numbers starting from num
    for (int inum = (num - '0') + 1; inum <= 9; inum++)

      // If a value can be placed, place that value, push the row and col onto
      // the stack and set can_place to true
      if (board.can_place(row, col, char(inum + '0'))){
        board.place(row, col, char(inum + '0'));
        s.push(row); s.push(col);
        can_place = true;
      }
  }
}

int main()
{
  // Declaration of strings all_rows and one_row
  std::string all_rows = "";
  std::string one_row = "";

  // For each row of input, add it to all_rows
  for (size_t i = 0; i < 9; i++){
    std::cin >> one_row;
    all_rows += one_row;
  }

  // Create board and stack objects
  sudokuboard board(all_rows);
  stack s;

  // Loop that runs until the board is filled
  while(!board.solved()){
    bool can_place = false;
    size_t row = 0;
    size_t col = 0;

    // Find most constrained square on board, if you can place a value, place
    // that value, push the row and col onto the stack, set can_place to true
    board.find_constraint(row, col);
    for (char i = '1'; i <= '9'; i++)
      if(board.can_place(row, col, i)){
        board.place(row, col, i);
        s.push(row); s.push(col);
        can_place = true;
      }

    // If you cant place a value, backtrack
    if(!can_place)
      backtrack(board, s);
  }
  board.write(std::cout);
  return 0;
}
