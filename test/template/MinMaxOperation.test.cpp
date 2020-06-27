/**
 * @file MinMaxOperation.test.cpp
 * @author btk
 * @brief MinMaxOperation.hpp のテスト
 * @version 0.1
 * @date 2019-07-03
 *
 * @copyright Copyright (c) 2019
 *
 */
//! @cond
#define BOOST_TEST_MAIN
//! @endcond
#include "template/MinMaxOperation.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(MinMaxOperation)
BOOST_AUTO_TEST_SUITE(MultiOperation)

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


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
