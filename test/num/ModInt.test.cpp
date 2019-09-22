/**
 * @file ModInt.test.cpp
 * @author btk
 * @brief ModInt.hpp のテスト
 * @todo 未実装
 * @version 0.1
 * @date 2019-06-28
 *
 * @copyright Copyright (c) 2019
 *
 */
//! @cond
#define BOOST_TEST_MAIN
//! @endcond
#define STATIC_MOD 1e9+7;
#include "num/ModInt.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ModIntClass)

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Factorials)
BOOST_AUTO_TEST_CASE(Initialize) {
    BOOST_CHECK_EQUAL(factorial::size, 3123456);
    factorial::build();
    BOOST_CHECK_EQUAL(*(factorial::factorial[5]), 120);
}

BOOST_AUTO_TEST_SUITE_END()
