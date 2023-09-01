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

typedef unsigned long long int ull;
#define node first
#define parent first
#define distance second
#define weight second

std::vector<std::pair<size_t, unsigned long long int>> dijkstra_shortest_path_time_table(const std::vector<std::vector<Edge>>& adjaceny_list, size_t startNode){
    struct Compare{
        bool operator() (std::pair<size_t, ull> a, std::pair<size_t, ull> b){
            return a.distance > b.distance;
        }
    };

    std::vector<std::pair<size_t, ull>> parent_dist_pair(adjaceny_list.size(), {std::numeric_limits<size_t>::max(), std::numeric_limits<ull>::max()});
    std::priority_queue<std::pair<size_t, ull>, std::vector<std::pair<size_t, ull>>, Compare> pq;
    
    pq.push({startNode, 0});
    parent_dist_pair[startNode].distance = 0;

    while(!pq.empty()){
        std::pair<size_t, ull> p = pq.top();
        pq.pop();

        if(p.distance != parent_dist_pair[p.node].distance)
            continue;

        for(auto edge : adjaceny_list[p.node]){
            if(edge.repeatDepartures == 0 && p.distance > edge.firstDeparture) continue;
            long long int totalTime = (p.distance > edge.firstDeparture ? p.distance + edge.travelTime + (edge.firstDeparture + edge.repeatDepartures - (p.distance % edge.repeatDepartures))%edge.repeatDepartures : edge.firstDeparture + edge.travelTime);

            if(parent_dist_pair[edge.destination].distance > totalTime) {
                pq.push({edge.destination, totalTime});
                parent_dist_pair[edge.destination].distance = totalTime;
                parent_dist_pair[edge.destination].parent = p.node;
            }
        }
    }

    return parent_dist_pair;
}

#endif