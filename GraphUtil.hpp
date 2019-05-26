/**
 * @file GraphUtil.hpp
 * @author btk
 * @brief Graphクラスを使ったライブラリ(dijkstraなど)を管理
 * @date 2019-05-26
 * @copyright Copyright (c) 2019
 */

/*<head>*/
#pragma once
#include "Graph.hpp"
/*</head>*/

template <typename E, typename COST_TYPE>
vector<int> dijkstra(Graph<E> &g, const int s = 0) {
    //! TODO interval heapを使う
    priority_queue<pair<COST_TYPE, int>> que;
    vector<COST_TYPE> d;

    // init
    que.push(make_pair((COST_TYPE)0, s));

    while (!que.empty()) {
        const int v       = que.top().second;
        const COST_TYPE c = que.top().first;
        que.pop();
        if (d[v]<
    }

    return d;
}