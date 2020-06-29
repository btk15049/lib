/**
 * @file STLExtension.hpp
 * @brief STL独自拡張
 */
/*<head>*/
#pragma once
#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>
/*</head>*/

namespace ext {
    /**
     * @brief std::sortのWrapper関数
     * @tparam Container std::vectorやstd::listを想定
     * @param container ソートしたいコンテナオブジェクト
     * @return Container&
     * ソート後のコンテナオブジェクト==引数に渡したオブジェクト
     */
    template <typename Container>
    inline Container& sort(Container& container) {
        sort(std::begin(container), std::end(container));
        return container;
    }

    /**
     * @brief std::sortのWrapper関数
     * @tparam Container std::vectorやstd::listを想定
     * @tparam Comparator 比較関数の型
     * @param container ソートしたいコンテナオブジェクト
     * @param comparator 比較関数
     * @return Container&
     * ソート後のコンテナオブジェクト==引数に渡したオブジェクト
     */
    template <typename Container, typename Comparator>
    inline Container& sort(Container& container, Comparator comparator) {
        sort(std::begin(container), std::end(container), comparator);
        return container;
    }

    /**
     * @brief std::reverseのWrapper関数
     * @tparam Container std::vectorやstd::listを想定
     * @param container 反転したいコンテナオブジェクト
     * @return Container&
     * 反転後のコンテナオブジェクト==引数に渡したオブジェクト
     */
    template <typename Container>
    inline Container& reverse(Container& container) {
        reverse(std::begin(container), std::end(container));
        return container;
    }

    /**
     * @brief std::accumulateのvector限定Wrapper関数
     * @tparam T 配列の要素の型
     * @tparam U 戻り値の型
     * @param container 配列
     * @param zero 初期値
     * @return U 総和
     */
    template <typename T, typename U>
    inline U accumulate(const std::vector<T>& container, U zero) {
        return std::accumulate(std::begin(container), std::end(container),
                               zero);
    }

    /**
     * @brief std::accumulateのvector限定Wrapper関数の、引数省略版
     * @tparam T 配列の要素の型 && 戻り値の型
     * @param container 配列
     * @return T 総和 overflowに注意
     */
    template <typename T>
    inline T accumulate(const std::vector<T>& container) {
        return accumulate(container, T(0));
    }

    /**
     * @brief std::countのWrapper関数
     * @tparam Container std::vectorやstd::listを想定
     * @tparam T 数える値の型
     * @param container コンテナオブジェクト
     * @param value 数える値
     * @return int
     */
    template <typename Container, typename T>
    inline int count(Container& container, T value) {
        return std::count(std::begin(container), std::end(container), value);
    }

} // namespace ext
