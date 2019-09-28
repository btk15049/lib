/**
 * @file Dinic.test.cpp
 * @author btk
 * @brief Dinic.hpp のテスト
 * @todo 未実装
 * @version 0.1
 * @date 2019-06-28
 * @copyright Copyright (c) 2019
 */
//! @cond
#define BOOST_TEST_MAIN
//! @endcond
#include "graph/Dinic.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Init) {
    FlowGraph<FlowEdge<int>> g;
    g.resize(2);
    int actual   = Dinic<int, 10>(g).solve(0, 1);
    int expected = 0;
    BOOST_CHECK_EQUAL(actual, expected);
}