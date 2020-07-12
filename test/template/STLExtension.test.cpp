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

BOOST_AUTO_TEST_CASE(IotaTest) {
    {
        std::vector<int> expected = {0, 1, 2, 3};
        auto actual               = ext::iota(4);
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
    {
        std::vector<int> expected = {1, 2, 3, 4, 5};
        auto actual               = ext::iota(5, 1);
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
    {
        std::vector<int> expected = {2, 5, 8, 11};
        auto actual               = ext::iota(4, 2, 3);
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
    {
        std::vector<int> expected = {1, -1, -3, -5};
        auto actual               = ext::iota(4, 1, -2);
        BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(),
                                      expected.begin(), expected.end());
    }
}

BOOST_AUTO_TEST_CASE(maxInTest) {
    {
        std::vector<int> args = {1, 2, 3, 1};
        int expected          = 3;
        auto actual           = ext::maxIn(std::begin(args), std::end(args));
        BOOST_CHECK_EQUAL(actual, expected);
        actual = ext::maxIn(args);
        BOOST_CHECK_EQUAL(actual, expected);
    }
    {
        std::vector<int> args = {1, 2, 3, 1};
        int expected          = 3;
        auto actual = ext::maxIn(std::begin(args), std::end(args), -1);
        BOOST_CHECK_EQUAL(actual, expected);
        actual = ext::maxIn(args, -1);
        BOOST_CHECK_EQUAL(actual, expected);
    }
    {
        std::vector<int> args;
        int expected = -1;
        auto actual  = ext::maxIn(std::begin(args), std::end(args), -1);
        BOOST_CHECK_EQUAL(actual, expected);
        actual = ext::maxIn(args, -1);
        BOOST_CHECK_EQUAL(actual, expected);
    }
    {
        std::vector<int> args;
        int expected = 0;
        auto actual  = ext::maxIn(std::begin(args), std::end(args));
        BOOST_CHECK_EQUAL(actual, expected);
        actual = ext::maxIn(args);
        BOOST_CHECK_EQUAL(actual, expected);
    }
    {
        std::vector<int64_t> args = {int64_t(1e12)};
        int64_t expected          = 1e12;
        auto actual = ext::maxIn(std::begin(args), std::end(args));
        BOOST_CHECK_EQUAL(actual, expected);
        actual = ext::maxIn(args);
        BOOST_CHECK_EQUAL(actual, expected);
    }
    {
        std::vector<int64_t> args = {};
        int64_t expected          = -1e12;
        auto actual =
            ext::maxIn(std::begin(args), std::end(args), -int64_t(1e12));
        BOOST_CHECK_EQUAL(actual, expected);
        actual = ext::maxIn(args, -int64_t(1e12));
        BOOST_CHECK_EQUAL(actual, expected);
    }
}

BOOST_AUTO_TEST_CASE(minInTest) {
    // maxInで多めに検証しているので、テストは少なめ
    {
        std::vector<int> args = {5, 2, 3, 100};
        int expected          = 2;
        auto actual           = ext::minIn(std::begin(args), std::end(args));
        BOOST_CHECK_EQUAL(actual, expected);
        actual = ext::minIn(args);
        BOOST_CHECK_EQUAL(actual, expected);
    }
}

//! @cond
BOOST_AUTO_TEST_SUITE_END();
//! @endcond
