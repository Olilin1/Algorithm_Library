/*
AUTHOR: Oliver Lindgren
*/

#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP
#include<vector>
#include<utility>
#include<limits>
#include<stddef.h>

struct Edge{
    size_t from, to;
    long long int weight;
};

const long long int inf = std::numeric_limits<long long int>::max();
const long long int negInf = std::numeric_limits<long long int>::min();


/*
My implementation of the Bellman-Ford algorithm. Calculates the distance from startNode to all other nodes in the graph.
Returns a vector of pairs where the first item of each element i is the distance to the node i and the second item is the node you go to i from.
If there is no way to reach a node i then v[i].first is set to inf.
If node i is part of a negative cycle then v[i].first is set to negInf.
The start node's parent is set to inf unless it is part of a negative cycle.
Takes as input the amount of nodes in the graph, which node to compute the distance from, and a vector contaning all Edges in the graph.
Time complexity: O(n*m) where n is the amount of nodes in the graph and m is the amount of edges.
*/
std::vector<std::pair<long long int, size_t>> Bellman_Ford(const size_t nodes, const size_t startNode, const std::vector<Edge>& edges);


#endif