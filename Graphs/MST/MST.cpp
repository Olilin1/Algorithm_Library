/*
AUTHOR: Oliver Lindgren
*/

#include"MST.hpp"


std::pair<long long int, std::vector<std::pair<size_t, size_t>>> mst(size_t vertices, std::vector<std::pair<long long int, std::pair<size_t, size_t>>> edges){
    long long int cost = 0;
    std::vector<std::pair<size_t,size_t>> included;
    std::sort(edges.begin(), edges.end());
    DisjointSet s(vertices);
    for(auto a : edges) {
        if (!s.query(a.second.first, a.second.second)) {
            s.unionSets(a.second.first, a.second.second);
            included.push_back({a.second.first, a.second.second});
            cost += a.first;
        }
    }

    if(included.size() != vertices-1) return {-1, {}};
    return {cost,included};
}