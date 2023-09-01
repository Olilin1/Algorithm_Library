/*
Author: Oliver Lindgren
*/

#ifndef PRIME_SIEVE_HPP
#define PRIME_SIEVE_HPP

#include<vector>
#include<stddef.h>
#include<iostream>

/*		
    Class to compute all primes up to a number N. it provides the following functions:		
            
    Prime_Sieve(N) - the constructor takes a number N as an argument and computes which numbers up to N that are prime.	
    get_Number_Of_Primes() - returns the number of primes that are smaller than or equal to N.		
    get_Primes() returns a sorted vector of all numbers less than N that are prime.
    is_Prime(x) - returns true if x is prime. Returns false otherwise.		
*/

class Prime_Sieve{
    std::vector<bool> is_composite;
    std::vector<size_t> primes;

    public:
    const std::vector<size_t>& get_Primes();
    Prime_Sieve(size_t n);
    size_t get_Number_Of_Primes();
    bool is_Prime(size_t i);
};




































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

#endif