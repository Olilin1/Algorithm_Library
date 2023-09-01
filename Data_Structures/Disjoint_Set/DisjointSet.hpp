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
*/

class DisjointSet {
private:
    //Used to keep track of what set elements are in, and the size of that set.
    std::vector<size_t> comp; 

    //What other element is a in the same set as? A negative number if a represents itself
    size_t representative(size_t a){
        if(comp[a] < 0) return a;

        //recursively find and update our representative
        comp[a] = representative(comp[a]);
        return comp[a];
    }  

public:
    //The constructor takes as input the amount of elements that exists.
    DisjointSet(size_t elements) : comp(elements, -1) {};

    //The unionSets function takes two elements as input and merges the sets that they are in.
    void unionSets(size_t a, size_t b){
        a = representative(a);
        b = representative(b);

        if(a == b) return;

        if(comp[a] > comp[b]) std::swap(a,b);

        comp[a] += comp[b]; //The size of set containing a has been increased by size of set containing b.
        comp[b] = a;
    }

    //The query function takes two elements as input and returns true if they are in the same set. Otherwise it returns false.
    bool query(size_t a, size_t b){
        return representative(a) == representative(b);
    }
};

#endif