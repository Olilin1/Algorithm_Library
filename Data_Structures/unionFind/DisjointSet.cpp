/*
    AUTHOR: Oliver Lindgren
*/

#include "DisjointSet.hpp"

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