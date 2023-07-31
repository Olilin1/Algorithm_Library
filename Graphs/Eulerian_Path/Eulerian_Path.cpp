/*
    AUTHOR: Oliver Lindgren
*/

#include"Eulerian_Path.hpp"

std::vector<size_t> Eulerian_Path_Undirected(size_t nodes, const std::vector<std::vector<size_t>>& neighbours){
    std::vector<std::unordered_map<size_t, unsigned long long int>> adjacent(nodes);

    std::vector<size_t> path;

    size_t edges = 0;
    size_t startNode = 0;
    size_t uneven = 0;

    std::vector<size_t> degrees(nodes);
    
    for(size_t i = 0; i < nodes; i++){
        for(size_t j : neighbours[i]){
            startNode = i;
            edges++;
            adjacent[i][j]++;
            degrees[i]++;
            degrees[j]++;
        }
    }
    edges /= 2;

    for(size_t i = 0; i < nodes; i++){
        degrees[i] /= 2;

        if(degrees[i] % 2 != 0){
            startNode = i;
            uneven++;
        }
    }

    if(uneven != 0 && uneven != 2) return {};

    std::stack<size_t> myStack;

    myStack.push(startNode);

    while(!myStack.empty()){
        size_t v = myStack.top();
        
        if(degrees[v] == 0){
            path.push_back(v);
            myStack.pop();
        }
        else{
            size_t next = adjacent[v].begin()->first;
            adjacent[v][next]--;
            adjacent[next][v]--;
            degrees[v]--;
            degrees[next]--;
            myStack.push(next);
            if(adjacent[v][next] == 0){
                adjacent[v].erase(next);
                adjacent[next].erase(v);
            }
        }
    }
    if(path.size() != edges + 1) return {};
    return path;
}


std::vector<size_t> Eulerian_Path_Directed(size_t nodes, const std::vector<std::vector<size_t>>& neighbours){
    std::vector<std::unordered_map<size_t, unsigned long long int>> adjacent(nodes);
    std::vector<size_t> path;

    size_t startNode = 0;
    size_t uneven = 0;
    size_t edges = 0;

    std::vector<long long int> degrees(nodes);
    
    for(size_t i = 0; i < nodes; i++){
        for(size_t j : neighbours[i]){
            startNode = i;
            edges++;
            adjacent[i][j]++;
            degrees[i]++;
            degrees[j]--;
        }
    }

    for(size_t i = 0; i < nodes; i++){
        if(degrees[i] != 0){
            if(degrees[i] == 1)
                startNode = i;
            uneven++;
        }
    }

    if(uneven != 0 && uneven != 2) return {};

    std::stack<size_t> myStack;

    myStack.push(startNode);

    while(!myStack.empty()){
        size_t v = myStack.top();

        if(adjacent[v].empty()){
            path.push_back(v);
            myStack.pop();
        }
        else{
            size_t next = adjacent[v].begin()->first;
            adjacent[v][next]--;

            myStack.push(next);
            if(adjacent[v][next] == 0){
                adjacent[v].erase(next);
            }
        }
    }

    if(path.size() != edges+1) return {};
    std::reverse(path.begin(), path.end());
    return path;
}