/************************************************************************
    File: sudokuboard.cc
    Author: Carter Steckbeck
    Date: 3/7/20

    Implementation of a sudoku board
************************************************************************/

#include "sudokuboard.h"
#include <cassert>
#include <iostream>
#include <cmath>
#include "stack.h"

#define DIM 9

// Constructor
sudokuboard::sudokuboard(std::string all_rows)
{
  set_board(all_rows);
}

// Function that returns true if you can place a given chararacter at a given
// row and col, returns false otherwise
bool sudokuboard::can_place(size_t r,size_t c,char n) const
{
  // Iterates through the given column and row, if the same number appears,
  // return false
  for (size_t i = 0; i < DIM; i++)
    if (rows[r][i] == n || rows[i][c] == n)
      return false;

  // Declare sub_row and sub_col to determine which 3x3 square it is in
  size_t sub_row = r/3 * 3;
  size_t sub_col = c/3 * 3;

  // Iterate through 3x3 square, if the same number appears, return false
  for (size_t row = 0; row < 3; row++){
    for (size_t col = 0; col < 3; col++){
      if (rows[sub_row + row][sub_col + col] == n)
        return false;
    }
  }

  // If the given space is an underscore, return false
  if (rows[r][c] != '_')
      return false;

  return true;
}

// Function that returns true if the board is completed, returns false otherwise
bool sudokuboard::solved() const
{
  // This method provided by Professor Campbell
  for (int i=0;i<DIM;i++)
    if (rows[i].find('_')<(size_t)DIM)
      return false;
  return true;
}

// Function that outputs the board
void sudokuboard::write(std::ostream & ostr) const
{
  // This method provided by Professor Campbell
  for (int i=0;i<DIM;i++)
    ostr << rows[i] << std::endl;
}

// Function that places a value at a given row and col
void sudokuboard::place(size_t r,size_t c,char n)
{
  if (can_place(r, c, n))
    rows[r][c] = n;
}

// Function that returns the value at a given row and col
char sudokuboard::get(size_t r, size_t c) const
{
  return rows[r][c];
}

// Function that removes the value at a given row and col
void sudokuboard::remove(size_t r,size_t c)
{
  rows[r][c] = '_';
}

// Function that finds the most constrained square on the board
void sudokuboard::find_constraint(size_t & r, size_t & c)
{
  size_t max = 0; // Declaration of max

  // Iterate through the whole grid
  for (size_t i=0;i<DIM;i++)
    for (size_t j=0;j<DIM;j++)

      // If rows at i and j is a number, call calculate
      if (rows[i][j] == '_'){
        size_t counter = 0;
        calculate(i, j, counter);

        // If it is the most constrained square, set max to counter and change
        // the row and col
        if (counter > max){
          max = counter;
          r = i;
          c = j;
        }
      }
}

// Function that checks how many numbers show up in a row and col
void sudokuboard::calculate(size_t r, size_t c, size_t & counter)
{
  // If a number appears in the col or row, increase counter
  for (size_t i=0;i<DIM;i++) {
    if (rows[i][c] != '_' || rows[r][i] != '_')
      counter++;
  }
}

// Helper function for constructor that given input sets the board
void sudokuboard::set_board(std::string all_rows)
{
  // Iterate through the grid and create rows from all_rows
  for (size_t i=0;i<DIM;i++) {
    for (size_t j=0;j<DIM;j++)
      rows[i] += all_rows[j];
    all_rows = all_rows.substr(DIM);
  }
}
