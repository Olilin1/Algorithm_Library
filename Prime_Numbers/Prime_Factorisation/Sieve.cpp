/*
Author: Oliver Lindgren
*/

#include "Sieve.hpp"

Prime_Sieve::Prime_Sieve(size_t n) : is_composite(n+1){
    n++;
    is_composite[0] = true;             //0 is not a composite number, however, it is not prime either.
    if(n > 1) is_composite[1] = true;   //The same applies to the number 1.
    if(n > 2) primes.push_back(2);


    size_t x = 4;
    while(x < n){
        is_composite[x] = true;
        x+=2;
    }

    
    for(size_t i = 3; i < n; i+=2){
        if(is_composite[i]) continue;
        
        primes.push_back(i);

        size_t mult = i*i;
        size_t add = 2*i;
        while(mult < n){
            is_composite[mult] = true;
            mult += add;
        }
        
    }

}

bool Prime_Sieve::is_Prime(size_t i){
    return !is_composite[i]; 
}

size_t Prime_Sieve::get_Number_Of_Primes(){
    return primes.size();
}

const std::vector<size_t>& Prime_Sieve::get_Primes(){
    return primes;
}