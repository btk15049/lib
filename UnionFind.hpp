/**
 * @file UnionFind.hpp
 * @author btk
 * @brief Union-Find 木
 * @version 0.1
 * @date 2019-06-26
 * @todo test
 */
/*<head>*/
#pragma once
#include "Template.hpp"
/*</head>*/


namespace _UnionFind_ {

    /**
     * @brief unionとfindとsameができる普通のUnion-Find
     */
    class UnionFind {
      private:
        vector<int> par, rank;

        /**
         * @brief ${x}の親を${new_par}に設定åå
         * @param x
         * @param new_par
         */
        inline void set_par(int x, int new_par) { par[x] = new_par; }

      public:
        /**
         * @brief xの親を探す
         * @param x
         * @return int
         */
        int find(int x) {
            if (par[x] != x) {
                int new_par = find(par[x]);
                set_par(x, new_par);
            }
            return par[x];
        }

        /**
         * @brief Construct a new Union Find object
         *
         * @param n
         */
        UnionFind(int n) : par(n), rank(n) {
            for (int i = 0; i < n; i++) {
                par[i] = i, rank[i] = 0;
            }
        }

        /**
         * @brief {xの属する集合}と{yの属する集合}をマージする
         *
         * @param x
         * @param y
         * @return true マージに成功したとき
         * @return false マージに失敗したとき（もともと同じ集合に属していた時）
         */
        bool unite(int x, int y) {
            x = find(x);
            y = find(y);
            if (x == y) return false;
            if (rank[x] < rank[y]) swap(x, y);
            set_par(y, x);
            if (rank[x] == rank[y]) rank[x]++;
            return true;
        }

        /**
         * @brief　xとyが同じ集合に属しているかどうか判定する
         * @param x
         * @param y
         * @return true
         * @return false
         */
        bool same(int x, int y) { return find(x) == find(y); }
    };
} // namespace _UnionFind_
using namespace _UnionFind_;