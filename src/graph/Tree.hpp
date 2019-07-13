/*<head>*/
#pragma once
#include "graph/Graph.hpp"
/*</head>*/

/**
 * @file Tree.hpp
 * @brief 根付き森と根付き木
 * @author btk15049
 * @date 2019/05/07
 * @details
 *  verify:
 */

/**
 * @brief 根付き森クラス
 * @tparam E=Edge 新たな辺構造体作るときは書き換える
 * @details 0-indexedで使うことしか考えてないので注意．
 * @see Graph
 */
template <typename E = Edge>
class Forest : public Graph<E> {
  private:
    using Graph<E>::add_edge;

    //! 根の集合
    vector<int> roots;

    /**
     * @brief
     * DFSで木を作る
     */
    void build_tree(Graph<E>& g, const int v, vector<bool>& used) {
        used[v] = true;
        for (int edge_id : g[v]) {
            auto e      = g.i2e(edge_id);
            const int u = e.versus(v);
            if (used[u]) continue;
            e.a = v;
            e.b = u;
            this->add_arc(e);
            build_tree(g, u, used);
        }
    }

  public:
    /**
     * @brief
     * 無向グラフから根付き森を作る
     * @see Graph::Graph()
     */
    Forest(Graph<E>& g, const int loop_begin_vtx = 0)
        : Graph<E>(g.size(), g.size() - 1) {
        this->resize(g.size());
        vector<bool> used(g.size());
        for (int v : range(loop_begin_vtx, g.size() + loop_begin_vtx)) {
            v = v % g.size();
            if (used[v] == false) {
                build_tree(g, v, used);
                roots.push_back(v);
            }
        }
    }

    /**
     * @brief Get the roots object
     * @return vector<int>
     */
    vector<int> get_roots() { return roots; }
};

/**
 * @brief
 * "木"に限定したクラス
 * @tparam Edge 辺構造体
 */
template <typename E = Edge>
class Tree : public Forest<E> {
  private:
    using Forest<E>::get_roots;
    //! 根
    int root;

  public:
    /**
     * @brief Construct a new Tree object
     *
     * @param g 元のグラフ
     * @param root 根を明示的に指定したい時
     */
    Tree(Graph<E>& g, const int root = 0) : Forest<E>(g, root), root(root) {}

    /**
     * @brief Get the root object
     *
     * @return int
     */
    inline int get_root() { return root; }
};
