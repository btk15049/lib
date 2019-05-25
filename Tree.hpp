/*<head>*/
#pragma once
#include "Graph.hpp"
/*</head>*/

/**
 * @file Tree.hpp
 * @brief 根付き森と根付き木
 * @author btk15049
 * @date 2019/05/07
 * @datails
 *  verify:
 */


namespace _Tree_ {
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
        void build_tree(Graph<E>& g, int v, vector<bool>& used) {
            used[v] = true;
            for (int edge_id : g[v]) {
                auto e      = g.i2e(edge_id);
                const int u = e.versus(v);
                if (used[u]) continue;
                // add_arc(e);
                this->add_arc(v, u);
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

    template <typename E = Edge>
    class Tree : public Forest<E> {
      private:
        using Forest<E>::get_roots;
        int root;

      public:
        Tree(Graph<E>& g, const int root = 0)
            : Forest<E>(g, root), root(root) {}
        inline int get_root() { return root; }
    };
} // namespace _Tree_
using namespace _Tree_;