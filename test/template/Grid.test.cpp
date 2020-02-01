/**
 * @file Grid.test.cpp
 * @author btk
 * @brief Grid.hpp のテスト
 * @version 0.1
 * @date 2020-02-01
 *
 * @copyright Copyright (c) 2020
 *
 */
//! @cond
#define BOOST_TEST_MAIN
//! @endcond
#include "template/Grid.hpp"
#include <boost/test/included/unit_test.hpp>
#include <string>
#include <vector>

//! @cond
BOOST_AUTO_TEST_SUITE(GridHpp)
//! @endcond

BOOST_AUTO_TEST_CASE(WrapGridTest) {
    {
        std::vector<std::string> args     = {"abc", "def", "fgu"};
        std::vector<std::string> actual   = wrapGrid(args, '#');
        std::vector<std::string> expected = {"#####", "#abc#", "#def#", "#fgu#",
                                             "#####"};
        BOOST_CHECK(expected == actual);
    }
    {
        std::vector<std::vector<int>> args     = {{1}};
        std::vector<std::vector<int>> actual   = wrapGrid(args, 0);
        std::vector<std::vector<int>> expected = {
            {0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
        BOOST_CHECK(expected == actual);
    }
}

//! @cond
BOOST_AUTO_TEST_SUITE_END();
//! @endcond
