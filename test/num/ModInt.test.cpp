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
#define STATIC_MOD 1e9 + 7;
#include "num/ModInt.hpp"
#include <boost/test/included/unit_test.hpp>
#include <functional>
#include <utility>
#include <vector>

BOOST_AUTO_TEST_SUITE(ModIntClass)

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Factorials)
BOOST_AUTO_TEST_CASE(Initialize) {
    BOOST_CHECK_EQUAL(factorial::size, 3123456);
    factorial::build();
    BOOST_CHECK_EQUAL(*(factorial::factorial[5]), 120);
}

BOOST_AUTO_TEST_CASE(MultiChoose) {
    auto gen = [](int line, int n, int r, int ans) {
        return std::vector<int>{line, n, r, ans};
    };
    auto run = [](std::vector<int> one) {
        const std::string line = "line:" + std::to_string(one.at(0));
        const int n            = one.at(1);
        const int r            = one.at(2);
        const int ans          = one.at(3);

        BOOST_CHECK_EQUAL(
            line + " ans:" + std::to_string(*factorial::multiChoose(n, r)),
            line + " ans:" + std::to_string(ans));
    };
    auto cases = {
        /*             n   r  ans */
        gen(__LINE__, +0, +0, +1), //<br>
        gen(__LINE__, +0, +1, +0), //<br>
        gen(__LINE__, +0, +2, +0), //<br>
        gen(__LINE__, +0, -1, +0), //<br>
        gen(__LINE__, +0, -2, +0), //<br>
        gen(__LINE__, -1, +0, +0), //<br>
        gen(__LINE__, -1, +1, +0), //<br>
        gen(__LINE__, -1, +2, +0), //<br>
        gen(__LINE__, -1, -1, +0), //<br>
        gen(__LINE__, -1, -2, +0), //<br>
        gen(__LINE__, +1, +0, +1), //<br>
        gen(__LINE__, +1, +1, +1), //<br>
        gen(__LINE__, +1, +2, +1), //<br>
        gen(__LINE__, +1, -1, +0), //<br>
        gen(__LINE__, +1, -2, +0), //<br>
        gen(__LINE__, +2, +0, +1), //<br>
        gen(__LINE__, +2, +1, +2), //<br>
        gen(__LINE__, +2, +2, +3), //<br>
        gen(__LINE__, +2, -1, +0), //<br>
        gen(__LINE__, +2, -2, +0), //<br>
    };
    for (const auto &one : cases) {
        run(one);
    }
}

BOOST_AUTO_TEST_CASE(MultiChooseWithLimit) {
    auto gen = [](int line, int n, int r, int lim, int ans) {
        return std::vector<int>{line, n, r, lim, ans};
    };
    auto run = [](std::vector<int> one) {
        const std::string line = "line:" + std::to_string(one.at(0));
        const int n            = one.at(1);
        const int r            = one.at(2);
        const int lim          = one.at(3);
        const int ans          = one.at(4);

        BOOST_CHECK_EQUAL(
            line + " ans:" + std::to_string(*factorial::multiChoose(n, r, lim)),
            line + " ans:" + std::to_string(ans));
    };
    auto cases = {
        /*             n   r  lim ans */
        gen(__LINE__, +0, +0, +0, +1), // <br>
        gen(__LINE__, +0, +0, +1, +1), // <br>
        gen(__LINE__, +0, +0, +2, +1), // <br>
        gen(__LINE__, +0, +0, -1, +1), // <br>
        gen(__LINE__, +0, +1, +0, +0), // <br>
        gen(__LINE__, +0, +1, +1, +0), // <br>
        gen(__LINE__, +0, +1, +2, +0), // <br>
        gen(__LINE__, +0, +1, -1, +0), // <br>
        gen(__LINE__, +0, +2, +0, +0), // <br>
        gen(__LINE__, +0, +2, +1, +0), // <br>
        gen(__LINE__, +0, +2, +2, +0), // <br>
        gen(__LINE__, +0, +2, -1, +0), // <br>
        gen(__LINE__, +0, -1, +0, +0), // <br>
        gen(__LINE__, +0, -1, +1, +0), // <br>
        gen(__LINE__, +0, -1, +2, +0), // <br>
        gen(__LINE__, +0, -1, -1, +0), // <br>

        gen(__LINE__, +1, +0, +0, +1), // <br>
        gen(__LINE__, +1, +0, +1, +1), // <br>
        gen(__LINE__, +1, +0, +2, +1), // <br>
        gen(__LINE__, +1, +0, -1, +0), // <br>
        gen(__LINE__, +1, +1, +0, +0), // <br>
        gen(__LINE__, +1, +1, +1, +1), // <br>
        gen(__LINE__, +1, +1, +2, +1), // <br>
        gen(__LINE__, +1, +1, -1, +0), // <br>
        gen(__LINE__, +1, +2, +0, +0), // <br>
        gen(__LINE__, +1, +2, +1, +0), // <br>
        gen(__LINE__, +1, +2, +2, +1), // <br>
        gen(__LINE__, +1, +2, -1, +0), // <br>
        gen(__LINE__, +1, -1, +0, +0), // <br>
        gen(__LINE__, +1, -1, +1, +0), // <br>
        gen(__LINE__, +1, -1, +2, +0), // <br>
        gen(__LINE__, +1, -1, -1, +0), // <br>

        gen(__LINE__, +2, +0, +0, +1), // <br>
        gen(__LINE__, +2, +0, +1, +1), // <br>
        gen(__LINE__, +2, +0, +2, +1), // <br>
        gen(__LINE__, +2, +0, -1, +0), // <br>
        gen(__LINE__, +2, +1, +0, +0), // <br>
        gen(__LINE__, +2, +1, +1, +2), // <br>
        gen(__LINE__, +2, +1, +2, +2), // <br>
        gen(__LINE__, +2, +1, -1, +0), // <br>
        gen(__LINE__, +2, +2, +0, +0), // <br>
        gen(__LINE__, +2, +2, +1, +1), // <br>
        gen(__LINE__, +2, +2, +2, +3), // <br>
        gen(__LINE__, +2, +2, -1, +0), // <br>
        gen(__LINE__, +2, -1, +0, +0), // <br>
        gen(__LINE__, +2, -1, +1, +0), // <br>
        gen(__LINE__, +2, -1, +2, +0), // <br>
        gen(__LINE__, +2, -1, -1, +0), // <br>

        gen(__LINE__, -1, +0, +0, +0), // <br>
        gen(__LINE__, -1, +0, +1, +0), // <br>
        gen(__LINE__, -1, +0, +2, +0), // <br>
        gen(__LINE__, -1, +0, -1, +0), // <br>
        gen(__LINE__, -1, +1, +0, +0), // <br>
        gen(__LINE__, -1, +1, +1, +0), // <br>
        gen(__LINE__, -1, +1, +2, +0), // <br>
        gen(__LINE__, -1, +1, -1, +0), // <br>
        gen(__LINE__, -1, +2, +0, +0), // <br>
        gen(__LINE__, -1, +2, +1, +0), // <br>
        gen(__LINE__, -1, +2, +2, +0), // <br>
        gen(__LINE__, -1, +2, -1, +0), // <br>
        gen(__LINE__, -1, -1, +0, +0), // <br>
        gen(__LINE__, -1, -1, +1, +0), // <br>
        gen(__LINE__, -1, -1, +2, +0), // <br>
        gen(__LINE__, -1, -1, -1, +0), // <br>
    };
    for (const auto &one : cases) {
        run(one);
    }
}


BOOST_AUTO_TEST_SUITE_END()
