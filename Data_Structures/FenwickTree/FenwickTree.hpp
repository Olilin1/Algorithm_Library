/*
AUTHOR: Oliver Lindgren
*/

#ifndef FENWICKTREE_HPP
#define FENWICKTREE_HPP

#include<cstddef>

//A class designed to compute and maintain the prefix sum of an array.
class FenwickTree{
private:
    long long int* base;
    size_t size;
public:
    //initSize is the size of the array to be stored.
    FenwickTree(size_t initSize);
    ~FenwickTree();

    //This increases the value of array[index] with value.
    void Update(size_t index, long long int value);

    //This querys the array to get the sum of all the values in the array in the range [0, index)
    long long int Query(size_t index);
};

#endif