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


/**
 * @brief 入力サンプル生成
 *
 * @return Graph<>
 */
Graph<> forestSample() {
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
 * @brief 入力サンプル生成
 *
 * @return Graph<>
 */
Graph<> treeSample() {
    Graph<> g;
    g.add_edge(0, 1);
    g.add_edge(2, 1);
    g.add_edge(1, 3);
    g.add_edge(0, 4);
    g.add_edge(5, 3);
    g.add_edge(0, 6);
    g.add_edge(7, 6);
    return g;
}

/**
 * @brief DFSをして連結成分を取得
 * 処理をサボってN^2
 * @param v
 * @param forest
 * @return vector<int>
 */
vector<int> collect_component(int v, Forest<>& forest) {
    vector<int> vs;
    vs.push_back(v);
    for (int u : forest.Ns(v)) {
        for (auto c : collect_component(u, forest)) {
            vs.push_back(c);
        }
    }
    return vs;
}

BOOST_AUTO_TEST_SUITE(Tree)
/* #region class Forest */
BOOST_AUTO_TEST_SUITE(ForestClass)


/**
 * @brief インスタンス生成ができるかどうかのテスト
 */
BOOST_AUTO_TEST_CASE(Forest_createTest) {
    Graph<> arg = forestSample();
    Forest<> forest(arg);
    unused_var(forest);
}


/**
 * @brief 根集合が正しいかのテスト1
 */
BOOST_AUTO_TEST_CASE(Forest_checkRoots1) {
    Graph<> arg = forestSample();
    Forest<> forest(arg);
    vector<int> roots    = forest.get_roots();
    vector<int> expected = {0, 6};
    BOOST_CHECK_EQUAL_COLLECTIONS(roots.begin(), roots.end(), expected.begin(),
                                  expected.end());
}

/**
 * @brief 根集合が正しいかのテスト2
 */
BOOST_AUTO_TEST_CASE(Forest_checkRoots2) {
    Graph<> arg = forestSample();
    Forest<> forest(arg, 8);
    vector<int> roots    = forest.get_roots();
    vector<int> expected = {8, 0};
    BOOST_CHECK_EQUAL_COLLECTIONS(roots.begin(), roots.end(), expected.begin(),
                                  expected.end());
}

/**
 * @brief 頂点数が正しいかのテスト
 */
BOOST_AUTO_TEST_CASE(Forest_checkSize) {
    Graph<> arg = forestSample();
    Forest<> forest(arg);
    BOOST_CHECK_EQUAL(forest.size(), 11);
}

/**
 * @brief 辺の総数が正しいかのテスト
 */
BOOST_AUTO_TEST_CASE(Forest_checkAllDegree) {
    Graph<> arg = forestSample();
    Forest<> forest(arg);
    BOOST_CHECK_EQUAL(forest.degree(), 9);
}

/**
 * @brief 各辺の次数が正しいかのテスト
 */
BOOST_AUTO_TEST_CASE(Forest_checkEachDegree) {
    Graph<> arg = forestSample();
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
 * @brief 連結成分が正しいかのテスト1
 */
BOOST_AUTO_TEST_CASE(Forest_checkComponents1) {
    Graph<> arg = forestSample();
    Forest<> forest(arg);
    vector<int> component = collect_component(forest.get_roots()[0], forest);
    sort(ALL(component));
    vector<int> expected = {0, 1, 2, 3, 4, 5};
    BOOST_CHECK_EQUAL_COLLECTIONS(component.begin(), component.end(),
                                  expected.begin(), expected.end());
}

/**
 * @brief 連結成分が正しいかのテスト2
 */
BOOST_AUTO_TEST_CASE(Forest_checkComponents2) {
    Graph<> arg = forestSample();
    Forest<> forest(arg);
    vector<int> component = collect_component(forest.get_roots()[1], forest);
    sort(ALL(component));
    vector<int> expected = {6, 7, 8, 9, 10};
    BOOST_CHECK_EQUAL_COLLECTIONS(component.begin(), component.end(),
                                  expected.begin(), expected.end());
}


BOOST_AUTO_TEST_SUITE_END()
/* #endregion */

/* #region class Tree */
BOOST_AUTO_TEST_SUITE(TreeClass)
/**
 * @brief インスタンス生成ができるかどうかのテスト
 */
BOOST_AUTO_TEST_CASE(Tree_createTest1) {
    Graph<> arg = treeSample();
    _Tree_::Tree<> tree(arg);
    unused_var(tree);
}

/**
 * @brief 根が正しいかのテスト1
 */
BOOST_AUTO_TEST_CASE(Tree_checkRoot1) {
    Graph<> arg = treeSample();
    _Tree_::Tree<> tree(arg);
    BOOST_CHECK_EQUAL(tree.get_root(), 0);
}

/**
 * @brief 根が正しいかのテスト2
 */
BOOST_AUTO_TEST_CASE(Tree_checkRoot2) {
    Graph<> arg = treeSample();
    _Tree_::Tree<> tree(arg, 3);
    BOOST_CHECK_EQUAL(tree.get_root(), 3);
}

/**
 * @brief 頂点数が正しいかのテスト
 */
BOOST_AUTO_TEST_CASE(Tree_checkAllSize) {
    Graph<> arg = treeSample();
    _Tree_::Tree<> tree(arg);
    BOOST_CHECK_EQUAL(tree.size(), 8);
}

/**
 * @brief 辺の総数が正しいかのテスト
 */
BOOST_AUTO_TEST_CASE(Tree_checkAllDegree) {
    Graph<> arg = treeSample();
    _Tree_::Tree<> tree(arg);
    BOOST_CHECK_EQUAL(tree.degree(), 7);
}

/**
 * @brief 各辺の次数が正しいかのテスト
 */
BOOST_AUTO_TEST_CASE(Tree_checkEachDegree) {
    Graph<> arg = treeSample();
    _Tree_::Tree<> tree(arg);
    vector<int> degrees;
    for (int v : range(tree.size())) {
        degrees.push_back(tree.degree(v));
    }
    vector<int> expected = {3, 2, 0, 1, 0, 0, 1, 0};
    BOOST_CHECK_EQUAL_COLLECTIONS(degrees.begin(), degrees.end(),
                                  expected.begin(), expected.end());
}

/**
 * @brief 連結成分が正しいかのテスト1
 */
BOOST_AUTO_TEST_CASE(Tree_checkComponents) {
    Graph<> arg = treeSample();
    _Tree_::Tree<> tree(arg);
    vector<int> component = collect_component(tree.get_root(), tree);
    sort(ALL(component));
    vector<int> expected = {0, 1, 2, 3, 4, 5, 6, 7};
    BOOST_CHECK_EQUAL_COLLECTIONS(component.begin(), component.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()
/* #endregion */

BOOST_AUTO_TEST_SUITE_END()