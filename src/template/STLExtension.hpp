/**
 * @file STLExtension.hpp
 * @brief STL独自拡張
 */
/*<head>*/
#pragma once
#include <algorithm>
#include <iterator>
#include <numeric>
#include <type_traits>
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

    /**
     * @brief 等差数列のvectorを作る関数
     * @param n 要素数
     * @param startFrom 初項
     * @param step 公差
     * @return std::vector<int> 等差数列
     */
    inline std::vector<int> iota(int n, int startFrom = 0, int step = 1) {
        std::vector<int> container(n);
        int v = startFrom;
        for (int i = 0; i < n; i++, v += step) {
            container[i] = v;
        }
        return container;
    }

    /**
     * @brief
     * (*max_element) のwrapper、位置は返さない
     * @tparam ITR iterator
     * @param l iteratorの最初
     * @param r iteratorの終了位置
     * @param defaultValue 要素がないときのデフォルト値
     * @return auto 最大値、型はコンテナ内の型
     */
    template <typename ITR>
    inline auto maxIn(ITR l, ITR r,
                      std::remove_reference_t<decltype(*l)> defaultValue = 0) {
        if (r == l) {
            return defaultValue;
        }
        return *std::max_element(l, r);
    }


    /**
     * @brief maxIn の vector 限定版
     * @tparam T 戻り値の型
     * @param containter 最大値求める対象のコンテナ
     * @param defaultValue コンテナの要素がない場合の初期値
     * @return T 最大値、コンテナ似要素がない場合はdefaultValue
     */
    template <typename T>
    inline T maxIn(std::vector<T> container, T defaultValue = 0) {
        return maxIn(container.begin(), container.end(), defaultValue);
    }

    /**
     * @brief
     * (*min_element) のwrapper、位置は返さない
     * @tparam ITR iterator
     * @param l iteratorの最初
     * @param r iteratorの終了位置
     * @param defaultValue 要素がないときのデフォルト値
     * @return auto 最小値、型はコンテナ内の型
     */
    template <typename ITR>
    inline auto minIn(ITR l, ITR r,
                      std::remove_reference_t<decltype(*l)> defaultValue = 0) {
        if (r == l) {
            return defaultValue;
        }
        return *std::min_element(l, r);
    }

    /**
     * @brief minIn の vector 限定版
     * @tparam T 戻り値の型
     * @param containter 最大値求める対象のコンテナ
     * @param defaultValue コンテナの要素がない場合の初期値
     * @return T 最小値、コンテナ似要素がない場合はdefaultValue
     */
    template <typename T>
    inline T minIn(std::vector<T> container, T defaultValue = 0) {
        return minIn(container.begin(), container.end(), defaultValue);
    }

} // namespace ext
