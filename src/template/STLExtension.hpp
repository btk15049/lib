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
    template <typename Container>
    Container& sort(Container& container) {
        sort(std::begin(container), std::end(container));
        return container;
    }

    template <typename Container>
    Container& reverse(Container& container) {
        reverse(std::begin(container), std::end(container));
        return container;
    }

} // namespace ext