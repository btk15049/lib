/**
 * @file Dinic.hpp
 * @brief Dinic法の実装
 * @author btk15049
 * @date 2019/03/13
 * @details
 * @todo project selection problem
 *  verify: WUPC F
 */

/*<head>*/
#pragma once
#include "graph/Graph.hpp"
/*</head>*/

#include <queue>

/**
 * @brief フロー用の辺構造体
 * @tparam F 流量の型
 */
template <typename F>
struct FlowEdge {
    //! 辺id
    int id;
    //! 端点
    int a;
    //! 端点
    int b;
    //! その辺に流せる流量
    F cap;
    //! 逆向き辺のid
    int rev;
    /**
     * @brief Construct a new Edge object
     * @param id 辺番号
     * @param a 辺に接続する頂点番号
     * @param b 辺に接続する頂点番号
     * @param cap 辺に許容できる流量
     * @param rev 対応する逆向き辺のid
     */
    FlowEdge(int id = 0, int a = 0, int b = 0, F cap = 0, int rev = 0)
        : id(id), a(a), b(b), cap(cap), rev(rev) {}
    /**
     * @brief 辺における，vの対になってる頂点番号を取得する
     * @param v 頂点番号
     * @return int vじゃない方の頂点番号
     */
    inline int versus(const int v) const { return a ^ b ^ v; }
};

/**
 * @brief フロー用のグラフクラス,Graphを継承
 * @tparam T 辺構造体
 */
template <typename T>
class FlowGraph : public Graph<T> {
  private:
    using E = T;
    using Graph<E>::add_arc; // add_arcは外から呼び出せないようにする
  public:
    /**
     * @brief a->bへ流量fの辺を追加
     * @tparam F 流量の型
     * @param a 頂点番号
     * @param b 頂点番号
     * @param f 最大流量
     * @details Graph::add_edge をオーバーライドしている．
     */
    template <typename F>
    inline void add_edge(int a, int b, F f) {
        const int id = this->degree();
        this->add_arc(a, b, f, id + 1);
        this->add_arc(b, a, 0, id);
    }
    /**
     * @brief Construct a new Flow Graph object
     * @details
     * 完全転送してるので詳しくはGraphクラスのコンストラクタを参照．
     */
    template <typename... Ts>
    FlowGraph(Ts&&... params) : Graph<E>(std::forward<Ts>(params)...) {}
};

/**
 * @brief Dinic法の実装
 * @tparam T 流量の型
 * @tparam flow_inf 流量の最大値
 */
template <typename T, T flow_inf>
class Dinic {
  private:
    using F = T;
    using E = FlowEdge<F>;
    FlowGraph<E>* G;
    /**
     * @brief 最短路求めるBFSをする
     * @param s 始点
     * @return vector<int> sから各頂点への最短距離
     */
    std::vector<int> bfs(const int s) {
        int N = G->size();
        std::queue<int> que;
        std::vector<int> dist(N, -1);
        dist[s] = 0;
        que.push(s);
        for (; !que.empty(); que.pop()) {
            const int v = que.front();
            for (int id : (*G)[v]) {
                const E& e  = G->i2e(id);
                const int u = e.versus(v);
                if (e.cap > 0 && dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    que.push(u);
                }
            }
        }
        return dist;
    }
    /**
     * @brief s->tに向けてできるだけフローを流す
     */
    F dfs(const int v, const int s, const F f, std::vector<unsigned>& I,
          std::vector<int>& D) {
        if (v == s) return f;
        const std::vector<int>& edge_ids = (*G)[v];
        for (unsigned& i = I[v]; i < edge_ids.size(); i++) {
            E& e        = G->i2e(edge_ids[i]);
            E& re       = G->i2e(e.rev);
            const int u = e.versus(v);
            if (re.cap > 0 && D[v] > D[u]) {
                F d = dfs(u, s, std::min(f, re.cap), I, D);
                if (d > 0) {
                    e.cap += d;
                    re.cap -= d;
                    return d;
                }
            }
        }
        return 0;
    }

  public:
    /**
     * @brief 現在の残余グラフから得られる最大流を求めて流す．
     * @param s 始点
     * @param t 終点
     * @return F 流量
     */
    F solve(const int s, const int t) {
        F res = 0;
        while (true) {
            std::vector<int> dist = bfs(s);
            if (dist[t] < 0 || flow_inf == res) break;
            std::vector<unsigned> iter(G->size(), 0);
            while (true) {
                F f = dfs(t, s, flow_inf - res, iter, dist);
                if (f == 0) break;
                res += f;
            }
        }
        return res;
    }
    /**
     * @brief Construct a new Dinic object
     * @param G 最大流を流したいグラフ
     */
    Dinic(FlowGraph<E>& G) : G(&G) {}
};