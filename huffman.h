#ifndef _HUFFMAN_H
#define _HUFFMAN_H
using namespace std;
#include <vector>
#include<bitset>
// Define the tree node struct here ...
struct Node {
  // ...
  int val=0;
  Node* left=nullptr;
  Node* right=nullptr;
};

// Define a symbol struct here to hold the symbol (grayscale value)
// and its probability/frequency
struct Symbol {
  // Grayscale value of the symbol
  unsigned char val;
  // frequency
  int frequency;
  float propability;
};

class Huffman {
public:
  // Constructor and destructor
  Huffman();
  ~Huffman();
  // A function to compute the entropy of the input message and
  // stores the probabilities of the different symbols in
  // the input array.
  float compute_entropy(const vector<unsigned char>& msg,
                        vector<Symbol>* prob);
  
  // A function to build the Huffman tree given the computed
  // symbol probabilities.
  void build_tree(const vector<Symbol>& prob);
  
  // A function to print the code table computed from the build_tree above.
  void print_code_table();
  
  // A function to encode the input message using the computed tree 
  // and store the output in the output array, where each entry
  // corresponds to the codeword for an input symbol in the message.
  //
  // The function should return the number of bits in the encoded 
  // message.
  int encode(const vector<unsigned char>& msg,
             vector<unsigned int>* encoded_msg);
              
private:
  // Data members here ... for example to store the tree and the codeword 
  // hash table
  Node* tree;
  vector< pair< pair< unsigned char,vector<bitset<1>> >, Node* >> codeWord;
};

#endif