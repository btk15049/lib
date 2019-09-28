/**
 * @file RollingHash.test.cpp
 * @author btk
 * @brief RollingHash.hpp のテスト
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
#include "string/RollingHash.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Init) {
    const std::string target = "ABCDABC";
    RollingHash<>::Table rh(target);
    BOOST_CHECK_EQUAL(rh.substr(0, 3), rh.substr(4, 7));
}