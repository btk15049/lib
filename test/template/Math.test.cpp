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

/**
 * @brief minOfのテスト
 * @details 左端，中央，右端が最小の場合を全て検証
 */
BOOST_AUTO_TEST_CASE(MultiMinTest) {
    BOOST_CHECK_EQUAL(minOf(2, 3, 4), 2);
    BOOST_CHECK_EQUAL(minOf(3, 4, 2), 2);
    BOOST_CHECK_EQUAL(minOf(4, 2, 3), 2);
    int x = 3, y = 2, z = 4;
    BOOST_CHECK_EQUAL(minOf(x, y, z), 2);
}

/**
 * @brief minOfのテスト
 * @details 左端，中央，右端が最大の場合を全て検証
 */
BOOST_AUTO_TEST_CASE(MultiMaxTest) {
    BOOST_CHECK_EQUAL(maxOf(2, 3, 4), 4);
    BOOST_CHECK_EQUAL(maxOf(3, 4, 2), 4);
    BOOST_CHECK_EQUAL(maxOf(4, 2, 3), 4);
    int x = 3, y = 2, z = 4;
    BOOST_CHECK_EQUAL(maxOf(x, y, z), 4);
}

/**
 * @brief chminのテスト
 * @details 第一引数より {大きい，同じ，小さい} 場合を全て検証
 */
BOOST_AUTO_TEST_CASE(ChangeMinTest) {
    int x;
    x = 10;
    BOOST_CHECK_EQUAL(chmin(x, 3, 4), true);
    BOOST_CHECK_EQUAL(x, 3);

    BOOST_CHECK_EQUAL(chmin(x, 7, 4), false);
    BOOST_CHECK_EQUAL(x, 3);

    BOOST_CHECK_EQUAL(chmin(x, 3), false);
    BOOST_CHECK_EQUAL(x, 3);
}

/**
 * @brief chmaxのテスト
 * @details 第一引数より {大きい，同じ，小さい} 場合を全て検証
 */
BOOST_AUTO_TEST_CASE(ChangeMaxTest) {
    int x;
    x = 1;
    BOOST_CHECK_EQUAL(chmax(x, 3, 4), true);
    BOOST_CHECK_EQUAL(x, 4);

    BOOST_CHECK_EQUAL(chmax(x, 2, 3), false);
    BOOST_CHECK_EQUAL(x, 4);

    BOOST_CHECK_EQUAL(chmax(x, 4), false);
    BOOST_CHECK_EQUAL(x, 4);
}


//! @cond
BOOST_AUTO_TEST_SUITE_END();
//! @endcond
