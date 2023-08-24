#ifndef CHINESE_REMAINDER_HPP
#define CHINESE_REMAINDER_HPP
#include<vector>
#include<utility>
#include"modular.hpp"

/*
Function to solve a system of congruencies of the form

x = a1 mod b1
x = a2 mod b2
.
.
.
x = an mod bn


Takes as argument a vector of pairs, where the i:th pair corresponds to (ai, bi)

b1-bn do not have to be co-prime //ACTUALLY THEY DO, BUT THIS WILL BE FIXED IN THE FUTURE
If you know b1-bn are co_prime then setting the flag co_prime to true may improve performance

Returns -1 if there is no solution
*/

long long int Solve_System_Of_Congruencies(std::vector<std::pair<long long int, long long int>> equations, bool co_prime = false){
    
    if(co_prime) goto start_solving;



    start_solving:

    long long int lcm = 1;
    for(auto& pair : equations){
        lcm *= pair.second;
    }

    long long int ans = 0;

    for(auto& pair : equations){
        long long int Mi = lcm/pair.second; 
        long long int xi = Mi % pair.second;
        long long int bi = modInverse(xi, pair.second);
        long long int yi = (bi * Mi) % lcm;
        ans = modAdd(ans, modMult(pair.first, yi, lcm), lcm);
    }

    return ans;
}

#endif