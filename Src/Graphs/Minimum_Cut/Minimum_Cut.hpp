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

std::vector<size_t> minimum_cut(const size_t nodes, const size_t s, const size_t t, std::vector<std::vector<Edge>> edges){
    long long int flowIncrease;
    long long int total = 0;

    //Add reverse flow edges
    for(size_t node = 0; node < nodes; node++){
        for(size_t i = 0; i < edges[node].size(); i++){
            Edge& e = edges[node][i];
            if (e.reverse == -1){
                e.reverse = edges[e.to].size();
                Edge reverse = {e.to, e.from, 0, 0, i};
                edges[e.to].push_back(reverse);
            }
            else{
                break;
            }
        }
    }

    std::vector<long long int> level(nodes);
    std::vector<size_t> next(2*nodes);
    while (dinic_bfs(s, t, edges, level)) {
        for (size_t i = 0; i < nodes; i++) {
            next[i] = 0;
        }
        do {
            flowIncrease = dinic_dfs(s, t, edges, level, next, (1 << 30));
            total += flowIncrease;

        } while (flowIncrease); //Medans det finns flöde att expandera med, gör det.
    }

    //The nodes to be included in the cut are all nodes still reachable from s
    std::vector<size_t> minCutNodes;
    for (size_t i = 0; i < nodes; i++) {
        if(level[i] != -1) minCutNodes.push_back(i);
    }

    return minCutNodes;
}

#endif