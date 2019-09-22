/**
 * @file UnionFind.test.cpp
 * @author btk
 * @brief UnionFind.hpp のテスト
 * @date 2019-06-28
 *
 * @copyright Copyright (c) 2019
 *
 */

//! @cond
#define BOOST_TEST_MAIN
//! @endcond
#include "structure/UnionFind.hpp"
#include "template/Random.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(UnionFindClass)
/**
 * @brief 初期化時のテスト
 */
BOOST_AUTO_TEST_CASE(Construct) {
    UnionFind uf(10);
    for (int i = 0; i < 10; i++) {
        BOOST_CHECK_EQUAL(uf.find(i), i);
    }
}

/**
 * @brief 雑なストレステスト,localでも1秒超えないようにみたいな調整
 */
BOOST_AUTO_TEST_CASE(StressTest, *boost::unit_test::timeout(1)) {
    constexpr int N = 112345;
    UnionFind uf(N);

    for (int i = 0; i < N; i++) {
        BOOST_CHECK_EQUAL(uf.find(i), i);
    }

    XorShift32 rnd;
    int unite_count = 0;
    for (int i = 0; i < 10 * N; i++) {
        unite_count += uf.unite(rnd.next_int() % N, rnd.next_int() % N) ? 1 : 0;
    }

    BOOST_CHECK_EQUAL(unite_count, N - 1);
    for (int i = 0; i < N; i++) {
        BOOST_CHECK_EQUAL(uf.same(0, i), true);
    }
}


BOOST_AUTO_TEST_SUITE_END()