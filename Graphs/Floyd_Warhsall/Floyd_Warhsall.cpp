/*
AUTHOR: Oliver Lindgren
*/

#include"floyd_warshall.hpp"

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