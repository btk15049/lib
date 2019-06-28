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
/*</head>*/

namespace _GraphUtil_ {

    /**
     * @brief
     * 通常のダイクストラ
     * @tparam E 重み付き辺構造体　.costをメンバにもつ必要あり
     * @tparam COST_TYPE コストの型
     * @param g グラフ
     * @param inf 流量のinf
     * @param s 始点
     * @return vector<int>
     */
    template <typename E, typename COST_TYPE>
    vector<COST_TYPE> dijkstra(Graph<E>& g, COST_TYPE inf, const int s = 0) {
        //! TODO interval heapを使う
        priority_queue<pair<COST_TYPE, int>> que;
        vector<COST_TYPE> d(g.size(), inf);

        // init
        d[s] = 0;
        que.push(make_pair((COST_TYPE)0, s));

        while (!que.empty()) {
            const int v       = que.top().second;
            const COST_TYPE c = -que.top().first;
            que.pop();
            if (d[v] < c) continue;
            for (const int eid : g[v]) {
                E& e        = g.i2e(eid);
                const int u = e.versus(v);
                if (chmin(d[u], c + e.cost)) {
                    que.push(make_pair(-(c + e.cost), u));
                }
            }
        }
        return d;
    }
} // namespace _GraphUtil_
using namespace _GraphUtil_;