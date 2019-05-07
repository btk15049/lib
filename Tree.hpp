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
    template <typename E=Edge>
    class Forest : public Graph<E> {
        private:
        using Graph<E>::add_edge;

        //! 根の集合
        vector<int> roots;

        /**
         * @brief
         * DFSで木を作る
         * @param g 元のグラフ
         * @param v 現在の頂点
         * @param used 既訪問リスト
         */
        void build(Graph<E>& g, int v,vector<bool>& used) {
            used[v] = true;
            for(int edge_id:g[v]){
                auto e = g.i2e(edge_id);
                const int u = e.versus(v);
                if(used[u])continue;
                //add_arc(e);
                this->add_arc(v,u);
                build(g,u,v);
            }
        }

        public:
        /**
         * @brief
         * 無向グラフから根付き森を新しく作る用のコンストラクタ
         * @see Graph::Graph()
         */
        Forest(Graph<E>& g , const int loop_begin = 0)
        : Graph<E>(g.size(), g.size()-1){
            vector<bool> used(g.size());
            for(int v:range(loop_begin, g.size())){
                if(used[v]==false){
                    build(g,v,v);
                    roots.push_back(v);
                }
            }
            for(int v:range(loop_begin)){
                if(used[v]==false){
                    build(g,v,v);
                    roots.push_back(v);
                }
            }
        }

        /**
         * @brief Get the roots object
         * @return vector<int>
         */
        vector<int> get_roots(){
            return roots;
        }
    };

    template <typename E=Edge>
    class Tree : public Forest<E> {
        private:
        using Forest<E>::get_roots;
        int root;
        public:
        Tree(int reserved_vertex_size = 1, int reserved_edge_size = -1, const int root = 0)
         : Graph<E>(reserved_vertex_size, reserved_edge_size) , root(root) {}
        Tree(Graph<E>& g, const int root = 0) : Forest<E>(g, root), root(root) {}
        inline int get_root(){
            return root;
        }
    };
}
using namespace _Tree_;
