/*
AUTHOR: Oliver Lindgren
*/
#include "lis.hpp"

std::vector<size_t> lis(const std::vector<long long int>& v){
    typedef long long int ll;
    const ll inf = std::numeric_limits<ll>::max();

    std::vector<size_t> ans;
    std::vector<std::pair<ll, size_t>> last(v.size()+1, {inf, inf}); //Last[L].first is the lowest value so far that can end a subsequence of length L. Second är L's index i v
    std::vector<size_t> backTrack(v.size(), inf);
    last[0].first = -last[0].first;

    for(size_t i = 0; i < v.size(); i++){
        
        //it pekar på första elementet som är större än v[i].
        auto it = std::upper_bound(last.begin(), last.end(), v[i], [](auto value, auto elem){
            return value < elem.first;
        }); 

        if((it-1)->first < v[i]){ //Kolla så att det går att avsluta en subsequence av längd L-1 med ett värde som är mindre än v[i]
            it->first = v[i];
            it->second = i;
            backTrack[i] = (it-1)->second;
        }
    }

    size_t L;
    for(size_t i = 1; i < last.size(); i++){
        if(last[i].first < inf){
            L = last[i].second;
        }
    }
    
    //Reconstruct the solution
    ans.reserve(L);
    do{
        ans.push_back(L);
        L = backTrack[L];
    }while(L != inf);

    std::reverse(ans.begin(), ans.end());

    return ans;
}