/************************************************************************
    File: stack.cc
    Author: Carter Steckbeck
    Date: 3/7/20

    Implementation of a link-list-based stack data structure
************************************************************************/

#include <iostream>
#include <cassert>
#include "stack.h"

stack::node::node() {}  // node constructor leaving fields uninitialized

stack::node::node(const element & item, node * n) {
  data = item;
  next = n;
}

// Constructor
stack::stack() {
  _top = nullptr;
}

// Function that places value on the top of the stack
void stack::push(const element & e)
{
  _top = new node(e, _top);
}

// Function that removes the top value of the stack
void stack::pop()
{
  node* old = _top;
  _top = _top->next;
  delete old;
}

// Function that returns the value that is on the top of the stack
stack::element stack::top() const
{
  return _top->data;
}

// Function that returns true if the stack is empty, false otherwise
bool stack::empty() const
{
  return _top == nullptr;
}
