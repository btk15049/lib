/**
 * @file STLExtension.hpp
 * @brief STL独自拡張
 */
/*<head>*/
#pragma once
#include <algorithm>
#include <iterator>
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

} // namespace ext