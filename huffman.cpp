#include "huffman.h" 
#include "cmath"
#include <bits/stdc++.h> 

// Your implementations here

Huffman::Huffman(){}

float Huffman::compute_entropy(const vector<unsigned char>& msg,vector<Symbol>* prob) {
    int freq=0;
    //loop to get all symbols and its frequencies in the msg
    for (int i=0;i<msg.size();i++) {
        bool isFound;
        for (vector<Symbol>::iterator it=prob->begin();it<prob->end();it++) {
            isFound=false;
            if (msg[i]==it->val) {
                it->frequency++;
                isFound=true;
                break;
            }
        }
        if (!isFound)
            prob->push_back({msg[i],1,0});
    }
    //calculate probability for every symbol
    for (vector<Symbol>::iterator it=prob->begin();it<prob->end();it++) {
        it->propability=(float)it->frequency/msg.size();
    }
    //calculating entropy
    float entropy=0;
    for (vector<Symbol>::iterator it=prob->begin();it<prob->end();it++) {
        entropy-=(float)(it->propability)*log2(it->propability);
    }
    return entropy;
}
// Compare probabilities
bool compareProb(pair<Symbol,Node*> s1, pair<Symbol,Node*> s2) 
{ 
    return (s1.first.propability > s2.first.propability); 
} 

//Getting Huffman code and Huffman tree
void Huffman::build_tree(const vector<Symbol>& prob) {
    //vector that contains the symbols and poiter to refere to new nodes that contains more than 1 symbol
    vector< pair<Symbol,Node*> > s;
    Node* node;
    int freq;
    float pro;
    //putting prob in new vector to make operations on it
    for (int i=0;i<prob.size();i++) {
            s.push_back(make_pair(prob[i],nullptr));
        }
    //to generate nodes to the tree
    while (s.size()>1) {
        freq=0;
        pro=0;
        sort(s.begin(),s.end(),compareProb);
        //initialize new node in the tree
        node=new Node;
        node->val+=s.back().first.frequency;
        freq+=s.back().first.frequency;
        pro+=s.back().first.propability;
        if (!s.back().second) {
            //if this node is symbol then make this symbol to the left of the new node
            node->left=new Node{s.back().first.val,nullptr,nullptr};
            //push 0 to the codeword as this value is on the left 
            vector<bitset<1>>temp;
            temp.push_back(0);
            codeWord.push_back(make_pair(make_pair(s.back().first.val,temp),node));
        }
        else {
            node->left=s.back().second;
            for (int j=0;j<codeWord.size();j++)
            {
                //if this node is already a parent (not symbol to be encoded) then add 0 to all of its children 
                //and make the new parent parent to every child node belongs to this node
                if (codeWord[j].second==node->left) {
                    codeWord[j].second=node;
                    codeWord[j].first.second.push_back(0);
                }
            }
        }
        s.pop_back();
        node->val+=s.back().first.frequency;
        freq+=s.back().first.frequency;
        pro+=s.back().first.propability;
        //like above but for the right branch
        if (!s.back().second) {
            node->right=new Node{s.back().first.val,nullptr,nullptr};
            vector<bitset<1>>temp;
            temp.push_back(1);
            codeWord.push_back(make_pair(make_pair(s.back().first.val,temp),node));  
        }
        else {
            node->right=s.back().second;
            for (int j=0;j<codeWord.size();j++)
            {
                if (codeWord[j].second == node->right) {
                    codeWord[j].second=node;
                    codeWord[j].first.second.push_back(1);
                }
            }
        }
        s.pop_back();
        //pushing the new node prob to the s vector
        s.push_back(make_pair(Symbol{node->val,freq,pro},node));
    }
    tree=node;
    //to print tree
}

void Huffman::print_code_table() {
    cout<<"Symbols code:";
    cout<<endl<<"_________________\n";
    for (int i=codeWord.size()-1;i>=0;i--) {
        cout<<(int)codeWord[i].first.first<<" : ";
        //to print the code
        for (int j=codeWord[i].first.second.size()-1;j>=0;j--)
            cout<<codeWord[i].first.second[j];
        cout<<endl;
    }
}

int Huffman::encode(const vector<unsigned char>& msg,vector<unsigned int>* encoded_msg) {
    //number of bits in img
    int bits=0;
    for (int i=0;i<msg.size();i++) {
        for (int j=0;j<codeWord.size();j++) {
            //the encoded bits
            
            if (codeWord[j].first.first==msg[i]) {
                bits+=codeWord[j].first.second.size();
                int n=0;
                for (int k=0;k<codeWord[j].first.second.size();k++) {
                    n+=pow(2,k)*(int)codeWord[j].first.second[k].to_ulong();
                }
                encoded_msg->push_back(n);
                break;
            }
        }
    }
    return bits;
}

Huffman::~Huffman(){}