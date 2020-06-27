/**
 * @file MinMaxOperation.hpp
 * @author btk
 * @brief 最大値とか最小値を求める
 * @version 0.1
 * @date 2019-07-04
 *
 * @copyright Copyright (c) 2019
 *
 */
/*<head>*/
#pragma once
/*</head>*/

/**
 * @brief 2項の最小値求める
 *
 * @tparam T
 */
template <typename T>
struct minFunc {
    /**
     * @brief 本体
     *
     * @param l
     * @param r
     * @return T
     */
    static T exec(const T l, const T r) { return l < r ? l : r; }
};

/**
 * @brief 2項の最大値求める
 *
 * @tparam T
 */
template <typename T>
struct maxFunc {
    /**
     * @brief 本体
     *
     * @param l
     * @param r
     * @return T
     */
    static T exec(const T l, const T r) { return l > r ? l : r; }
};

/**
 * @brief テンプレート再帰の末尾
 *
 * @tparam F 二項演算
 * @tparam T
 * @param v
 * @return T
 */
template <typename F, typename T>
inline T chain(T&& v) {
    return v;
}

/**
 * @brief 複数項における演算の結果を返す
 *
 * @tparam F
 * @tparam T
 * @tparam Ts
 * @param head
 * @param tail
 * @return T
 */
template <typename F, typename T, typename... Ts>
inline T chain(const T head, Ts&&... tail) {
    return F::exec(head, chain<F>(tail...));
}

/**
 * @brief 複数項の最小値
 * @see chain
 * @tparam T
 * @tparam Ts
 * @param head
 * @param tail
 * @return T
 */
template <typename T, typename... Ts>
inline T minOf(T head, Ts... tail) {
    return chain<minFunc<T>>(head, tail...);
}

/**
 * @brief 複数項の最大値
 * @see chain
 * @tparam T
 * @tparam Ts
 * @param head
 * @param tail
 * @return T
 */
template <typename T, typename... Ts>
inline T maxOf(T head, Ts... tail) {
    return chain<maxFunc<T>>(head, tail...);
}

/**
 * @brief
 * 先頭の値をFで参照する関数に基づいて変更できたらする
 * @tparam F
 * @tparam T
 * @tparam Ts
 * @param target
 * @param candidates
 * @return true
 * @return false
 */
template <typename F, typename T, typename... Ts>
inline bool changeTarget(T& target, Ts&&... candidates) {
    const T old = target;
    target      = chain<F>(target, candidates...);
    return old != target;
}

/**
 * @brief change min
 * @tparam T 型
 * @param target 変更する値
 * @param candidates
 * @return 更新があればtrue
 */
template <typename T, typename... Ts>
inline bool chmin(T& target, Ts&&... candidates) {
    return changeTarget<minFunc<T>>(target, candidates...);
}

/**
 * @brief chminのmax版
 * @see chmin
 *  @tparam T 型
 * @param target 変更する値
 * @param candidates
 * @return 更新があればtrue
 */
template <typename T, typename... Ts>
inline bool chmax(T& target, Ts&&... candidates) {
    return changeTarget<maxFunc<T>>(target, candidates...);
}
