/*
AUTHOR: Oliver Lindgren
*/


#include<cmath>
#include<vector>

#include"Prime_Numbers\Prime_Sieve\Sieve.hpp"
#include"Arithmetic\Modular-Arithmetic\modular.hpp"

using namespace std;

typedef long long int ll;
typedef unsigned long long int ull;


/*
This whole file is a mess...
why did I name a function f ?
why did I write a third GCD function?
why does half the functions not work correctly unless this global variable primes is initialised correctly?
why does the primes variable have to be initialized outside of any function in this file?

so many questions.
*/

vector<size_t> primes;

bool Miller_test(ull n, ull a, ull d, int s) {
    ull x = powMod(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = modMult(x, x, n);
        if (x == n - 1)
            return false;
    }
    return true;
};

bool is_Probably_Prime(ull n, int k=5) { // returns true if n is probably prime, else returns false.
    if (n == 1 || n == 4)
        return false;
    if (n <= 5) return true;

    int s = 0;
    ull d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (int i = 0; i < k; i++) {
        int a = 2 + rand() % (n - 3);
        if (Miller_test(n, a, d, s))
            return false;
    }
    return true;
}

ll gcd(ll a, ll b){
    a = std::abs(a);
    b = std::abs(b);
    if(a > b){
        std::swap(a,b);
    }

    if (a == 0)
        return b;
    return gcd(b % a, a);
}

inline ull f(ull x, ull c, ull m){
    return (modMult(x, x, m) + c) % m;
}

ull Pollard_Rho(ull n, ull c = 1, ull x0 = 2){
    ll hare = x0;
    ll tortoise = x0;
    ull p = 1;

    
    ull t = 0;
    while(p == 1){
        t++;
        tortoise = f(tortoise, c, n);
        hare = f(hare, c, n);
        hare = f(hare, c, n);

        p = gcd(abs(tortoise-hare), n);
    }

    if(p == n) return Pollard_Rho(n, c+1, x0);
    else return p;
}

//Almost identical to fast_prime except it keeps track of how many times a prime appears
vector<pair<ull,ull>> fast_prime_factors_with_mult(ull n){
    vector<pair<ull,ull>> ans;

    for(auto x : primes){
        if(n % x == 0) ans.push_back({x, 0});
        while(n % x == 0){
            n /= x;
            ans.rbegin()->second++;
        }

        if(x*x > n) break;
    }

    if(n == 1) return ans;

    if(!is_Probably_Prime(n, 10)){
        ull p = Pollard_Rho(n);
        if(p*p == n){
            ans.push_back({p,2});
        }
        else{
            ans.push_back({p, 1});
            ans.push_back({n/p, 1});
        }
    }
    else{
        ans.push_back({n, 1});
    }
    return ans;
}

vector<ull> fast_prime_factors_without_mult(ull n){
    vector<ull> ans;

    for(auto x : primes){
        if(n % x == 0) ans.push_back(x);
        while(n % x == 0) n /= x;

        if(x*x > n) break;
    }

    if(n == 1) return ans;

    if(!is_Probably_Prime(n, 10)){
        ull p = Pollard_Rho(n);

        if(p*p == n){
            ans.push_back(p);
        }
        else{
            ans.push_back(p);
            ans.push_back(n/p);
        }
    }
    else{
        ans.push_back(n);
    }
    return ans;
}

void nested(vector<pair<ull,ull>>& v, const vector<pair<ull,ull>>& org, int depth, vector<ull>& ans){
    if(depth == v.size()){
        ull d = 1;
        for(int i = 0; i < v.size(); i++){
            d *= pow(v[i].first, v[i].second);
        }
        ans.push_back(d);
        return;
    }

    while(v[depth].second >= 0){
        nested(v, org, depth+1, ans);

        if(v[depth].second == 0)break;
        v[depth].second--;
    }
    v[depth].second = org[depth].second;
    return;
}


vector<ull> fast_factors(ull n){
    auto v = fast_prime_factors_with_mult(n);
    auto org = v;
    vector<ull> ans;

    nested(v, org, 0, ans);
    return ans;
}