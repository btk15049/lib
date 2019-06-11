/**
 * @file HeavyLightDecomposition.hpp
 * @author btk
 * @brief 重軽分解
 * @version 0.1
 * @date 2019-06-04
 *
 */
/*<head>*/
#pragma once
#include "Buffer.hpp"
#include "Template.hpp"
#include "Tree.hpp"
/*</head>*/


namespace _HeavyLightDecomposition_ {
    /**
     * @brief 重軽分解
     * @details 各パスを色で塗っていく
     * col[v] = col[u] のときは同じ成分
     * col のナンバリング順は DFS ordering
     * とする。ある成分の子にあたる成分は必ず番号が大きくなる
     */
    template <typename E>
    class HeavyLightDecomposition {
      private:
        BufferManager<int>& lender;
        static constexpr int super_root = -1;
        //! col[v] := 頂点 v の色（含まれるパス成分の番号）
        int* col;
        //! i2v[i] := v HL分解の順にそった、元のグラフでのDFS-ordering
        int* i2v;
        //! i2v[v2i[v]]]=v
        int* v2i;

        //! 各パスのrootの開始位置(rootがordのどこにあるか)
        int* col_root;
        //! 各頂点の親
        int* par;

        /**
         * @brief
         * subに、各頂点を根とした部分木のサイズを求める
         * @param v
         * @param sub
         * @param f
         */
        void compute_subtrees(int v, vector<int>& sub, Forest<E>& f) {
            sub[v]++;
            for (int u : f.Ns(v)) {
                compute_subtrees(u, sub, f);
                sub[v] += sub[u];
            }
        }

        /**
         * @brief
         * compute_subtreesで求めた部分木サイズ使ってHL分解をする
         * @param v
         * @param sub
         * @param f
         * @param seg_id
         * @param col_id
         * @details
         * 太い枝を優先に色ぬりをしていく(細い枝に進むたびcol_idを進める)
         * 頂点に訪れる度seg_idを進める
         */
        void coloring(int v, vector<int>& sub, Forest<E>& f, int& seg_id,
                      int& col_id) {
            col[v]      = col_id;
            i2v[seg_id] = v;
            v2i[v]      = seg_id;
            seg_id++;
            if (f.degree(v) == 0) return;
            int top = 0;
            for (int i : range(f.degree(v))) {
                if (sub[f.i2e(f[v][top]).versus(v)]
                    < sub[f.i2e(f[v][i]).versus(v)]) {
                    top = i;
                }
            }
            {
                const int u = f.i2e(f[v][top]).versus(v);
                par[u]      = v;
                coloring(u, sub, f, seg_id, col_id);
            }
            for (int i : range(f.degree(v))) {
                if (top == i) continue;
                const int u = f.i2e(f[v][i]).versus(v);
                par[u]      = v;
                col_root[++col_id]=seg_id;
                coloring(u, sub, f, seg_id, col_id);
            }
        }


      public:
        /**
         * @brief
         * 色col_idが表すパスの長さ(頂点数）を取得
         * @param col_id
         * @return int
         */
        inline int len(int col_id) const {
            return col_root[col_id + 1] - col_root[col_id];
        }


        /**
         * @brief
         * vとuのlcaを返す
         * @param v
         * @param u
         * @return int
         * @details
         * パスの成分のidの大きい方を上にあげてく
         * 含まれる成分が一緒になったら、DFS-orderの小さい方が答え
         */
        inline int lca(int v, int u) const {
            while (v != super_root && u != super_root && col[v] != col[u]) {
                if (col[v] > col[u]) swap(v, u);
                u = par[i2v[col_root[col[u]]]];
            }
            cerr << v << " " << u << endl;
            if (v == super_root || u == super_root) return super_root;
            return i2v[min(v2i[v], v2i[u])];
        }

        /**
         * @brief Construct a new Heavy Light Decomposition object
         * lenderにはBlockBufferを使うのを推奨 N*5メモリがいるよ
         * @param f
         * @param lender
         */
        HeavyLightDecomposition(Forest<E>& f, BufferManager<int>& lender)
            : lender(lender) {
            const int n = f.size();
            col         = lender.pop(n + 10);
            v2i         = lender.pop(n + 10);
            i2v         = lender.pop(n + 10);
            col_root    = lender.pop(n + 10);
            par         = lender.pop(n + 10);

            int col_id = 0;
            int seg_id = 0;
            vector<int> sub(n, 0);
            for (int r : f.get_roots()) {
                compute_subtrees(r, sub, f);
                par[r] = super_root;
                col_root[col_id]=seg_id;
                coloring(r, sub, f, seg_id, col_id);
                col_id++;
            }
        }

        /**
         * @brief Destroy the Heavy Light Decomposition object
         * デストラクタ
         * メモリを返すよ
         */
        ~HeavyLightDecomposition() {
            lender.push(col);
            lender.push(v2i);
            lender.push(i2v);
            lender.push(col_root);
            lender.push(par);
        }

        inline int get_color(int v) const { return col[v]; }

        inline int get_id(const int v) const { return v2i[v]; }

        inline int get_vertex(const int id) const { return i2v[id]; }
    };
} // namespace _HeavyLightDecomposition_
using namespace _HeavyLightDecomposition_;