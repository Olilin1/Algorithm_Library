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




#endif