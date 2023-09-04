/*
Author: Oliver Lindgren
*/

#include<utility>
#include<cstdlib>
#include<stddef.h>


typedef long long int ll;
typedef unsigned long long int ull;
typedef __uint128_t u128;
typedef __int128_t i128;

//Returnerar a mod m. Fungerar för både negativa och positiva tal a.
inline ll mod(const i128 a, const i128 m){
    return (m+(a%m))%m;
}

//Returnerar (a*b) mod m. Där a,b,m får plats i ett 64-bitars tal
inline ll modMult(const i128 a, const i128 b, const i128 m){
    return mod(a * b, m);
}

ull powMod(ull base, ull exp, ull m) {
    ull result = 1;
    base %= m;
    while (exp) {
        if (exp % 2 == 1)
            result = (u128)result * base % m;
        base = (u128)base * base % m;
        exp /= 2;
    }
    return result;
}

//Returnerar (a+b) mod m. Där a,b,m får plats i ett 64-bitars tal
inline ll modAdd(const i128 a, const i128 b, const i128 m){
    return mod(a + b, m);
}

//Returnerar (a-b) mod m. Där a,b,m får plats i ett 64-bitars tal
inline ll modSub(const i128 a, const i128 b, const i128 m){
    return mod(a - b, m);
}

//Returnerar största gemensamma nämnaren till a och b
i128 gcd(i128 a, i128 b, i128& x0, i128& y0){
    a = std::abs(a);
    b = std::abs(b);
    if(a > b){
        std::swap(a,b);
    }

    if (a == 0){
        x0 = 0;
        y0 = 1;
        return b;
    }
    i128 x1, y1, d;
    d = gcd(b % a, a, x1, y1);

    x0 = y1 - (b/a) * x1;
    y0 = x1;

    return d;
}

//Returnerar inversen till b i Z_m
i128 modInverse(const i128 b, const i128 m){
    i128 x, y, d;
    d = gcd(b, m, x, y);

    if(d != 1) return -1;

    return mod(x, m);
}

//Returnerar a * b^(-1) i Z_m
ll modDiv(const i128 a, const i128 b, const i128 m){
    i128 inverse = modInverse(b, m);
    if(inverse != -1){
        return modMult(a, inverse, m);
    }
    else{
        return -1;
    }
}
