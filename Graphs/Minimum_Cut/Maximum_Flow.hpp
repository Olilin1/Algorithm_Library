/*
AUTHOR: Oliver Lindgren
*/

#ifndef MAXIMUM_FLOW_HPP
#define MAXIMUM_FLOW_HPP

#include<vector>
#include<stddef.h>
#include<queue>
#include<optional>


struct Edge {
    size_t from; //Vilken nod går denna kanten från?
    size_t to; //Vilken nod går denna kanten till?
    long long int capacity; //Hur mycket capacitet finns kvar?
    long long int flow = 0; //Hur mycket flöde är det just nu?
    long long int reverse = -1; //Var finns reverse-flow kanten?
};


//Beräkna nivån för varje nod. D.v.s. hur långt ifrån källan den ligger. Om en nod inte kan nås från källan då får den värdet -1
bool dinic_bfs(const size_t source, const size_t sink, const std::vector<std::vector<Edge>>& edges, std::vector<long long int>& level);

//Hitta vägar som expanderar flödet med en DFS.
long long int dinic_dfs(const size_t at, const size_t sink, std::vector<std::vector<Edge>>& edges, const std::vector<long long int>& level, std::vector<size_t>& next, long long int mini);

#endif