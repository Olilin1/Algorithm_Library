/*
    AUTHOR: Oliver Lindgren
*/

#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP
#include<vector>
#include<utility>
#include<algorithm>

/*
A function that solves the knapsack problem and returns the indices in the items vector that should be used to obtain the optimal value.
Capacity is the maximum weight that the knapsack can hold. Must be non-negative.
Items is a list of non-negative integer pairs where the first value in each pair is the weight of the item, and the second pair is the value.
O(n*k) - where n is the size of the items vector and k is the capacity

TODO: Change to iterator based implementation, make capacity size_t, template it.
*/
std::vector<size_t> knapsack(const int capacity, const std::vector<std::pair<int,int>>& items);


#endif