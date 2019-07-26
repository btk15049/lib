/**
 * @file Matrix.test.cpp
 * @author btk
 * @brief Matrix.hpp のテスト
 * @date 2019-06-10
 *
 * @copyright Copyright (c) 2019
 *
 */
//! @cond
#define BOOST_TEST_MAIN
//! @endcond
#include "num/Matrix.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(MatrixClass)

/**
 * @brief オブジェクト生成ができるかのテスト
 */
BOOST_AUTO_TEST_CASE(init) {
    Matrix<int, 5, 5> m;
    Chain<int, 5> chain(m);
}

/**
 * @brief 行列累乗のテストをフィボナッチで
 */
BOOST_AUTO_TEST_CASE(fibonacci) {
    Chain<int, 2> chain([]() {
        Matrix<int, 2, 2> m;
        m[0][0] = 1;
        m[0][1] = 1;
        m[1][0] = 1;
        m[1][1] = 0;
        return m;
    }());
    auto actual = chain.compute(
        []() {
            std::array<int, 2> in;
            in[0] = 1;
            in[1] = 0;
            return in;
        }(),
        6);
    std::array<int, 2> expected = {13, 8};
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(actual), std::end(actual), std::begin(expected),
                                  std::end(expected));
}


BOOST_AUTO_TEST_SUITE_END()