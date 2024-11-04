/*
AUTHOR: Oliver Lindgren
*/

#ifndef FENWICKTREE_HPP
#define FENWICKTREE_HPP

#include<cstddef>

//A class designed to compute and maintain the prefix sum of an array.
template<class T>
class FenwickTree{
private:
    T* base;
    size_t size;
public:
    //initSize is the size of the array to be stored.
    FenwickTree(size_t initSize){
        size = initSize+1;
        base = new T[size]();
    }

    ~FenwickTree(){
        delete[] base; 
    }

    //This increases the value of array[index] with value.
    void Update(size_t index, T value){
        index++;

        //Use bit indexing to update necessary values.
        while(index < size){
            base[index] += value;
            index += index & (-index);
        }
    }

    //This querys the array to get the sum of all the values in the array in the range [0, index)
    T Query(size_t index){
        T sum = 0;

        //Use bit indexing to retrieve necessary values.
        while(index > 0){
            sum += base[index];
            index -= index & (-index);
        }
        return sum;
    }

    //This querys the array to get the sum of all the values in the array in the range [left, right)
    T Query_Range(size_t left, size_t right){
        // 0 1 2 3 4 5     l = 2  r = 4 results in [2, 3]
        return Query(right) - Query(left);
    }
};

#endif