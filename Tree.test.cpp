/**
 * @file Tree.test.cpp
 * @author btk
 * @brief Tree.hppのテスト
 * @date 2019-05-08
 *
 * @copyright Copyright (c) 2019
 *
 */
#define BOOST_TEST_MAIN
#include "Tree.hpp"
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(Tree)
/* #region class Forest */
BOOST_AUTO_TEST_SUITE(ForestClass)

/**
 * @brief サンプル生成
 *
 * @return Graph<>
 */
Graph<> graphSample() {
    Graph<> g;
    g.add_edge(0, 1);
    g.add_edge(2, 1);
    g.add_edge(1, 3);
    g.add_edge(0, 4);
    g.add_edge(5, 3);
    g.add_edge(6, 7);
    g.add_edge(8, 7);
    g.add_edge(8, 9);
    g.add_edge(9, 10);
    return g;
}

/**
 * @brief インスタンス生成ができるかどうかのテスト
 */
BOOST_AUTO_TEST_CASE(createTest) {
    Graph<> arg = graphSample();
    Forest<> forest(arg);
    unused_var(forest);
}

/**
 * @brief 根集合が正しいかのテスト1
 */
BOOST_AUTO_TEST_CASE(checkRoots1) {
    Graph<> arg = graphSample();
    Forest<> forest(arg);
    vector<int> roots    = forest.get_roots();
    vector<int> expected = {0, 6};
    BOOST_CHECK_EQUAL_COLLECTIONS(roots.begin(), roots.end(), expected.begin(),
                                  expected.end());
}

/**
 * @brief 根集合が正しいかのテスト2
 */
BOOST_AUTO_TEST_CASE(checkRoots2) {
    Graph<> arg = graphSample();
    Forest<> forest(arg, 8);
    vector<int> roots    = forest.get_roots();
    vector<int> expected = {8, 0};
    BOOST_CHECK_EQUAL_COLLECTIONS(roots.begin(), roots.end(), expected.begin(),
                                  expected.end());
}

/**
 * @brief 辺の総数が正しいかのテスト
 */
BOOST_AUTO_TEST_CASE(checkAllDegree) {
    Graph<> arg = graphSample();
    Forest<> forest(arg, 8);
    BOOST_CHECK_EQUAL(forest.degree(), 9);
}

/**
 * @brief 各辺の次数が正しいかのテスト
 */
BOOST_AUTO_TEST_CASE(checkEachDegree) {
    Graph<> arg = graphSample();
    Forest<> forest(arg);
    vector<int> degrees;
    for (int v : range(forest.size())) {
        degrees.push_back(forest.degree(v));
    }
    vector<int> expected = {2, 2, 0, 1, 0, 0, 1, 1, 1, 1, 0};
    BOOST_CHECK_EQUAL_COLLECTIONS(degrees.begin(), degrees.end(),
                                  expected.begin(), expected.end());
}

/**
 * @brief 連結成分を取得
 * 処理をサボってN^2
 * @param v
 * @param forest
 * @return vector<int>
 */
vector<int> get_component(int v, Forest<>& forest) {
    vector<int> vs;
    vs.push_back(v);
    for (int u : forest.Ns(v)) {
        for (auto c : get_component(u, forest)) {
            vs.push_back(c);
        }
    }
    return vs;
}

/**
 * @brief 連結成分が正しいかのテスト1
 */
BOOST_AUTO_TEST_CASE(checkComponents1) {
    Graph<> arg = graphSample();
    Forest<> forest(arg);
    vector<int> component = get_component(forest.get_roots()[0], forest);
    sort(ALL(component));
    vector<int> expected = {0, 1, 2, 3, 4, 5};
    BOOST_CHECK_EQUAL_COLLECTIONS(component.begin(), component.end(),
                                  expected.begin(), expected.end());
}

/**
 * @brief 連結成分が正しいかのテスト2
 */
BOOST_AUTO_TEST_CASE(checkComponents2) {
    Graph<> arg = graphSample();
    Forest<> forest(arg);
    vector<int> component = get_component(forest.get_roots()[1], forest);
    sort(ALL(component));
    vector<int> expected = {6, 7, 8, 9, 10};
    BOOST_CHECK_EQUAL_COLLECTIONS(component.begin(), component.end(),
                                  expected.begin(), expected.end());
}


BOOST_AUTO_TEST_SUITE_END()
/* #endregion */

/* #region class Tree */


BOOST_AUTO_TEST_SUITE_END()