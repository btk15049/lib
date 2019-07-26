/**
 * @file Graph.test.cpp
 * @brief Graph.hpp のテスト
 * @version 0.1
 * @date 2019-05-25
 *
 * @copyright Copyright (c) 2019
 *
 */
//! @cond
#define BOOST_TEST_MAIN
//! @endcond
#include "graph/Graph.hpp"
#include "graph/GraphUtil.hpp"
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

/**
 * @brief Construct a new boost auto test case object
 *
 */
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
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(GraphUtilClass)

/**
 * @brief
 *
 * @return Graph<WeightedEdge<int>>
 */
Graph<WeightedEdge<int>> sample_weighted_graph() {
    Graph<WeightedEdge<int>> g;
    g.add_edge(2, 0, 4);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 3, 2);
    g.add_edge(3, 0, 0);
    return g;
}

/**
 * @brief Construct a new boost auto test case object
 * ダイクストラのテスト
 */
BOOST_AUTO_TEST_CASE(Dijkstra) {
    auto target          = sample_weighted_graph();
    std::vector<int> actual   = dijkstra(target, (int)1e9, 2);
    std::vector<int> expected = {3, 1, 0, 3};
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(actual), std::end(actual), std::begin(expected),
                                  std::end(expected));
}


BOOST_AUTO_TEST_SUITE_END() BOOST_AUTO_TEST_SUITE_END()