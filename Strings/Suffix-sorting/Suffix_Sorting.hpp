/*
AUTHOR: Oliver Lindgren
*/

#ifndef SUFFIX_ARRAY_HPP
#define SUFFIX_ARRAY_HPP

#include<string>
#include<algorithm>
#include<vector>
#include<iostream>
#include<stddef.h>

/*
A class that computes the suffix-array of a string s.
Takes a string to compute the array for as argument to the constructor.
Also provides a function getSuffix(i) which returns the index in s at which the i:th smallest suffix begins.

Time complexity of the constructor is O(n log^2(n)),
getSuffix runs in constant time.
*/
class SuffixArray{
private:
    std::vector<size_t> sorted;
    
public:
    SuffixArray(std::string const & s);
    size_t getSuffix(size_t i);

};

#endif