/**
 * @file Strings.test.cpp
 * @author btk
 * @brief Strings.hpp のテスト
 * @version 0.1
 * @date 2020-01-30
 *
 * @copyright Copyright (c) 2020
 *
 */
//! @cond
#define BOOST_TEST_MAIN
//! @endcond
#include "template/Strings.hpp"
#include <boost/test/included/unit_test.hpp>
#include <vector>

//! @cond
BOOST_AUTO_TEST_SUITE(StringsHpp)
//! @endcond

BOOST_AUTO_TEST_CASE(JoinTest) {
    {
        std::vector<int> args = {1, 23, 456, 789};
        std::string actual    = join(args, '-');
        std::string expected  = "1-23-456-789";
        BOOST_CHECK_EQUAL(expected, actual);
    }
    {
        std::vector<int> args = {1, 23, 456, 789};
        std::string actual    = join(args, "");
        std::string expected  = "123456789";
        BOOST_CHECK_EQUAL(expected, actual);
    }
    {
        std::vector<std::string> args = {"a", "b"};
        std::string actual            = join(args, ' ');
        std::string expected          = "a b";
        BOOST_CHECK_EQUAL(expected, actual);
    }
    {
        std::tuple<std::string, int> args("a", 1);
        std::string actual   = join(args, ' ');
        std::string expected = "a 1";
        BOOST_CHECK_EQUAL(expected, actual);
    }
    {
        std::string actual   = join(std::make_tuple("a", 1, 1.5), ' ');
        std::string expected = "a 1 1.5";
        BOOST_CHECK_EQUAL(expected, actual);
    }
}

//! @cond
BOOST_AUTO_TEST_SUITE_END();
//! @endcond
