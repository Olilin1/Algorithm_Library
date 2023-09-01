/*
    AUTHOR: Oliver Lindgren
*/

#ifndef COVER_HPP
#define COVER_HPP

#include<vector>
#include<utility>
#include<algorithm>

/*
Takes an interval to be covered as a pair of doubles, with the first pair value being the left bound of the interval,
and the second pair value being the right bound of the interval. It also takes a list of intervals that should be used to
try and cover this interval. Returns a vector containing the indices in the intervals vector relating to the intervals that need to be used.
If it is not possible to cover interval then an empty vector is returned.
O(n log(n)) - where n is the size of the intervals vector.

TODO: Template it & convert intervals to be range based.
*/


std::vector<size_t> cover(const std::pair<double, double> interval, const std::vector<std::pair<double, double>>& intervals){

    //Tripple will be used later to store intervals (first, second) as well as their index in the originial intervals array.
    struct Tripple{
        double first, second;
        size_t third;
    };

    double l = interval.first, r = interval.second;
    if(l == r){ //If the interval is a single point then deal with that case
        for(size_t i = 0; i < intervals.size(); i++){
            if(intervals[i].first <= l && intervals[i].second >= r) return {i};
        }

        return {};
    } 


    //Make a copy of intervals (where the original index is included also) and sort it based on where the intervals begin. This will be necessary to use the greedy algorithm effectively.
    std::vector<Tripple> intervalsCopy;

    intervalsCopy.reserve(intervals.size());

    for(size_t i = 0; i < intervals.size(); i++){
        intervalsCopy.push_back({intervals[i].first, intervals[i].second, i});
    }

    std::sort(intervalsCopy.begin(), intervalsCopy.end(), [](Tripple& a, Tripple& b){
        return a.first < b.first;
    });

    size_t index = 0;
    size_t bestIndex = 0;
    double reach = l;

    std::vector<size_t> solution;

    
    while(l < r){
        while(index < intervalsCopy.size() && intervalsCopy[index].first <= l){

            //Find whatever interval that begins before current l that reaches the furthest.
            if(intervalsCopy[index].second > reach){
                bestIndex = intervalsCopy[index].third;
                reach = intervalsCopy[index].second;
            }
            index++;
        }

        //If we couldn't extend the interval we are working on then return empty vector.
        if(reach == l) return {};

        l = reach;
        solution.push_back(bestIndex);
    }

    return solution;
}


#endif