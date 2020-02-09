/*<head>*/
#pragma once
#include <cstdint>
/*</head>*/

/**
 * @brief gcd, ceil等自作算数用関数を集める。stdと被るので名前空間を区切る
 */
namespace math {

    /**
     * @brief aとｂの最大公約数
     * @param a int64
     * @param b int64
     * @return int64 最大公約数
     */
    int64_t gcd(int64_t a, int64_t b) { return (b == 0) ? a : gcd(b, a % b); }

    /**
     * @brief aとｂの最小公倍数
     * @param a int64
     * @param b int64
     * @return int64 最小公倍数
     */
    int64_t lcm(int64_t a, int64_t b) { return (a / gcd(a, b)) * b; }


    /**
     * @brief 拡張ユークリッド互除法
     * @details ax + by = gとなるx,yを求める
     * @param a 入力
     * @param b 入力
     * @param x 値引き継ぎ用の変数
     * @param y 値引き継ぎ用の変数
     * @return int64_t g:aとbの最大公約数
     */
    int64_t extgcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
        int64_t g = a;
        x         = 1;
        y         = 0;
        if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
        return g;
    }

    /**
     * @brief u/dを切り上げした整数を求める
     * @todo 負の数への対応
     * @tparam T 整数型
     * @param u 入力
     * @param d 入力
     * @return T 切り上げ後の値
     */
    template <typename T>
    inline T ceil(T u, T d) {
        return (u + d - (T)1) / d;
    }

} // namespace math