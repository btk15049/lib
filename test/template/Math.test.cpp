/**
 * @file Math.test.cpp
 * @author btk
 * @brief Math.hpp のテスト
 */
//! @cond
#define BOOST_TEST_MAIN
//! @endcond
#include "template/Math.hpp"
#include <boost/test/included/unit_test.hpp>

//! @cond
BOOST_AUTO_TEST_SUITE(MathHpp)
//! @endcond

BOOST_AUTO_TEST_CASE(GCDTest) {
    {
        auto actual      = math::gcd(6, 9);
        int64_t expected = 3;
        BOOST_CHECK_EQUAL(actual, expected);
    }
    {
        auto actual      = math::gcd(12, 30, 10);
        int64_t expected = 2;
        BOOST_CHECK_EQUAL(actual, expected);
    }
    {
        auto actual      = math::gcd(1, 0, 0);
        int64_t expected = 1;
        BOOST_CHECK_EQUAL(actual, expected);
    }
    {
        auto actual      = math::gcd(0, 0, 1);
        int64_t expected = 1;
        BOOST_CHECK_EQUAL(actual, expected);
    }
    {
        auto actual      = math::gcd(0, 10 * int64_t(1e9), 15 * int64_t(1e9));
        int64_t expected = 5 * int64_t(1e9);
        BOOST_CHECK_EQUAL(actual, expected);
    }
}

//! @cond
BOOST_AUTO_TEST_SUITE_END();
//! @endcond
