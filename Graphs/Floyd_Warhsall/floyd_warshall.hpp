/*
AUTHOR: Oliver Lindgren
*/

#ifndef FLOYD_WARSHALL_HPP
#define FLOYD_WARSHALL_HPP
#include<vector>
#include<algorithm>
#include<limits>
#include<iostream>


/*
My implementation of the Floyd_Warshall algorithm.
Takes as input the adjacency matrix m of the graph. 
If there is no edge between two nodes from u to v then m[u][v] must be set to the maximum value of a long long int divided by 2.
For every node i m[i][i] must be set to 0.
For all nodes u, v with an edge between them from u to w with weight w, m[u][v] must be set to w.
If n is the amount of nodes in the graph then it returns a n*n matrix m where m[u][v] is the distance from u to v.
If it is not possible to reach v from u then m[u][v] is set to the maximum value of a long long int divided by 2
If it is possible to reach v from u taking a path with arbitrarily small value then m[u][v] is set to -(the maximum value of a long long int divided by 2)
Time complexity: O(n^3)
*/

std::vector<std::vector<long long int>> Floyd_Warshall(std::vector<std::vector<long long int>> distance_matrix){
    const long long int inf = std::numeric_limits<long long int>::max() / 2;
    size_t n = distance_matrix.size();

    for(size_t k = 0; k < n; k++){
        for(size_t i = 0; i < n; i++){
            for(size_t j = 0; j < n; j++){
                if(distance_matrix[i][k] == inf || distance_matrix[k][j] == inf) continue;
                distance_matrix[i][j] = std::min(distance_matrix[i][j], distance_matrix[i][k] + distance_matrix[k][j]);
            }
        }
    }


    for(size_t i = 0; i < n; i++){
        for(size_t j = 0; j < n; j++){
            for(size_t k = 0; k < n; k++){
                if( distance_matrix[i][k] != inf &&
                    distance_matrix[k][j] != inf &&
                    distance_matrix[k][k] < 0){ 
                        distance_matrix[i][j] = -inf;
                }
            }
        }
    }
    
    return distance_matrix;
}

#endif