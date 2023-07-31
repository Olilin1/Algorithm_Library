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

#endif