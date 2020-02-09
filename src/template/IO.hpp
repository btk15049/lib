/**
 * @file IO.hpp
 * @author btk
 * @brief cin高速化とか，出力の小数桁固定とか
 * @version 0.1
 * @date 2019-07-13
 *
 * @copyright Copyright (c) 2019
 */

/*<head>*/
#pragma once
#include "template/Macro.hpp"
#include <iomanip>
#include <iostream>
#include <vector>
/*</head>*/

/**
 * @brief 入出力の設定を行うための構造体
 */
struct cww {
    /**
     * @brief Construct a new cww::cww object
     * @details
     * CIN_ONLYを定義すると，submit時にcinとscanfの同期を切る設定が走る
     * DECIMAL_DIGITSを定義すると，doubleの出力時指定した桁数分小数部を吐くようになる
     */
    cww() {
#ifdef FAST_IO
        std::ios::sync_with_stdio(false);
        std::cin.tie(0);
#endif
#ifdef DECIMAL_DIGITS
        std::cout << std::fixed;
        std::cout << std::setprecision(DECIMAL_DIGITS);
#endif
    }
};

//! 入出力設定構造体を実体化
cww star;

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
