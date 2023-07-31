/*
AUTHOR: Oliver Lindgren
*/

#include "FFT.hpp"

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