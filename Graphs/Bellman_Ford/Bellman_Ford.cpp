/*
AUTHOR: Oliver Lindgren
*/

#include"Bellman_Ford.hpp"

std::vector<std::pair<long long int, size_t>> Bellman_Ford(const size_t nodes, const size_t startNode, const std::vector<Edge>& edges){
    std::vector<std::pair<long long int, size_t>> dist_pred(nodes, {inf, inf});

    dist_pred[startNode].first = 0;

    //Construct solution
    for(size_t i = 0; i < nodes-1; i++){
        bool change = false;
        for(Edge e : edges){
            if(dist_pred[e.from].first == inf) continue; //Avoid overflow error
            if(dist_pred[e.from].first + e.weight < dist_pred[e.to].first){
                dist_pred[e.to].first = dist_pred[e.from].first + e.weight;
                dist_pred[e.to].second = e.from;
                change = true;
            }
        }
        if(!change) return dist_pred;
    }


    //Now do the same thing again. Every single node that still has a shorter path to it is part of a negative cycle.
    for(size_t i = 0; i < nodes-1; i++){
        bool change = false;
        for(Edge e : edges){
            if(dist_pred[e.from].first == inf) continue; //Avoid overflow error
            if((dist_pred[e.from].first + e.weight < dist_pred[e.to].first) || (dist_pred[e.from].first == negInf && dist_pred[e.to].first != negInf)){
                dist_pred[e.to].first = negInf;
                dist_pred[e.to].second = e.from;
                change = true;
            }
        }
        if(!change) return dist_pred;
    }

    return dist_pred;
}