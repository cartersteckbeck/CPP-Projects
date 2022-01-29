/************************************************************************
    File: sequence.cc
    Author: Carter Steckbeck
    Date: 2/11/20

    Implementation of a simple array-based sequence class.

************************************************************************/
#include <iostream>
#include "sequence.h"

/*** Constructor ***/
sequence::sequence()
{
  _size = 0;
}

/*** Const member functions ***/

// Function that returns the number of elements in this sequence
size_t sequence::size() const
{
  return _size;
}

// Function that returns true if this sequence has no elements, false otherwise
bool sequence::empty() const
{
  return _size == 0;
}

// Function that returns true if this sequence has _capacity elements, false
// otherwise
bool sequence::full() const
{
  return _size == _capacity;
}

// Function that prints the array in the form of a list
void sequence::print() const
{
  std::cout << "[";

  // Iterate through each element and print it
  for (size_t i = 0; i < _size; i++){
    std::cout << get(i);
    if (i < _size - 1)
      std::cout << ", ";
  }
  std::cout << "]";
}

// Function that returns the element at a given position
int sequence::get(size_t position) const
{
  return _data[position];
}

// Function that returns smallest starting position of a run with length of the
// longest run of two or more identical adjacent elements of this sequence
size_t sequence::getLongestRun() const
{
  // Initialize current run, longest run, and starting position
  size_t curr_run = 0;
  size_t longest_run = 0;
  size_t starting_position = 0;

  // Iterate through the array
  for (size_t i = 0; i < _size; i++){

    // If the two adjacent elements are equal, increase current run
    if (_data[i] == _data[i+1]){
      curr_run++;

      // If the current run is larger than the largest run, set largest run
      // equal to current run and change starting position
      if (curr_run > longest_run){
        longest_run = curr_run;
        starting_position = i - longest_run + 1;
      }
    }

    // If two adjacent elements are not equal, set current run to 0
    else
      curr_run = 0;
  }

  // If there exists a largest run, return it, otherwise return _size
  if (longest_run > 0)
    return starting_position;
  else
    return _size;
}

/*** Non-const member functions ***/

// Function that adds an element to the array
void sequence::add(int item)
{
  // Add given item to the end of the array, increase _size
  _data[_size] = item;
  _size++;
}

// Function that adds an element at a specific position
void sequence::add(int item, size_t position)
{
  // Iterate through array and move each element to right starting at position
  for (size_t i = _size; i > position; i--){
    _data[i] = _data[i-1];
  }

  // Increase size and place item in the array at that position
  ++_size;
  _data[position] = item;
}

// Funciton that removes an element at a given position
void sequence::remove(size_t position)
{
  // Iterate through array and move each element to left starting at position
  for (int i = position; i < static_cast<int>(_size); i++){
    _data[i] = _data[i+1];
  }

  // Decrease size
  --_size;
}

// Function that replaces the item at the given position with the new item
void sequence::replace(int new_item, size_t position)
{
  _data[position] = new_item;
}

// Function that clears the array of all of its elements
void sequence::clear()
{
  _size = 0;
}
