/*
Author: Oliver Lindgren
*/

#ifndef AHO_CORASICK_HPP
#define AHO_CORASICK_HPP
#include<vector>
#include<string>
#include<queue>
#include<iostream>

/*
A class that implements the Aho-Corasick string matching algorithm.
It provides three functions of interest:

add_string(s) adds a string pattern to be matched against.
construct_automaton() constructs the automaton that will be used in the string matching. Call this once all strings you want to match against have been added.
search(s) searches through the string s. Returns a vector V of vectors containing the indicies in s where a pattern was sucessfully matched. V[i] contains the positions of where the ith string added match.
*/

class TrieAutomaton{
struct Node{
    std::vector<int> terminal;
    int depth;
    Node* suffixNode = nullptr;
    Node* terminalChain;
    char nodeChar = 'X';

    std::vector<Node*> transition = std::vector<Node*>(128, nullptr);
};

Node* root = new Node();
size_t stringIndex = 0;
std::vector<Node*> nodes;

public:
TrieAutomaton();
~TrieAutomaton();

void add_string(std::string const & s);
void construct_automaton();

std::vector<std::vector<size_t>> search(std::string const & s);


};















































void TrieAutomaton::add_string(std::string const & s){
    Node* at = root;

    for(char c : s){
        if(at->transition[c] == nullptr){
            Node* newNode = new Node();
            nodes.push_back(newNode);
            newNode->depth = at->depth + 1;
            newNode->nodeChar = c;
            at->transition[c] = newNode;
        }
         at = at->transition[c];
    }

    at->terminal.push_back(stringIndex);
    stringIndex++;
}

void TrieAutomaton::construct_automaton(){
    Node* at;
    std::queue<Node*> bfsQ;
    bfsQ.push(root);

    while(!bfsQ.empty()){
        at = bfsQ.front();
        bfsQ.pop();
        for(unsigned char c = 0; c < 128; c++){
            if(at->transition[c] == nullptr){
                if(at == root) at->transition[c] = root;
                else at->transition[c] = at->suffixNode->transition[c];

            }
            else{
                if(at == root) at->transition[c]->suffixNode = root;
                else at->transition[c]->suffixNode = at->suffixNode->transition[c]; //Could probably make some chain here during construction.

    //Suffix chain
    if(!at->suffixNode->transition[c]->terminal.empty()){
        at->transition[c]->terminalChain = at->suffixNode->transition[c];
    }
    else{
        at->transition[c]->terminalChain = at->suffixNode->transition[c]->terminalChain;
    }

    if(at == root){
        at->transition[c]->terminalChain = root;
    }
                bfsQ.push(at->transition[c]);
            }
        }
    }
}

std::vector<std::vector<size_t>> TrieAutomaton::search(std::string const & s){
    Node* at = root;
    std::vector<std::vector<size_t>> ans(stringIndex);
    for(size_t i = 0; i < s.length(); i++){
        char c = s[i];
        at = at->transition[c];
        
        Node* suffixLinking = at;
        Node* prev = nullptr;
        while(suffixLinking != root){  //Somehow safe the previous terminal suffix for all nodes to save time.
            if(suffixLinking == prev) std::cerr << "Linking err";
            
            for(auto index : suffixLinking->terminal){
                ans[index].push_back(i - suffixLinking->depth + 1);
            }
            
            prev = suffixLinking;
            suffixLinking = suffixLinking->terminalChain;
        }
    }
    return ans;
}

TrieAutomaton::TrieAutomaton(){
    root->suffixNode = root;
    root->depth = 0;
    root->terminalChain = root;
}

TrieAutomaton::~TrieAutomaton(){
    delete root;
    for(auto x : nodes){
        delete x;
    }
}
#endif