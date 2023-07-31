/*
AUTHOR: Oliver Lindgren
*/

#include"Maximum_Flow.hpp"

bool dinic_bfs(const size_t source, const size_t sink, const std::vector<std::vector<Edge>>& edges, std::vector<long long int>& level){
    for (size_t i = 0; i < level.size(); i++) {
        level[i] = -1;
    }
    
    level[source] = 0;

    std::queue<size_t> q;
    q.push(source);
    size_t at;
    while (!q.empty()) {
        at = q.front();
        q.pop();

        for (size_t i = 0; i < edges[at].size(); i++) {
            if (level[edges[at][i].to] < 0 && edges[at][i].flow < edges[at][i].capacity) {
                level[edges[at][i].to] = level[at] + 1;
                q.push(edges[at][i].to);
            }
        }
    }

    return level[sink] > 0; //Om level[sink] = -1 då finns det ingen väg från källan till sänkan och det finns inget sätt att skicka mer flöde.
}

long long int dinic_dfs(const size_t at, const size_t sink, std::vector<std::vector<Edge>>& edges, const std::vector<long long int>& level, std::vector<size_t>& next, long long int mini){
    if (at == sink) return mini;

    //Next sparas mellan olika anrop av dfs. D.v.s vi börjar där vi vet att det kan finnas utrymme att expandera.
    for (; next[at] < edges[at].size(); next[at]++) {
        Edge& e = edges[at][next[at]];

        //Om noden vi tittar på har en högre level och kanten har kapacitet.
        if (level[e.to] == level[at] + 1 && e.flow < e.capacity) {

            //T1 är den minsta kapaciteten hos alla kanter som går till sänkan. D.v.s. maximala möjliga utvidgninen.
            long long int t1 = dinic_dfs(e.to, sink, edges, level, next, std::min(mini, e.capacity - e.flow));
            if (t1) {
                e.flow += t1;
                edges[e.to][e.reverse].flow -= t1;
                return t1;
            }
        }
    }
    return 0;
}

std::pair<long long int, std::vector<Edge>> dinic_max_flow(const size_t nodes, const size_t source, const size_t sink, std::vector<std::vector<Edge>> edges){
    long long int flowIncrease;
    long long int total = 0;
    std::vector<long long int> level(nodes);
    std::vector<size_t> next(2*nodes);
    while (dinic_bfs(source, sink, edges, level)) {
        for (int i = 0; i < nodes; i++) {
            next[i] = 0;
        }
        do {
            flowIncrease = dinic_dfs(source, sink, edges, level, next, (1 << 30));
            total += flowIncrease;

        } while (flowIncrease); //Medans det finns flöde att expandera med, gör det.
    }

    std::vector<Edge> flowEdges;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            if (edges[i][j].flow > 0) flowEdges.push_back(edges[i][j]);
        }
    }

    return {total, flowEdges};
}