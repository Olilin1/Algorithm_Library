/*
AUTHOR: Oliver Lindgren
*/

#ifndef MINIMIAL_SPANNING_TREE_HPP
#define MINIMIAL_SPANNING_TREE_HPP

#include<vector>
#include<utility>
#include<algorithm>
#include<stddef.h>
#include"Data_Structures\Disjoint_Set\DisjointSet.hpp"

/*
Function used to calculate the minimum spanning tree of a graph.

Takes as input the number of vertices and a vector of edges.

An edge is represented as a pair of 1. the edge weight w, and 2. a pair containing nodes u & v. This means there is an edge between u & v with weight w

Returns a pair containing 1. the size of the tree, and 2. a vector containing pairs what nodes there are edges between.

If there is no minimum spanning tree then the size is returned as -1 and the vector is empty.

Time complexity: O(m * log(n)) where n is the number of nodes and m is the number of edges in the graph. 
*/
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

#endif