/************************************************************************
    File: list.h
    Author: Carter Steckbeck

    Declaration of a doubly linked list
************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <iostream>

class list
{
 public:
  typedef int element;

  list();
  // Create an empty doubly-linked list with front and rear sentinels,
  // _current points to rear, and _current_index = 0;

  ~list();
  // Delete all nodes (including the sentinels)

  list(const list & orig);
  // Make a copy of a list so that the copy does not share nodes with the
  // original.

  list & operator=(const list & rhs);
  // Support list assignment, with copy.

  void add(const element & item,int index);
  // Insert a new element at a position (k) given by index.
  //     If index is non-negative, k is index; otherwise
  //     k is size() + index.
  // PRE:  -size() <= index <= size()
  //       this list contains <v0, v1, ..., vk, ...>
  // POST: this list contains <v0, v1, ..., item, vk, ... >
  //       _current points to new node containing item.
  //       _current_index is k.
  // Guarantees constant time access to either end or vicinity of
  // _current_index.  See _set_current_index().

  void insert(const element &);
  // Pre: _current is not pointing to the front sentinel
  // Post: An element is inserted before the _current
  //       _current points to the node containing the inserted item.

  void remove_at(int index);
  // Remove an element from this list.
  // Pre: -size() <= index <= size()
  //       index indicates a position k in the manner described in (add).
  //      This list contains <v0, v1, ..., vk, v(k+1), ... >
  // Post: This list contains <v0, v1, ..., v(k+1), ... >
  //       _current points to v(k+1) (or the rear sentinel)
  // Guarantees constant time access to either end or vicinity of
  // _current_index.

  void remove(const element & item);
  // Let i be the smallest non-negative integer where get(i)==item.
  // Post: same as for removeAt(i)
  // If no such i exists, the list is completely unchanged.

  void remove();
  // Pre: _current is pointing to a datanode
  // Post: The element is removed.  _current points to the node that followed
  //       the deleted removed node.  (_current_index is unchanged.)

  size_t find(const element & item) const;
  // return smallest non-negative integer where get(i)==item,
  // or size() if no such integer.
  // Does not modify _current or _current_index.

  list::element & get(int index);
  const list::element & get(int index) const;
  // Pre: -size() <= index <= size()
  // index indicates a position k in the manner described in (add).
  // Sets _current_index to k, and returns the element at position k.
  // Guarantees constant time access to either end or vicinity of
  // _current_index.

  // Iteration methods:

  void start_first() const ;
  // Post: _current points to the node following the front sentinel
  //       _current_index is 0;

  void start_last() const;
  // Post: _current points to the node preceding the rear sentinel.
  //       If that is a datanode, _current_index is size()-1.

  bool done() const;
  // Return true if _current points to a sentinel, false otherwise.

  void advance() const;
  // Pre: _current points to a node N that is not the rear sentinel
  // Post _current to the node following N.

  void retreat() const ;
  // Pre: _current points to a node N that is not the front sentinel
  // Post: _current points to node preceding N.

  element & current();
  const element & current() const;
  // Pre: _current is not pointing to a sentinel
  // Returns a (const) reference to the data in the node that
  // _current points to.


  list::element & operator[](int index);
  const list::element & operator[](int index) const;
  // Same as get(), allowing the use of the indexing operator for a list


  size_t size() const;
  // return the number of elements of the list
  // runs in constant time

  void write(std::ostream & ostr) const;
  // write the list to ostr using format
  // [v0, v1, v2, ..., vn-1]
  // If _current is pointing to a datanode, that's indicated by
  // surrounding the value with asterisks, e.g. [1, 4, -2, *3*, 8]
  // _current and _current_index are unchanged

 private:

  // Struct definitions:
  struct node { // base class for list nodes
    node *prev, *next;
    node(node*, node*);  // construct a node with given pointers
  };

  struct datanode: public node {
    element data;
    datanode(node*, const element &, node*); // construct a node with data
  };


  // Helper methods:
  size_t _compute_index(int index) const;
  // Pre: -size() <= index <= size();
  // return the effective non-negative index

  void _set_current_index(size_t index) const;
  // PRE: 0 <= index <= size()
  // POST: (1) _current points to the node holding the element at position
  //       index, or to the rear sentinel.
  //       (2) _current_index is index
  // This is accomplished as quickly as possible.  (Start at
  // one of _front, _rear, or _current, whichever is closest
  // to the desired node.)

  // Memory management helper methods:
  void _init();
  void _copy(const list & orig);
  void _destroy();

  // Instance variables:
  size_t _size; // number of data items
  node* _front;  // points to front sentinel
  node* _rear;   // points to rear sentinel
  mutable node* _current;  // points to a node in the list, including either
                           // sentinel.
  mutable size_t _current_index;
    // corresponds to current (0 <= _current_index <= size() ) when
    // _current is not pointing to the front sentinel.

};

std::ostream & operator<<(std::ostream &, const list &);
// wrapper for a call to write()

#endif
