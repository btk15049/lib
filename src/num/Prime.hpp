/**
 * @file Prime.hpp
 * @author btk
 * @brief 篩とか素因数分解とか
 */
/*<head>*/
#pragma once
#include <cassert>
#include <cstdint>
#include <vector>
/*</head>*/

/**
 * @brief n 以下の素数をvectorに列挙する
 * @details n 以下の素数はだいたい n / log n 個
 * @param n 入力
 * @return std::vector<int> 素数のリスト
 */
std::vector<int> eratosthenes(const int n) {
    std::vector<bool> isPrime(n + 1);
    for (int i = 0; i <= n; i++) {
        isPrime[i] = true;
    }
    std::vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            for (int j = 2 * i; j <= n; j += i) {
                isPrime[j] = false;
            }
            primes.emplace_back(i);
        }
    }
    return primes;
}


/**
 * @brief 素因数を管理するための構造体
 */
struct PrimeFactor {
    // 素数
    int64_t prime;
    // 素数の個数
    int count;
    // vectorを作るためだけのデフォルトコンストラクタ
    PrimeFactor(){};
    // コンストラクタ
    PrimeFactor(int64_t p, int c = 1) : prime(p), count(c){};
};

/**
 * @brief 素因数分解
 * @details O(\sqrt(n))
 * @param n 素因数分解する数
 * @return std::vector<PrimeFactor> 素数の昇順にソートされた{素数,個数}のリスト
 */
std::vector<PrimeFactor> primeFactorization(int64_t n) {
    std::vector<PrimeFactor> ret;
    for (int i = 2; int64_t(i) * int64_t(i) <= n; i++) {
        if (n % i == 0) {
            int cnt = 0;
            do {
                cnt++;
            } while (n % i == 0);
            ret.emplace_back(int64_t(i), cnt);
        }
    }
    if (n != 1) {
        ret.emplace_back(n);
    }
    return ret;
}


/**
 * @brief 事前に用意した素数のリストを使った素因数分解
 * @details O(sqrt(n)/log(n))
 * @param n 素因数分解する数
 * @param reservedPrimes 素数のリスト
 * @return std::vector<PrimeFactor> 素数の昇順にソートされた{素数,個数}のリスト
 */
std::vector<PrimeFactor>
primeFactorization(int64_t n, const std::vector<int>& reservedPrimes) {
    std::vector<PrimeFactor> ret;
    assert(reservedPrimes.size() > size_t(0));
    assert(int64_t(reservedPrimes.back()) * int64_t(reservedPrimes.back()) < n);
    for (const int p : reservedPrimes) {
        if (int64_t(p) * int64_t(p) > n) break;
        if (n % p == 0) {
            int cnt = 0;
            do {
                cnt++;
            } while (n % p == 0);
            ret.emplace_back(p, cnt);
        }
    }
    if (n != 1) {
        ret.emplace_back(n);
    }
    return ret;
}
