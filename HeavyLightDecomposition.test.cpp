/**
 * @file HeavyLightDecomposition.test.cpp
 * @author btk
 * @brief
 * @version 0.1
 * @date 2019-06-11
 *
 * @copyright Copyright (c) 2019
 *
 */

#define BOOST_TEST_MAIN
#include "Buffer.hpp"
#include "HeavyLightDecomposition.hpp"
#include <boost/test/included/unit_test.hpp>

/**
 * @brief 入力サンプル生成
 *
 * @return Graph<>
 */
Tree<> forestSample() {
    Graph<> g;
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(0, 4);
    g.add_edge(3, 5);
    g.add_edge(0, 6);
    g.add_edge(6, 7);
    g.add_edge(8, 9);
    g.add_edge(8, 10);
    g.add_edge(10, 11);
    g.add_edge(3, 12);
    return Tree<>(g);
}

BlockBuffer(int, 5, 212345, blocks);

BOOST_AUTO_TEST_SUITE(HeavyLightDecompositionClass)

/**
 * @brief オブジェクト生成ができるかのテスト
 */
BOOST_AUTO_TEST_CASE(init) {
    auto forest = forestSample();
    HeavyLightDecomposition<Edge> hld(forest, blocks);
}

/**
 * @brief 色塗りが正しいかのテスト
 */
BOOST_AUTO_TEST_CASE(coloringTest) {
    auto forest = forestSample();
    HeavyLightDecomposition<Edge> hld(forest, blocks);
    vector<int> expected = {0, 0, 0, 0, 2, 0, 3, 3, 4, 5, 4, 4, 1};
    vector<int> actual;
    for (int v : range(forest.size())) {
        actual.push_back(hld.color(v));
    }
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(actual), end(actual), begin(expected),
                                  end(expected));
}

/**
 * @brief lca
 */
BOOST_AUTO_TEST_CASE(lcaTest) {
    auto forest = forestSample();
    HeavyLightDecomposition<Edge> hld(forest, blocks);
    BOOST_CHECK_EQUAL(hld.lca(1, 4), 0);
    BOOST_CHECK_EQUAL(hld.lca(0, 2), 0);
    BOOST_CHECK_EQUAL(hld.lca(7, 12), 0);
    BOOST_CHECK_EQUAL(hld.lca(5, 12), 3);
    BOOST_CHECK_EQUAL(hld.lca(0, 8), -1);
    BOOST_CHECK_EQUAL(hld.lca(11, 12), -1);
}


BOOST_AUTO_TEST_SUITE_END()