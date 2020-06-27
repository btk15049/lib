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

//! @cond
BOOST_AUTO_TEST_SUITE_END();
//! @endcond
