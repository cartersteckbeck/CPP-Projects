/***********************************************
* File: huffman.cc
*
* Author: Carter Steckbeck
*
* Description: Program that uses Huffman Encoding Algorithm to compress a given text file
*
*************************************************/

#include <iostream>
#include <fstream>
#include <cassert>

// Function signature declarations
void error(const std::string &);
void encode(int argc, char **argv); // the encoder program
void decode(int argc, char **argv); // the decoder program

// Class and struct declarations
struct hnode {
  unsigned char character;
  size_t count;
  hnode * left;
  hnode * right;
  hnode(unsigned char ch, size_t c, hnode* l = nullptr, hnode *r = nullptr) :
    character(ch), count(c), left(l), right(r) {}
};

// Function that chelcs if t1's count is less than t2's count or
// t1's count equals t2's count and t1's character is less than t2's character
bool hnodeless(hnode * & t1, hnode * & t2)
{
  if ((t1->count < t2->count) || (t1->count == t2->count &&
      t1->character < t2->character))
    return true;
  return false;
}

// Function that writes data in a linear fashion: Lc for a leaf, It1t2 for
// an internal node
void write_tree(hnode *tree)
{

  // If the tree has a left hnode, output I for an internal node and
  // recursively call write_tree for the left and right side of the tree
  if(tree->left){
    std::cout << "I";
    write_tree(tree->left);
    write_tree(tree->right);
  }

  // Otherwise, hnode must be a leaf, so output L and hnode's character
  else
    std::cout << "L" << (char) tree->character;
}

// Function that traverses the tree, keeping track of the path to each leaf.
void get_codes(hnode *tree, std::string *codes, std::string pathtaken)
{

  // At a leaf, assign to codes[tree->character] the path taken
  if (!tree->left and !tree->right){
    codes[tree->character] = pathtaken;
  }

  // If tree has a left hnode, call get_codes recursively for the left side
  // of tree, adding a '0' to pathtaken and modifying pathtaken
  if (tree->left){
    get_codes(tree->left, codes, pathtaken += '0');
    pathtaken = pathtaken.substr(0, pathtaken.size() - 1);
  }

  // If tree has a right hnode, call get_codes recursively for the right side
  // of tree, adding a '1' to pathtaken and modifying pathtaken
  if (tree->right){
    get_codes(tree->right, codes, pathtaken += '1');
    pathtaken = pathtaken.substr(0, pathtaken.size() - 1);
  }
}

// Function that writes the num_characters in decimal form and calls write_tree
void write_header(size_t num_characters, hnode *tree)
{
  std::cout << num_characters;
  write_tree(tree);
}

// Function that converts a bitstring to a unsigned char
unsigned char bitstring_to_char(std::string s)
{
  unsigned char result = 0;
  unsigned char v;
  size_t i;

  // Iterate 8 times
  for (i = 0, v= 128; i < 8; i++, v /= 2){

    // If the bitstring at i equals '1', add v to result
    if (s[i] == '1')
      result += v;
  }
  return result;
}

// Function that writes the encoded content
void write_content(char *filename, std::string *codes)
{

  // Open the file
  std::ifstream input;
  input.open(filename);

  // Declare the buffer and the bitstring
  std::string buffer;
  std::string bitstring;

  // If there is no input, print an error message
  if (!input)
    error(std::string("Can't open ") + filename + " for reading");

  // While the input is good, assign input.get() to char and add codes[ch]
  // to buffer
  while(input){
    int ch = input.get();
    if(input)
      buffer += codes[ch];
  }

  // While the buffer is greather or equal to 0, assign buffer substring with
  // length 8 to bitstring, modify buffer and output unsigned char version
  // of the bitstring
  while (buffer.size() >= 8){
    bitstring = buffer.substr(0,8);
    buffer = buffer.substr(8);
    std::cout << bitstring_to_char(bitstring);
  }

  // If the buffer is greater than 0, add '0' till the size of the buffer
  // equal 8, then repeat same operation as above
  if (buffer.size() > 0){
    while(buffer.size() != 8){
      buffer += "0";
    }
    bitstring = buffer.substr(0, 8);
    std::cout << bitstring_to_char(bitstring);
  }
}

// Function that converts an unsigned char to a bitstring
std::string char_to_bitstring(unsigned char ch)
{
  std::string result = "";
  unsigned char v;
  size_t i;

  // Iterate 8 times
  for (i = 0, v = 128; i < 8; i++, v /= 2){

    // If ch is greater than or equal to v, add '1' to result and subtract v
    // from ch
    if (ch >= v){
      result += '1';
      ch -= v;
    }

    // Otherwise add '0' to result
    else
      result += '0';
  }
  return result;
}

// Function that reads the linear form of the tree and converts it to hnode form
hnode *read_tree(std::istream & istr)
{

  // Assign v to istr.get()
  int v = istr.get();

  // If v is a leaf, create a new hnode
  if (v == 'L')
    return new hnode(istr.get(), 0, nullptr, nullptr);

  // Otherwise, call function recursively and create a new hnode
  else{
    hnode *left = read_tree(istr);
    hnode *right = read_tree(istr);
    return new hnode(left->character, 0, left, right);
  }
}

// Function that reads the header by getting the file_size and reading the tree
void read_header(size_t & num_characters, hnode * & tree)
{
  size_t file_size;
  std::cin >> file_size;
  num_characters = file_size;
  tree = read_tree(std::cin);
}

// Function that follows a path in the tree from the root to a leaf according
// to the bits in bit_buffer
hnode *read_bytes_to_leaf(hnode *root, std::string & bit_buffer)
{

  // If the root is a leaf, return the root
  if (!root->left and !root->right)
    return root;

  // If the bit_buffer at 0 is equal to '0', remove it from bit_buffer and
  // call read_bytes_to_leaf recursively with left side of the tree
  else if (bit_buffer[0] == '0'){
    bit_buffer = bit_buffer.substr(1);
    return read_bytes_to_leaf(root->left, bit_buffer);
  }

  // If the bit_buffer at 0 is equal to '1', remove it from bit_buffer and
  // call read_bytes_to_leaf recursively with right side of the tree
  else if (bit_buffer[0] == '1'){
    bit_buffer = bit_buffer.substr(1);
    return read_bytes_to_leaf(root->right, bit_buffer);
  }

  // Otherwise, get at a new byte, convert it to a bitstring, assign it to
  // bit_buffer and call read_bytes_to_leaf recursively
  else{
    unsigned char byte = std::cin.get();
    bit_buffer = char_to_bitstring(byte);
    return read_bytes_to_leaf(root, bit_buffer);
  }
}

// Provided by Professor Campbell

class priority_queue {
private:
  struct node {
    hnode *data;
    node *next;
    node(hnode *d, node *n) : data(d), next(n) {}
  };

  static void _add(hnode * item, node * & list)
  {
    if (!list or hnodeless(item, list->data))
      list = new node(item, list);
    else
      _add(item, list->next);
  }

  node * _front;
  size_t _size;
public:
  priority_queue() { _size = 0; _front = nullptr; }
  size_t size() { return _size; }
  void add(hnode * item)
  {
    _add(item, _front);
    _size++;
  }

  hnode *remove()
  {
    hnode *item = _front->data;
    node *old = _front;
    _front = _front->next;
    delete old;
    _size--;
    return item;
  }
};

void get_counts(char * filename, size_t *counts, size_t & num_characters)
{
  for (size_t i=0; i < 256; i++)
    counts[i] = 0;
  std::ifstream input(filename);
  if (!input)
    error(std::string("Can't open ") + filename + " for reading");
  while(input) {
    int ch = input.get();
    if (input) {
      counts[ch]++;
      num_characters++;
    }
  }
  input.close();
}

void encode(int argc, char **argv)
{
  if (argc != 2)
    error(std::string("Usage: encode filename"));
  size_t counts[256];
  std::string codes[256];
  size_t num_characters = 0;
  get_counts(argv[1], counts, num_characters);
  priority_queue queue; // contains hnode *
  for (size_t i=0; i<256; i++)
    if (counts[i] > 0) {
      queue.add(new hnode(i, counts[i]));
    }
  while (queue.size() > 1) {
    hnode * left = queue.remove();
    hnode * right = queue.remove();
    hnode * baby = new hnode(left->character, left->count + right->count,
                             left, right);
    queue.add(baby);
  }
  hnode *tree = queue.remove();
  get_codes(tree, codes, "");
  write_header(num_characters, tree);
  write_content(argv[1], codes);
}

void decode(int argc , char **/* argv */)
{
  if (argc != 1)
    error(std::string("Usage: decode"));
  size_t num_characters;
  hnode *tree;
  read_header(num_characters, tree);
  size_t count = 0;
  std::string bit_buffer = "";
  while (count < num_characters) {
    hnode *leaf = read_bytes_to_leaf(tree, bit_buffer);
    std::cout << leaf->character;
    count++;
  }
}

void error(const std::string & message)
{
  std::cout << message << std::endl;
  exit(1);
}

int main(int argc, char **argv)
{
  if (std::string(argv[0]) == "./encode")
    encode(argc, argv);
  else if (std::string(argv[0]) == "./decode")
    decode (argc, argv);
  else
    error(std::string("Usage: encode file OR decode"));
}
