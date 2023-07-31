/*
    AUTHOR: Oliver Lindgren
*/

#ifndef EULERIAN_PATH
#define EULERIAN_PATH

#include<vector>
#include<set>
#include<unordered_set>
#include<stddef.h>
#include<unordered_map>
#include<algorithm>
#include<stack>
#include<iostream>

/*
Calculates the Eulerian path in an udirected graph. Takes as input the number of nodes, as well as the edges of the graph in adjaceny list form.
Returns a vector of nodes, indicating the order to visit the nodes in.
If no Eulerian path exists then the empty vector is returned.
Time complexity: O(m) where m is the number of edges in the graph
*/
std::vector<size_t> Eulerian_Path_Undirected(size_t nodes, const std::vector<std::vector<size_t>>& neighbours);

/*
Calculates the Eulerian path in a directed graph. Takes as input the number of nodes, as well as the edges of the graph in adjaceny list form.
Returns a vector of nodes, indicating the order to visit the nodes in.
If no Eulerian path exists then the empty vector is returned.
Time complexity: O(m) where m is the number of edges in the graph
*/
std::vector<size_t> Eulerian_Path_Directed(size_t nodes, const std::vector<std::vector<size_t>>& neighbours);

#endif