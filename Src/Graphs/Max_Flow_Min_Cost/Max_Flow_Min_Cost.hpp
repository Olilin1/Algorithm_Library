/*
AUTHOR: Oliver Lindgren
*/

#ifndef MAXIMUM_FLOW_MINIMUM_COST_HPP
#define MAXIMUM_FLOW_MINIMUM_COST_HPP

#include<vector>
#include<stddef.h>
#include<queue>
#include<optional>
#include<iostream>

struct Edge {
    size_t from; //Vilken nod går denna kanten från?
    size_t to; //Vilken nod går denna kanten till?
    long long int capacity; //Hur mycket capacitet finns kvar?
    long long int cost;
    long long int flow = 0; //Hur mycket flöde är det just nu?
    long long int reverse = -1; //Var finns reverse-flow kanten?
};

std::vector<std::pair<long long int, Edge*>> Bellman_Ford_Flow(const size_t nodes, const size_t startNode, std::vector<Edge*>& edges);

const long long int inf = std::numeric_limits<long long int>::max();
const long long int negInf = std::numeric_limits<long long int>::min();

std::pair<long long int, long long int> max_flow_min_cost(const size_t nodes, const size_t source, const size_t sink, std::vector<Edge> edges){
    long long int flow = 0;
    long long int cost = 0;
    size_t n = edges.size();
    //Add reverse flow edges
    for(size_t i = 0; i < n; i++){
        Edge& e = edges[i];
        e.reverse = edges.size();
        Edge reverse = {e.to, e.from, 0, -e.cost, 0, i};
        edges.push_back(reverse);
    }
    

    while(true){
        std::vector<Edge*> v;
        for(Edge& e : edges){
            if(e.capacity - e.flow > 0) v.push_back(&e);
        }
        auto x = Bellman_Ford_Flow(nodes, source, v);

        if(x[sink].first == inf) return {flow, cost};


        size_t node = sink;
        long long int min_cap = inf;
        long long int path_cost = 0;
        while(x[node].second != nullptr){
            const Edge& e = *x[node].second;
            min_cap = std::min(min_cap, e.capacity - e.flow);
            node = e.from;
            path_cost += e.cost;
        }

        cost += path_cost * min_cap;
        flow += min_cap;

        node = sink;
        while(x[node].second != nullptr){
            Edge& e = *x[node].second;
            e.flow += min_cap;
            edges[e.reverse].flow -= min_cap;
            node = e.from;
        }
    }
}






std::vector<std::pair<long long int, Edge*>> Bellman_Ford_Flow(const size_t nodes, const size_t startNode, std::vector<Edge*>& edges){
    std::vector<std::pair<long long int, Edge*>> dist_pred(nodes, {inf, nullptr});

    dist_pred[startNode].first = 0;

    //Construct solution
    for(size_t i = 0; i < nodes-1; i++){
        bool change = false;
        for(Edge* e : edges){
            if(e->flow >= e->capacity) continue;
            if(dist_pred[e->from].first == inf) continue; //Avoid overflow error
            if(dist_pred[e->from].first + e->cost < dist_pred[e->to].first){
                dist_pred[e->to].first = dist_pred[e->from].first + e->cost;
                dist_pred[e->to].second = e;
                change = true;
            }
        }
        if(!change) return dist_pred;
    }

    return dist_pred;
}
#endif