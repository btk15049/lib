/**
 * @file STLExtension.cpp
 * @author btk
 * @brief STLExtension.cppのテスト
 */

//! @cond
#define BOOST_TEST_MAIN
//! @endcond
#include "template/STLExtension.hpp"
#include <boost/test/included/unit_test.hpp>
#include <cstdint>
#include <functional>
#include <vector>

//! @cond
BOOST_AUTO_TEST_SUITE(STLExtensionHpp)
//! @endcond


BOOST_AUTO_TEST_CASE(SortTest) {
    {
        std::vector<int> args     = {2, 3, 1, 4};
        std::vector<int> expected = {1, 2, 3, 4};
        auto& actual              = ext::sort(args);
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      args.begin(), args.end());
    }
    {
        std::vector<int> args     = {2, 3, 1, 4};
        std::vector<int> expected = {4, 3, 2, 1};
        auto& actual              = ext::sort(args, std::greater<int>());
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      args.begin(), args.end());
    }
}

BOOST_AUTO_TEST_CASE(ReverseTest) {
    {
        std::vector<int> args     = {2, 3, 1, 4};
        std::vector<int> expected = {4, 1, 3, 2};
        auto& actual              = ext::reverse(args);
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      args.begin(), args.end());
    }
    {
        std::vector<int> args     = {2, 3, 1, 4};
        std::vector<int> expected = {4, 3, 2, 1};
        auto& actual              = ext::reverse(ext::sort(args));
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      args.begin(), args.end());
    }
}

BOOST_AUTO_TEST_CASE(AccumulateTest) {
    {
        std::vector<int> args = {1, 10, 100, 1000};
        int expected          = 1111;
        auto actual           = ext::accumulate(args);
        BOOST_CHECK_EQUAL(actual, expected);
    }
    {
        std::vector<int> args = {1, 10, 100, 1000};
        int expected          = 1111;
        auto actual           = ext::accumulate(args, 0);
        BOOST_CHECK_EQUAL(actual, expected);
    }
    {
        std::vector<int64_t> args(100, 1e9);
        int64_t expected = 1e11;
        auto actual      = ext::accumulate(args);
        BOOST_CHECK_EQUAL(actual, expected);
    }
    {
        std::vector<int> args(1000, 1e9);
        int64_t expected = 1e12;
        auto actual      = ext::accumulate(args, int64_t(0));
        BOOST_CHECK_EQUAL(actual, expected);
    }
}

BOOST_AUTO_TEST_CASE(CountTest) {
    {
        std::vector<int> args = {1, 2, 3, 1};
        int expected          = 2;
        auto actual           = ext::count(args, 1);
        BOOST_CHECK_EQUAL(actual, expected);
    }
    {
        std::vector<int> args = {};
        int expected          = 0;
        auto actual           = ext::count(args, 1);
        BOOST_CHECK_EQUAL(actual, expected);
    }
}


//! @cond
BOOST_AUTO_TEST_SUITE_END();
//! @endcond
