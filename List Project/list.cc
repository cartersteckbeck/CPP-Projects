/************************************************************************
    File: list.cc
    Author: Carter Steckbeck

    Implementation of a doubly linked list
************************************************************************/

#include <cassert>
#include "list.h"

list::list()
{
  _init();
}

list::~list()
{
  _destroy();
}

list::list(const list & orig)
{
  _copy(orig);
}

list & list::operator=(const list & rhs)
{
  if (this != &rhs) {
    _destroy();
    _copy(rhs);
  }
  return *this;
}

// Function that adds an element to the list at a certain index
void list::add(const element & item, int index)
{
  // Sets current index and then inserts the item
  _set_current_index(_compute_index(index));
  insert(item);
}

// Function that inserts a new node into the list
void list::insert(const element & item)
{
  assert(_current != _front);

  // Set previous equal to node before _current and create a new node that is
  // right after previous
  node *previous = _current->prev;
  previous->next = new datanode(previous, item, _current);

  // Set _current's prev field equal to the new node and then set _current to
  // point to the new node, then increase _size
  _current->prev = previous->next;
  _current = previous->next;
  _size++;
}

// Function that removes an element of the list at a specific index
void list::remove_at(int index)
{
  // Set current index and then remove
  _set_current_index(_compute_index(index));
  remove();
}

// Function that removes the first instance of a given item in the list
void list::remove(const element & item)
{
  // Find the index of the item
  size_t index = find(item);

  // If the index is the _size, then return nothing (item was not found)
  if(index == size())
    return;

  // Otherwise, set current index and remove the item
  else{
    _set_current_index(index);
    remove();
  }
}

// Function that removes the node that _current is pointing at
void list::remove()
{
  // Set prev equal to the node before _current and set _current to the
  // following node
  node* previous = _current->prev;
  _current = _current->next;

  // Change prev next field to equal _current, then delete the middle node
  previous->next = _current;
  delete _current->prev;

  // Set _current prev field equal to previous and then decrease _size
  _current->prev = previous;
  _size--;
}

// Function that finds the first instance of a given item in the list
size_t list::find(const element & item) const
{
  // Set p equal to the first element in the list and declare count
  node* p = _front->next;
  size_t count = 0;

  // Iterate through the list
  while(p != _rear){
    datanode *q = static_cast<datanode*>(p);

    // If q's data field is equal to the item, return count, otherwise keep
    // going
    if (q->data == item)
      return count;
    p = p->next;
    count++;
  }

  // If the item is not found, return the size of the list
  return size();
}

// Function that returns the element in the list at a given index
list::element & list::get(int index)
{
  // Set current index, then the data that _current is pointing to
  _set_current_index(_compute_index(index));
  return static_cast<datanode*>(_current)->data;
}

// Same as previous get function, except returns a const version
const list::element & list::get(int index) const
{
  _set_current_index(_compute_index(index));
  return static_cast<datanode*>(_current)->data;
}

// Function that allows for list indexing
list::element & list::operator[](int index)
{
  return get(index);
}

// Same as previous function, const version
const list::element & list::operator[](int index) const
{
  return get(index);
}

// Function that sets _current to the first element in the list and sets
// _current_index equal to zero
void list::start_first() const
{
  _current = _front->next;
  _current_index = 0;
}

// Function that sets _current to the last element in the list and sets
// _current_index equal to _size - 1
void list::start_last() const
{
  _current = _rear->prev;
  _current_index = size() - 1;
}

// Function that returns true if _current points to the _rear, false otherwise
bool list::done() const
{
  if (_current == _rear)
    return true;
  return false;
}

// Function that advances _current to the next node and increase _current_index
void list::advance() const
{
  assert(_current != _rear);
  _current = _current->next;
  _current_index += 1;
}

// Function that retreats _current to the previous node and decrease
// _current_index
void list::retreat() const
{
  assert(_current != _front);
  _current = _current->prev;
  _current_index -= 1;
}

// Function that returns the node's data that _current is pointing to
list::element & list::current()
{
  assert(_current != _front || _current != _rear);
  return static_cast<datanode*>(_current)->data;
}

// Same as previous function, const version
const list::element & list::current() const
{
  assert(_current != _front || _current != _rear);
  return static_cast<datanode*>(_current)->data;
}

// Function that returns the size of the list
size_t list::size() const
{
  return _size;
}

// Function that writes out the list in list formt
void list::write(std::ostream & ostr) const
{
  ostr << "[";

  // Iterate through the list
  for (node *p = _front->next; p != _rear; p = p->next) {

    // If p is equal to _current, put stars around that element, otherwise
    // output it regularly
    if (p == _current){
      datanode *q = static_cast<datanode *>(p);
      ostr << "*" << q->data << "*";
    }
    else{
      datanode *q = static_cast<datanode *>(p);
      ostr << q->data;
    }

    // If the next node is not the _rear, then output a comma
    if (p->next != _rear)
      ostr << ", ";
  }
  ostr << "]";
}

// List node constructors provided by Prof. Campbell

list::node::node(node* p, node* n): prev(p), next(n) {}

list::datanode::datanode(node* p, const element& e, node* n):
  node(p,n), data(e) {}

// Function that converts negative indices into positive indices
size_t list::_compute_index(int index) const
{
  assert(static_cast<int>(-size())<=index && index<=static_cast<int>(size()));

  // If the index is negative, add the size of the list to it and return it
  if(index < 0)
    return index + size();

  // Otherwise, return the index
  else
    return index;
}

// Function that sets _current_index and _current to a given index
// Taken from class notes
void list::_set_current_index(size_t index) const
{
  index = _compute_index(index);
  for (_current = _front->next, _current_index = 0;
       _current_index < index;
       _current = _current->next, _current_index++) {}
}

// Constructor
// Taken from class notes
void list::_init()
{
  _front = new node(nullptr, nullptr);
  _rear = new node(nullptr, nullptr);
  _front->next = _rear;
  _rear->prev = _front;
  _size = 0;
  _current = _rear;
  _current_index = 0;
}

// Function that given a list, copies that list to make a new list
void list::_copy(const list & orig)
{
  // Make a new list by calling _init() set curr equal to the nullptr
  _init();
  node* curr = nullptr;

  // Iterate through the original list
  for (node* p = orig._front->next; p != orig._rear; p = p->next){
    insert(static_cast<datanode*>(p)->data);

    // If p is equal to the original current, set curr equal to that _current,
    // then advance
    if(p == orig._current)
      curr = _current;
    advance();
  }

  // If curr is not the nullptr, set _current equal to curr
  if(curr)
    _current = curr;
}

// Function that destroys the list after the program is done running
void list::_destroy()
{
  // Start at the first node, then remove each node until size is zero
  start_first();
  while(_size != 0)
    remove();
}

std::ostream & operator<<(std::ostream & ostr, const list & lst)
{
  lst.write(ostr);
  return ostr;
}
