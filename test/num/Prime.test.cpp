/**
 * @file Prime.test.cpp
 * @author btk
 * @brief Prime.hpp のテスト
 */

//! @cond
#define BOOST_TEST_MAIN
//! @endcond
#include "num/Prime.hpp"
#include <boost/test/included/unit_test.hpp>
#include <vector>

BOOST_AUTO_TEST_SUITE(Prime)

BOOST_AUTO_TEST_CASE(Eratosthenes) {
    {
        int in                    = 0;
        std::vector<int> actual   = eratosthenes(in);
        std::vector<int> expected = {};
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
    {
        int in                    = 1;
        std::vector<int> actual   = eratosthenes(in);
        std::vector<int> expected = {};
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
    {
        int in                    = 2;
        std::vector<int> actual   = eratosthenes(in);
        std::vector<int> expected = {2};
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
    {
        int in                    = 20;
        std::vector<int> actual   = eratosthenes(in);
        std::vector<int> expected = {2, 3, 5, 7, 11, 13, 17, 19};
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
}

BOOST_AUTO_TEST_CASE(PrimeFactorization) {
    {
        int64_t in                        = 1;
        std::vector<PrimeFactor> actual   = primeFactorization(in);
        std::vector<PrimeFactor> expected = {};
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
    {
        int64_t in                        = 2;
        std::vector<PrimeFactor> actual   = primeFactorization(in);
        std::vector<PrimeFactor> expected = {PrimeFactor(2, 1)};
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
    {
        int64_t in                        = 1024;
        std::vector<PrimeFactor> actual   = primeFactorization(in);
        std::vector<PrimeFactor> expected = {PrimeFactor(2, 10)};
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
    {
        int64_t in                        = 1024 * 37;
        std::vector<PrimeFactor> actual   = primeFactorization(in);
        std::vector<PrimeFactor> expected = {PrimeFactor(2, 10),
                                             PrimeFactor(37, 1)};
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
    {
        int64_t in                        = 2 * 3 * 5 * 7 * 11 * 13 * 17;
        std::vector<PrimeFactor> actual   = primeFactorization(in);
        std::vector<PrimeFactor> expected = {2, 3, 5, 7, 11, 13, 17};
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
}

BOOST_AUTO_TEST_CASE(PrimeFactorizationWithReservedPrimeList) {
    auto reserved = eratosthenes(20);
    {
        int64_t in                        = 1;
        std::vector<PrimeFactor> actual   = primeFactorization(in);
        std::vector<PrimeFactor> expected = {};
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
    {
        int64_t in                        = 2;
        std::vector<PrimeFactor> actual   = primeFactorization(in, reserved);
        std::vector<PrimeFactor> expected = {PrimeFactor(2, 1)};
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
    {
        int64_t in                        = 1024;
        std::vector<PrimeFactor> actual   = primeFactorization(in, reserved);
        std::vector<PrimeFactor> expected = {PrimeFactor(2, 10)};
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
    {
        int64_t in                        = 1024 * 37;
        std::vector<PrimeFactor> actual   = primeFactorization(in, reserved);
        std::vector<PrimeFactor> expected = {PrimeFactor(2, 10),
                                             PrimeFactor(37, 1)};
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
    {
        int64_t in                        = 2 * 3 * 5 * 7 * 11 * 13 * 17;
        std::vector<PrimeFactor> actual   = primeFactorization(in, reserved);
        std::vector<PrimeFactor> expected = {2, 3, 5, 7, 11, 13, 17};
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
}

BOOST_AUTO_TEST_SUITE_END()