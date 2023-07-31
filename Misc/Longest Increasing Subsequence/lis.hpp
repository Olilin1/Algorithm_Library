/*
AUTHOR: Oliver Lindgren
*/

#ifndef LONGEST_INCREASING_SUBSEQUENCE_HPP
#define LONGEST_INCREASING_SUBSEQUENCE_HPP
#include<vector>
#include<iterator>
#include<limits>
#include<algorithm>

/*
Takes a vector of integers and returns a vector of the indicies that should be used if you want to construct the longest possible subsequence using those integers.
O(N*log(N))
*/
std::vector<size_t> lis(const std::vector<long long int>&);


#endif