/**
 * @file Graph.hpp
 * @brief グラフクラス
 * @author btk15049
 * @date 2019/03/11
 * @details
 *  verify: WUPC C
 */

/*<head>*/
#pragma once
#include "template/Loop.hpp"
#include <algorithm>
#include <vector>
/*</head>*/


/**
 * @brief 辺を扱う構造体の例
 * @details
 *   辺に重みなどを加えたい場合は変数とかを増やして作る．
 *   Graphに使うために必要な要件:
 *   - id,a,bは必須，他のパラメータ増やすときはコンストラクタを忘れずに
 *   - versusは必須，基本的にコピペでOK
 */
struct Edge {
    //! 辺id
    int id;
    //! 端点
    int a;
    //! 端点
    int b;
    /**
     * @brief Construct a new Edge object
     * @param id 辺番号
     * @param a 辺に接続する頂点番号
     * @param b 辺に接続する頂点番号
     */
    Edge(int id = 0, int a = 0, int b = 0) : id(id), a(a), b(b) {}
    /**
     * @brief 辺における，vの対になってる頂点番号を取得する
     * @param v 頂点番号
     * @return int vじゃない方の頂点番号
     */
    inline int versus(const int v) const { return a ^ b ^ v; }
};

/**
* @brief 重み付き辺を扱う構造体の例
* @details
    辺に重みなどを加えたい場合は変数とかを増やして作る．
    Graphに使うために必要な要件:
    - id,a,bは必須，他のパラメータ増やすときはコンストラクタを忘れずに
    - versusは必須，基本的にコピペでOK
*/
template <typename COST_TYPE>
struct WeightedEdge {
    //! 辺id
    int id;
    //! 端点
    int a;
    //! 端点
    int b;
    //! 辺重み
    COST_TYPE cost;

    /**
     * @brief Construct a new Weighted Edge object
     *
     * @param id
     * @param a
     * @param b
     * @param cost
     */
    WeightedEdge(int id = 0, int a = 0, int b = 0, int cost = 0)
        : id(id), a(a), b(b), cost(cost) {}
    /**
     * @brief 辺における，vの対になってる頂点番号を取得する
     * @param v 頂点番号
     * @return int vじゃない方の頂点番号
     */
    inline int versus(const int v) const { return a ^ b ^ v; }
};
/**
 * @brief グラフクラス
 * @tparam E=Edge 新たなグラフクラス作るときは書き換える
 * @details 0-indexedで使うことしか考えてないので注意．
 */
template <typename E = Edge>
class Graph {
  private:
    //! 辺集合
    std::vector<E> edges;
    //! 隣接リスト
    std::vector<std::vector<int>> g;

  public:
    /**
     * @brief Construct a new Graph object
     * @param reserved_vertex_size 頂点数の最大値，vectorのサイズ確保用
     * @param reserved_edge_size 辺数の最大値，vectorのサイズ確保用
     */
    Graph(int reserved_vertex_size = 1, int reserved_edge_size = -1) {
        g.reserve(reserved_vertex_size);
        edges.reserve(std::max(reserved_vertex_size, reserved_edge_size));
    }

    /**
     * @brief グラフの頂点数を返す
     * @return int 頂点数
     */
    inline int size() { return g.size(); }

    /**
     * @brief vの次数を返す
     * @param v 頂点番号
     * @return int 次数
     */
    inline int degree(const int v) { return g[v].size(); }

    /**
     * @brief グラフ全体の辺の数を返す
     * @return int グラフ全体の辺の数
     */
    inline int degree() { return edges.size(); }

    /**
     * @brief
     * グラフの頂点数を変更する
     * @return int
     */
    inline void resize(const int n) { g.resize(n); }

    /**
     * @brief "無向"辺(a,b)を追加する．
     * @param a 頂点番号
     * @param b 頂点番号
     * @param params 重みとか，容量とか
     * @details paramsはemplace_backと同じノリで続けて足してけばOK
     */
    template <typename... Ts>
    inline void add_edge(int a, int b, Ts&&... params) {
        const int id = edges.size();
        if ((int)g.size() <= std::max(a, b)) {
            g.resize(std::max(a, b) + 1);
        }
        g[a].emplace_back(id);
        g[b].emplace_back(id);
        edges.emplace_back(id, a, b, std::forward<Ts>(params)...);
    }

    /**
     * @brief "無向"辺Eを追加する．
     * @details paramsはemplace_backと同じノリで続けて足してけばOK
     */


    /**
     * @brief 辺を追加 idは自動付与
     * @param e
     */
    inline void add_edge(E e) {
        e.id = edges.size();
        if ((int)g.size() <= max(e.a, e.b)) {
            g.resize(max(e.a, e.b) + 1);
        }
        g[e.a].emplace_back(e.id);
        g[e.b].emplace_back(e.id);
        edges.emplace_back(e);
    }

    /**
     * @brief "有向"辺(a,b)を追加する．
     * @param a 頂点番号
     * @param b 頂点番号
     * @param params 重みとか，容量とか
     * @details paramsはemplace_backと同じノリで続けて足してけばOK
     */
    template <typename... Ts>
    inline void add_arc(int a, int b, Ts&&... params) {
        const int id = edges.size();
        if ((int)g.size() <= std::max(a, b)) {
            g.resize(std::max(a, b) + 1);
        }
        g[a].emplace_back(id);
        edges.emplace_back(id, a, b, std::forward<Ts>(params)...);
    }

    /**
     * @brief 辺を追加 idは自動付与
     * @param e
     */
    inline void add_arc(E e) {
        e.id = edges.size();
        if ((int)g.size() <= std::max(e.a, e.b)) {
            g.resize(std::max(e.a, e.b) + 1);
        }
        g[e.a].emplace_back(e.id);
        edges.emplace_back(e);
    }

    /**
     * @brief vの隣接頂点を返す
     * @param v int
     * @return vector<int>
     */
    inline std::vector<int> Ns(const int v) {
        std::vector<int> ns(g[v].size());
        for (int i = 0; i < degree(v); i++) {
            ns[i] = edges[g[v][i]].versus(v);
        }
        return ns;
    }

    /**
     * @brief vに隣接する辺番号の集合を返す
     * @param v int 頂点番号
     * @return vector<int> 辺番号の集合
     */
    inline const std::vector<int>& operator[](const int v) { return g[v]; }

    /**
     * @brief 辺番号から辺の参照を取得する
     * @param edge_id
     * @return E&
     */
    inline E& i2e(const int edge_id) { return edges[edge_id]; }
};