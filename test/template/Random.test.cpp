/**
 * @file Random.test.cpp
 * @author btk
 * @brief Random.hpp のテスト
 * @version 0.1
 * @date 2019-07-07
 *
 * @copyright Copyright (c) 2019
 *
 */
//! @cond
#define BOOST_TEST_MAIN
//! @endcond
#include "template/Random.hpp"
#include <boost/test/included/unit_test.hpp>
#include <set>
#include <vector>

//! @cond
BOOST_AUTO_TEST_SUITE(RandomClass)

BOOST_AUTO_TEST_SUITE(XorShift32Class)
//! @endcond

/**
 * @brief XorShift32::next_int の テスト
 * @details
 * テンプレート引数なしの状態で[0,2^31)の乱数になるかどうかチェック
 */
BOOST_AUTO_TEST_CASE(NoParamStress) {
    XorShift32 r;
    for (int i = 0; i < 1000; i++) {
        long long v = r.next_int();
        BOOST_CHECK_LT(v, 1ll << 31);
        BOOST_CHECK_GE(v, 0ll);
        BOOST_CHECK_NE(v, pid);
    }
}

/**
 * @brief XorShift32::next_int の テスト
 * @details
 * テンプレート引数を指定した状態で[-2^b,2^b)の乱数になるかどうかチェック
 * b = 3 なので，[0,8)の値になる
 */
BOOST_AUTO_TEST_CASE(ParamStress) {
    XorShift32 r;
    std::set<long long> actual;
    for (int i = 0; i < 1000; i++) {
        long long v = r.next_int<3>();
        actual.insert(v);
        BOOST_CHECK_LT(v, 1ll << 3);
        BOOST_CHECK_GE(v, 0ll);
        BOOST_CHECK_NE(v, pid);
    }
    std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6, 7};
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(actual), std::end(actual),
                                  std::begin(expected), std::end(expected));
}

/**
 * @brief XorShift32::next_signed の テスト
 * @details
 * テンプレート引数を指定した状態で[-2^b,2^b)の乱数になるかどうかチェック
 * b = 2 なので，[-4,3)の値になる
 */
BOOST_AUTO_TEST_CASE(ParamSignedStress) {
    XorShift32 r;
    std::set<long long> actual;
    for (int i = 0; i < 1000; i++) {
        long long v = r.next_signed<2>();
        actual.insert(v);
        BOOST_CHECK_LT(v, 1ll << 2);
        BOOST_CHECK_GE(v, -(1ll << 2));
        BOOST_CHECK_NE(v, pid);
    }
    std::vector<int> expected = {-4, -3, -2, -1, 0, 1, 2, 3};
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(actual), std::end(actual),
                                  std::begin(expected), std::end(expected));
}

//! @cond
BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();
//! @endcond
