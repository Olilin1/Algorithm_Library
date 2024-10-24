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

std::vector<size_t> knapsack(const int capacity, const std::vector<std::pair<int, int>>& items){
    std::vector<size_t> indices;

    std::vector<std::vector<int>> dp(capacity+1);
    for(size_t i = 0; i <= capacity; i++){
        dp[i].resize(items.size()+1);
    }

    //Fill out DP
    for(int weight = capacity; weight >= 0; --weight){
        for(int item = items.size(); item >= 0; --item){
            if(weight == capacity || item == items.size()) 
                dp[weight][item] = 0;
            else if (weight+items[item].first <= capacity)
                dp[weight][item] = std::max(dp[weight][item + 1], dp[weight+items[item].first][item + 1] + items[item].second);
            else
                dp[weight][item] = dp[weight][item + 1];
        }
    }

    //Reconstruct the solution
    int weight = 0;
    size_t item = 0;
    while(item != items.size() && weight != capacity){
        if (weight+items[item].first <= capacity && dp[weight+items[item].first][item + 1] + items[item].second > dp[weight][item + 1]){
            indices.push_back(item);
            weight += items[item].first;
            item++;
        }
        else{
            item++;
        }
    }

    return indices;
}


#endif