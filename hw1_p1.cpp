#include <iostream>
#include "huffman.h"
#include <vector>
#include "cmath"
using namespace std;

int main(int argc, char* argv[]) {
  Huffman huff;
  // read parameters here ...
  string b;
  cin>>b;
  int x,y;
  //handling comments in pgm files 
  while (1) {
    cin>>b;
    if (b[0]!='#')
      break;
    else 
      cin.ignore(5000,'\n');
  }
  x=stoi(b);
  cin>>y;
  b=argv[1];
  string c;
  int depth;
  cin>>depth;
  int a;
  //Vector that contains the symbol,probability and frequency
  vector<Symbol> sym;
  //get the msg
  vector<int> file;
  while (cin>>a)
    file.push_back(a);
  vector<unsigned char> msg;
  //converting msg to unsigned char
  for (int i=0;i<file.size();i++) {
    msg.push_back((unsigned char)file[i]);
  }
  vector <unsigned int>output;
  // perform the required operation ...
  if (b.compare("-entropy")==0) 
      a=0;
  else if (b.compare("-tree")==0) 
      a=1;
  else if (b.compare("-encode")==0 && argc==2)
      a=2;
  else 
      a=3;
  vector<unsigned char> difference =msg;
  int bits;
  for (int i=0;i<difference.size();i++) {
    if (i%x!=0)
    //get the difference from the left neighbour
      difference[i]=(unsigned char)((int)difference[i]-(int)msg[i-1]);
  }
  // write output ...
  switch(a) {
    case 0:
      cout<<"Entropy= "<<huff.compute_entropy(msg,&sym)<<endl;
      break;
    case 1:
      huff.compute_entropy(msg,&sym);
      huff.build_tree(sym);
      huff.print_code_table();
      break;
    case 2:
      huff.compute_entropy(msg,&sym);
      huff.build_tree(sym);
      bits=huff.encode(msg,&output);
      cout<<"# of bits = "<<bits<<endl;
      cout<<"# of bytes = "<<(float)bits/8<<endl;
      cout<<"Compression ratio = "<<ceil(log2(depth))*x*y/(float)bits<<endl;
      //Output array
       cout<<"Output array:\n";
      for (int i=0;i<output.size();i++)
        cout<<output[i]<<" ";
        break;
    case 3:
      huff.compute_entropy(difference,&sym);
      huff.build_tree(sym);
      bits=huff.encode(difference,&output);
      cout<<"# of bits = "<<bits<<endl;
      cout<<"# of bytes = "<<(float)bits/8<<endl;
      cout<<"Compression ratio = "<<ceil(log2(depth))*x*y/(float)bits<<endl;
    default:
      break;
  }
  return 0;
}