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






























std::vector<ll> Polymul(std::vector<ll> a, std::vector<ll> b){
    int n=1;
    int org = a.size() + b.size() - 1;

    while(n < org) n*=2;

    while(a.size() < n) a.push_back(0);
    while(b.size() < n) b.push_back(0);

    std::vector<std::complex<double>> a_value_rep = FFT(a, n);    
    std::vector<std::complex<double>> b_value_rep = FFT(b, n);   
    std::vector<std::complex<double>> merged;
    std::vector<std::complex<double>> reversed;

    merged.reserve(n);

    for(int i = 0; i < n; i++){
        merged.push_back(a_value_rep[i] * b_value_rep[i]);
    }

    reversed = INVERSE_FFT(merged, n);

    std::vector<ll> ans;
    ans.reserve(org);

    for(int i = 0; i < org; i++){
        ans.push_back(round(reversed[i].real()/(double)n));
    }

    return ans;
}


std::vector<std::complex<double>> FFT(const std::vector<ll>& p, int n, int start, int skip){
    using namespace std::complex_literals;

    if(p.size() == skip){
        return {{(double)p[start], 0.0}};
    } //Ett polynom av grad 0 har alltid värdet av koefficienten. FIIIIIIIX



    std::vector<std::complex<double>> y_even, y_odd;
    y_even = FFT(p, n/2, start, skip*2);
    y_odd = FFT(p, n/2, start+skip, skip*2);

    std::vector<std::complex<double>> y_merged(n);
    for(int i = 0; i < n/2; i++){
        std::complex<double> compute = std::exp((2.0*PI*1i*(double)i)/(double)n) * y_odd[i];
        y_merged[i] = y_even[i] + compute;
        y_merged[i+n/2] = y_even[i] - compute;
    }
    return y_merged;
}


std::vector<std::complex<double>> INVERSE_FFT(const std::vector<std::complex<double>>& p, int n, int start, int skip){
    using namespace std::complex_literals;

    if(p.size() == skip){
        return {p[start]};
    } //Ett polynom av grad 0 har alltid värdet av koefficienten. FIIIIIIIX

    std::vector<std::complex<double>> y_even, y_odd;
    y_even = INVERSE_FFT(p, n/2, start, skip*2);
    y_odd = INVERSE_FFT(p, n/2, start+skip, skip*2);

    std::vector<std::complex<double>> y_merged(n);
    for(int i = 0; i < n/2; i++){
        std::complex<double> compute = std::exp((-2.0*PI*1i*(double)i)/(double)n) * y_odd[i];
        y_merged[i] = y_even[i] + compute;
        y_merged[i+n/2] = y_even[i] - compute;
    }
    return y_merged;
}

std::vector<ll> Polymul_Quadratic(std::vector<ll> a, std::vector<ll> b){
    std::vector<ll> res(a.size() + b.size() - 1);

    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < b.size(); j++){
            res[i+j] += a[i]*b[j];
        }
    }

    return res;
}

#endif