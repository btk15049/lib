/**
 * @file ChainOperation.hpp
 * @author btk
 * @brief パラメータパックを利用した演算子結合を実現
 */

/**
 * @brief テンプレート再帰の末尾
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
 * @tparam F
 * @tparam T
 * @tparam Ts
 * @param head
 * @param tail
 * @return T
 */
template <typename F, typename T, typename... Ts>
inline auto chain(const T head, Ts&&... tail) {
    return F::exec(head, chain<F>(tail...));
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
