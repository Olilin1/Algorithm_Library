/*
    AUTHOR: Oliver Lindgren
*/

#ifndef DISJOINTSET_HPP
#define DISJOINTSET_HPP

#include<vector>
#include<functional>

/*
A class designed to keep track of N different sets of N total elements.
Has a function to merge two sets, and a function to check if two elements are in the same set.
TODO: Change to size_t
*/
class DisjointSet {
private:
    //! Used to keep track of what set elements are in, and the size of that set.
    std::vector<int> comp; 

    //!What other element is a in the same set as? A negative number if a represents itself
    int representative(unsigned int a);  

public:
    //! The constructor takes as input the amount of elements that exists.
    DisjointSet(unsigned int elements);

    //! The unionSets function takes two elements as input and merges the sets that they are in.
    void unionSets(unsigned int a, unsigned int b);

    //! The query function takes two elements as input and returns true if they are in the same set. Otherwise it returns false.
    bool query(unsigned int a, unsigned int b);
};
















DisjointSet::DisjointSet(unsigned int elements) : comp(elements, -1) {};

void DisjointSet::unionSets(unsigned int a, unsigned int b){
    a = representative(a);
    b = representative(b);

    if(a == b) return;

    if(comp[a] > comp[b]) std::swap(a,b);

    comp[a] += comp[b]; //The size of set containing a has been increased by size of set containing b.
    comp[b] = a; //All elements that had b as a representative will now have a as a representative.
}

int DisjointSet::representative(unsigned int a){
    if(comp[a] < 0) return a;

    //recursively find and update our representative
    comp[a] = representative(comp[a]);
    return comp[a];
}

bool DisjointSet::query(unsigned int a, unsigned int b){
    return representative(a) == representative(b);
}



#endif