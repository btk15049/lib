/**
 * @file Graph.test.cpp
 * @brief Graph.hpp のテスト
 * @version 0.1
 * @date 2019-05-25
 *
 * @copyright Copyright (c) 2019
 *
 */
#define BOOST_TEST_MAIN
#include "Graph.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(GraphTest)
BOOST_AUTO_TEST_SUITE(GraphClass)
/**
 * @brief
 * 頂点数4の無向パスを生成
 * @return Graph<>
 */
Graph<> sample_undirected_path() {
    Graph<> g;
    g.add_edge(2, 3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    return g;
}

BOOST_AUTO_TEST_CASE(resize) {
    auto target = sample_undirected_path();
    target.resize(10);
    BOOST_CHECK_EQUAL(target.degree(0), 1);
    BOOST_CHECK_EQUAL(target.degree(1), 2);
    BOOST_CHECK_EQUAL(target.degree(2), 2);
    BOOST_CHECK_EQUAL(target.degree(3), 1);
    for (int vi : range(4, 10)) {
        BOOST_CHECK_EQUAL(target.degree(vi), 0);
    }
}

BOOST_AUTO_TEST_SUITE_END() BOOST_AUTO_TEST_SUITE_END()