/*
AUTHOR: Oliver Lindgren
*/


#ifndef FFT_HPP
#define FFT_HPP

#define PI 3.14159265359

#include<vector>
#include<complex>

typedef long long int ll;
/*
Takes two polynomials in coefficient list representation, where the coefficients are whole integers, 
multiplies them together using the fast fourier transformtation algorithm
and returns the resulting polynomial also in coefficient list representation.
O(N log(N))
*/
std::vector<ll> Polymul(std::vector<ll> a, std::vector<ll> b);

/*
Takes two polynomials in coefficient list representation, where the coefficients are whole integers, 
multiplies them together using a naive O(N^2) algorithm
and returns the resulting polynomial also in coefficient list representation.
O(N^2)
*/
std::vector<ll> Polymul_Quadratic(std::vector<ll> a, std::vector<ll> b);

/*
Applies the FFT on the vector P and returns the result. N is the size of the vector P. 
Start and skip are used to index the vector and should be left default initialized.
O(N log(N))
*/
std::vector<std::complex<double>> FFT(const std::vector<ll>& P, int n, int start = 0, int skip = 1);

/*
Applies the inverse FFT on the vector P and returns the result. N is the size of the vector P.
Start and skip are used to index the vector and should be left default initialized.
O(N log(N))
*/
std::vector<std::complex<double>> INVERSE_FFT(const std::vector<std::complex<double>>& P, int n, int start = 0, int skip = 1);

#endif