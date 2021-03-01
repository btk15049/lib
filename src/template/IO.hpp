/**
 * @file IO.hpp
 * @author btk
 * @brief cin高速化とか，出力の小数桁固定とか
 * @version 0.2
 * @date 2021-03-01
 *
 * @copyright Copyright (c) 2021
 */

/*<head>*/
#pragma once
#include <iomanip>
#include <iostream>
#include <vector>
/*</head>*/

/**
 * @brief 入出力の設定を行うための構造体
 */

namespace io {
    inline void enableFastIO() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(0);
    }
    inline void setDigits(int digits) {
        std::cout << std::fixed;
        std::cout << std::setprecision(digits);
    }
} // namespace io

/**
 * @brief
 * vectorに直接cin流すためのやつ
 * @tparam T
 * @param is
 * @param v
 * @return istream&
 */
template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    for (auto& it : v) is >> it;
    return is;
}
