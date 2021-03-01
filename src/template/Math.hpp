/**
 * @file Math.hpp
 * @author btk
 * @brief 最大値とか最小値を求める
 */
/*<head>*/
#pragma once
#include "template/ChainOperation.hpp"
#include <cstdint>
#include <optional>
/*</head>*/

/**
 * @brief gcd, ceil等自作算数用関数を集める。stdと被るので名前空間を区切る
 */
namespace math {

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
     * @brief 一次不定方程式の解
     * @details 値の説明は betouzEquation 関数を参照のこと
     */
    struct BetouzSolution {
        int64_t x, y, dx, dy;
    };


    /**
     * @brief 一次不定方程式
     * @details a(x + k*dx) + b(y -k*dy) = cとなる x, y, dx, dy を求める。
     * @param a 入力
     * @param b 入力
     * @param c 入力
     * @return int64_t 解がないときは nullopt が返る
     */
    std::optional<BetouzSolution> betouzEquation(int64_t a, int64_t b,
                                                 int64_t c) {
        BetouzSolution sol;
        const int64_t g = extgcd(a, b, sol.x, sol.y);
        if (c % g == 0) {
            return std::nullopt;
        }
        sol.dx = b / g;
        sol.dy = a / g;
        sol.x *= c / g;
        sol.y *= c / g;
        return sol;
    }

    namespace inner {
        /**
         * @brief 2項のgcdを求める
         * @tparam T
         */
        template <typename T>
        struct GCDFunc {
            /**
             * @brief 本体
             * @param l
             * @param r
             * @return T
             */
            static inline T exec(T l, T r) {
                while (r != 0) {
                    T u = l % r;
                    l   = r;
                    r   = u;
                }
                return l;
            }
        };

        /**
         * @brief 2項のgcdを求める
         * @tparam T
         */
        template <typename T>
        struct LCMFunc {
            /**
             * @brief 本体
             * @param l
             * @param r
             * @return T
             */
            static inline T exec(T l, T r) {
                return (l / GCDFunc<T>::exec(l, r)) * r;
            }
        };

    } // namespace inner

    /**
     * @brief valuesの最大公約数
     * @tparam Ts パラメータパック
     * @param values gcdを求めたい値の集合（2個以上）
     * @return int64 最大公約数
     */
    template <typename... Ts>
    inline int64_t gcd(Ts &&...values) {
        return chain<inner::GCDFunc<int64_t>>(values...);
    }

    /**
     * @brief valuesの最小公倍数
     * @tparam Ts パラメータパック
     * @param values lcmを求めたい値の集合（2個以上）
     * @return int64 最小公倍数
     */
    template <typename... Ts>
    inline int64_t lcm(Ts &&...values) {
        return chain<inner::LCMFunc<int64_t>>(values...);
    }

    /**
     * @brief iterator で指定された集合のlcmを求める
     * @tparam ITR iterator
     * @param l 開始位置
     * @param r 終了位置
     * @return int64_t lcm
     */
    template <typename ITR>
    inline int64_t lcmAll(ITR l, ITR r) {
        int64_t ret = 1;
        for (auto it = l; it != r; ++it) {
            ret = lcm(ret, *it);
        }
        return ret;
    }

    /**
     * @brief container (配列など) で指定された要素のlcmを求める
     * @tparam Container vectorやlist
     * @param container コンテナ
     * @return int64_t lcm
     */
    template <typename Container>
    inline int64_t lcmAll(Container container) {
        int64_t ret = 1;
        for (auto e : container) {
            ret = lcm(ret, e);
        }
        return ret;
    }

    /**
     * @brief iterator で指定された集合のgcdを求める
     * @tparam ITR iterator
     * @param l 開始位置
     * @param r 終了位置
     * @return int64_t lcm
     */
    template <typename ITR>
    inline int64_t gcdAll(ITR l, ITR r) {
        int64_t ret = 0;
        for (auto it = l; it != r; ++it) {
            ret = gcd(ret, *it);
        }
        return ret;
    }

    /**
     * @brief container (配列など) で指定された要素のgcdを求める
     * @tparam Container vectorやlist
     * @param container コンテナ
     * @return int64_t gcd
     */
    template <typename Container>
    inline int64_t gcdAll(Container container) {
        int64_t ret = 0;
        for (auto e : container) {
            ret = gcd(ret, e);
        }
        return ret;
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

/**
 * @brief 2項の最小値求める
 * @tparam T
 */
template <typename T>
struct minFunc {
    /**
     * @brief 本体
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
 * @brief change min
 * @tparam T 型
 * @param target 変更する値
 * @param candidates
 * @return 更新があればtrue
 */
template <typename T, typename... Ts>
inline bool chmin(T &target, Ts &&...candidates) {
    return changeTarget<minFunc<T>>(target, candidates...);
}

/**
 * @brief chminのmax版
 * @see chmin
 * @tparam T 型
 * @param target 変更する値
 * @param candidates
 * @return 更新があればtrue
 */
template <typename T, typename... Ts>
inline bool chmax(T &target, Ts &&...candidates) {
    return changeTarget<maxFunc<T>>(target, candidates...);
}
