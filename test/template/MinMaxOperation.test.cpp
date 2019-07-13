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
#define BOOST_TEST_MAIN
#include "template/MinMaxOperation.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(MinMaxOperation)
BOOST_AUTO_TEST_SUITE(MultiOperation)

/**
 * @brief multi_minのテスト
 * @details 左端，中央，右端が最小の場合を全て検証
 */
BOOST_AUTO_TEST_CASE(MultiMin) {
    BOOST_CHECK_EQUAL(multi_min(2, 3, 4), 2);
    BOOST_CHECK_EQUAL(multi_min(3, 4, 2), 2);
    BOOST_CHECK_EQUAL(multi_min(4, 2, 3), 2);
}

/**
 * @brief multi_minのテスト
 * @details 左端，中央，右端が最大の場合を全て検証
 */
BOOST_AUTO_TEST_CASE(MultiMax) {
    BOOST_CHECK_EQUAL(multi_max(2, 3, 4), 4);
    BOOST_CHECK_EQUAL(multi_max(3, 4, 2), 4);
    BOOST_CHECK_EQUAL(multi_max(4, 2, 3), 4);
}

/**
 * @brief chminのテスト
 * @details 第一引数より {大きい，同じ，小さい} 場合を全て検証
 */
BOOST_AUTO_TEST_CASE(ChMin) {
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
BOOST_AUTO_TEST_CASE(ChMax) {
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
