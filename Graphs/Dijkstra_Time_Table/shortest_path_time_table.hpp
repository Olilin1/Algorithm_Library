/*
AUTHOR: Oliver Lindgren
*/

#ifndef SHORTEST_PATH_TIME_TABLE_DIJKSTRA_HPP
#define SHORTEST_PATH_TIME_TABLE_DIJKSTRA_HPP
#include<vector>
#include<utility>
#include<queue>
#include<limits>
#include<iostream>
#include<stddef.h>


struct Edge
{
    size_t destination;
    unsigned long long int travelTime;
    unsigned long long int firstDeparture;
    unsigned long long int repeatDepartures;
};


/*
My implementation of the dijkstra algorithm but were certain edges may only be used on certain times.
Returns a vector of pairs where the second item of each element i is the distance to the node i and the first item is the node you go to i from.
If there is no way to reach a node i then v[i].first and v[i].second is set to the max size of size_t and unsigned long long int respectively.
The start node's parent is set to the maximum value of size_t
Takes as input the graph represented in adjacency list form and the node we start from.
Time complexity: O(m * log(n)) where n is the amount of nodes in the graph and m is the amount of edges.
*/
std::vector<std::pair<size_t, unsigned long long int>> dijkstra_shortest_path_time_table(const std::vector<std::vector<Edge>>& adjaceny_list, size_t startNode);

#endif