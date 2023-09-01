/*
AUTHOR: Oliver Lindgren
*/

#ifndef MINIMUM_CUT
#define MINIMUM_CUT

#include "Graphs\Maximum_Flow\Maximum_Flow.hpp"

/*
My implementation of using dinitz algorithm to calculate the minimum cut of a graph.
Takes as input the number of nodes in the graph, the vertice s that should be in the cut, the vertice v which must not be in the cut. And the edges of the graph as adjacency lists
Returns a vector containing all the nodes that are included in the cut.
Time complexity: O(m*n^2) where n is the number of nodes in the graph, and m is the number of edges.
*/
std::vector<size_t> minimum_cut(const size_t nodes, const size_t s, const size_t t, std::vector<std::vector<Edge>> edges);

#endif