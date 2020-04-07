/**
 * @file Macro.test.cpp
 * @author btk
 * @brief Macro.hppのテスト
 * @version 0.1
 * @date 2019-07-26
 *
 * @copyright Copyright (c) 2019
 *
 */
//! @cond
#define BOOST_TEST_MAIN
//! @endcond

#include "template/Macro.hpp"
#include <boost/test/included/unit_test.hpp>
#include <string>

BOOST_AUTO_TEST_SUITE(Macro)
/**
 * @brief 変数名表示マクロのテスト
 */
BOOST_AUTO_TEST_CASE(VarName) {
    int a = 0;
    BOOST_CHECK_EQUAL(VAR_NAME(a), "a");

    std::string b = "string";
    BOOST_CHECK_EQUAL(VAR_NAME(b), "b");

    int c[2] = {1, 2};
    BOOST_CHECK_EQUAL(VAR_NAME(c), "c");

    unused_var(a);
    unused_var(b);
    unused_var(c);
}

/**
 * @brief ローカル実行時のDEBUGマクロをテスト
 */
BOOST_AUTO_TEST_CASE(WhenLocal) {
    DEBUG;
    else BOOST_FAIL("ここには来ないはず");
}

/**
 * @brief 多次元vector関数のテスト
 */
BOOST_AUTO_TEST_CASE(NestingVector) {
    {
        std::vector<int> expected(10, 0);
        auto actual = nestingVector<int>(10);
        BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(expected), std::end(expected),
                                      std::begin(actual), std::end(actual));
    }
    {
        std::vector<std::vector<int>> expected(20, std::vector<int>(10, 0));
        auto actual = nestingVector<int>(20, 10);
        BOOST_ASSERT(actual == expected);
    }
}
BOOST_AUTO_TEST_SUITE_END()