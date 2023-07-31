/*
AUTHOR: Oliver Lindgren
*/

#include"Suffix_Sorting.hpp"

SuffixArray::SuffixArray(std::string const & s){
    std::vector<size_t> buckets(s.length());
    std::vector<size_t> newBuckets(s.length());
    std::vector<size_t> suffixPosition(s.length());

    buckets[0] = 0;
    newBuckets[0] = 0;

    for(size_t i = 0; i < s.size(); i++){
        sorted.push_back(i);
    }

    //Do an initial sorting on just the first charachter
    std::sort(sorted.begin(), sorted.end(), [&s](const size_t a, const size_t b){
        return s[a] < s[b];
    });

    buckets[0] = 0;
    suffixPosition[sorted[0]] = 0;

    for(int i = 1; i < s.length(); i++){
        if(s[sorted[i]] == s[sorted[i-1]]) buckets[i] = buckets[i-1];
        else buckets[i] = buckets[i-1] + 1;

        suffixPosition[sorted[i]] = buckets[i];
    }



    //This loop will run log(n) times
    for(int k = 1; k <= s.length(); k *= 2){

        //Sorting takes n log(n) time
        std::sort(sorted.begin(), sorted.end(), [&s, &k, &suffixPosition](const size_t a, const size_t b){
            if(suffixPosition[a] == suffixPosition[b]){
                //If one of the suffixes in this buckets end then it should come before the others
                if(a+k >= s.length() || b+k >= s.length()){
                    return a > b; // '>' instead of '<' because the bigger the number, the shorter the suffix
                }
                //Otherwise we sort based on the next 2^k chars, which have already been sorted somewhere else.
                return suffixPosition[a+k] < suffixPosition[b+k];
            }
            //If they don't belong to the same bucket then their relative position shall remain the same.
            return suffixPosition[a] < suffixPosition[b];
        });
        
        //This will run n times for bookkeeping
        for(int i = 1; i < s.length(); i++){
            if(buckets[i] > buckets[i-1]) newBuckets[i] = newBuckets[i-1] + 1;
            else if(suffixPosition[sorted[i] + k] > suffixPosition[sorted[i-1] + k]) newBuckets[i] = newBuckets[i-1] + 1;
            else newBuckets[i] = newBuckets[i-1];
        }

        buckets.swap(newBuckets);

        for(int i = 0; i < s.length(); i++){
            suffixPosition[sorted[i]] = buckets[i]; 
        }

    }
}

size_t SuffixArray::getSuffix(size_t i){
    return sorted[i];
}