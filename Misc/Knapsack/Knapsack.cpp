/*
    AUTHOR: Oliver Lindgren
*/


#include "Knapsack.hpp"

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
