/************************************************************************
    File: stack.h
    Author: Carter Steckbeck
    Date: 3/07/20
    Assignment: Lab 03 (Sudoku)

    Declaration of a link-list-based stack data structure
************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <cstdlib>

class stack {
 public:
  typedef int element;

  // Stack no-arg constructor:
  // PRE: none
  // POST: this stack is initialized.  It contains no elements.
  stack();

  // push
  // PRE: there are fewer than MAX elements on this stack
  //      this stack has n elements: <v1,v2,...,vn>
  // POST: this stack has n+1 elements: <e,v1,v2,...,vn>
  void push(const element & e);

  // pop
  // PRE: this stack is not empty.
  //      this stack has n elements: <v1,v2,...,vn>
  // POST: this stack has n-1 elements: <v2,...,vn>
  void pop();

  // top
  // PRE: this stack is not empty.
  //      this stack has n elements: <v1,v2,...,vn>
  // POST: this stack is not changed.
  //       v1 is returned
  element top() const;

  // empty
  // PRE: none
  // POST: returns true if there are no elements in this stack,
  //       otherwise returns false.
  bool empty() const;

 private:
  struct node {
    element data;
    node *next;
    node();
    node(const element&, node*);
  };
  node* _top;
};

#endif
