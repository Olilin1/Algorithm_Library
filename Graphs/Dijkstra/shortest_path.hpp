/*
AUTHOR: Oliver Lindgren
*/

#ifndef SHORTEST_PATH_DIJKSTRA_HPP
#define SHORTEST_PATH_DIJKSTRA_HPP
#include<vector>
#include<utility>
#include<queue>
#include<limits>
#include<stddef.h>


/*
My implementation of the dijkstra algorithm.
Returns a vector of pairs where the second item of each element i is the distance to the node i and the first item is the node you go to i from.
If there is no way to reach a node i then v[i].first and v[i].second is set to the max value of size_t and unsigned long long int respectively.
The start node's parent is set to the maximum value of size_t
Takes as input the graph represented in adjacency list form and the node we start from.
Time complexity: O(m * log(n)) where n is the amount of nodes in the graph and m is the amount of edges.
*/

std::vector<std::pair<size_t, unsigned long long int>> dijkstra_shortest_path(const std::vector<std::vector<std::pair<size_t,unsigned long long int>>>& adjaceny_list, size_t startNode);

#endif