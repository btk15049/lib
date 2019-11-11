/**
 * @file GraphUtil.hpp
 * @author btk
 * @brief Graphクラスを使ったライブラリ(dijkstraなど)を管理
 * @date 2019-05-26
 * @copyright Copyright (c) 2019
 */

/*<head>*/
#pragma once
#include "graph/Graph.hpp"
#include "template/MinMaxOperation.hpp"
/*</head>*/

#include <queue>

/**
 * @brief
 * 通常のダイクストラ
 * @tparam T 重み付き辺構造体 .costをメンバにもつ必要あり
 * @tparam U コストの型
 * @param g グラフ
 * @param inf 流量のinf
 * @param s 始点
 * @return std::vector<int>
 */
template <typename T, typename U>
std::vector<U> dijkstra(Graph<T>& g, U inf, const int s = 0) {
    //! TODO interval heapを使う
    std::priority_queue<std::pair<U, int>> que;
    std::vector<U> d(g.size(), inf);

    // init
    d[s] = U();
    que.push(std::make_pair(-U(), s));

    while (!que.empty()) {
        const int v       = que.top().second;
        const U c = -que.top().first;
        que.pop();
        if (d[v] < c) continue;
        for (const int eid : g[v]) {
            T& e        = g.i2e(eid);
            const int u = e.versus(v);
            if (chmin(d[u], c + e.cost)) {
                que.push(std::make_pair(-(c + e.cost), u));
            }
        }
    }
    return d;
}