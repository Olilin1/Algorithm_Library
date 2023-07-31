/*
AUTHOR: Oliver Lindgren
*/

#include "FenwickTree.hpp"

FenwickTree::FenwickTree(size_t initSize){
    size = initSize+1;
    base = new long long int[size]();
}

FenwickTree::~FenwickTree(){
    delete[] base; 
}


void FenwickTree::Update(size_t index, long long int value){
    index++;

    //Use bit indexing to update necessary values.
    while(index < size){
        base[index] += value;
        index += index & (-index);
    }
}

long long int FenwickTree::Query(size_t index){
    long long int sum = 0;

    //Use bit indexing to retrieve necessary values.
    while(index > 0){
        sum += base[index];
        index -= index & (-index);
    }
    return sum;
}