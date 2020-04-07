/*<head>*/
#pragma once
#include <vector>
#include <cstdint>
/*</head>*/

/**
 * @brief n 以下の素数をvectorに列挙する
 * @details n 以下の素数はだいたい n / log n 個
 * @param n 入力
 * @return std::vector<int> 素数のリスト
 */
std::vector<int> Eratosthenes( const int n )
{
    std::vector<bool> isPrime( n + 1 );
    for( int i = 0; i <= n; i++ )
    {
        isPrime[ i ] = true;
    }
    std::vector<int> primes;
    for( int i = 2; i <= n; i++ )
    {
        if( isPrime[ i ] )
        {
            for( int j = 2 * i; j <= n; j += i )
            {
                isPrime[ j ] = false;
            }
            primes.emplace_back( i );
        }
    }
    return primes;
}


struct PrimeFactor{
    int64_t prime;
    int count;
    PrimeFactor(){};
    PrimeFactor(int64_t p) :prime(p), count(1){};
    PrimeFactor(int64_t p, int c) :prime(p), count(c){};
};

std::vector<PrimeFactor> PrimeFactorDecomposition(int64_t n) {

}

std::vector<PrimeFactor> PrimeFactorDecomposition(int64_t n, std::vector<int64_t> reservedPrimes) {

}
