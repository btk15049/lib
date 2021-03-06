/*<head>*/
#pragma once
/*</head>*/

#include <utility>
#include <cstdint>

/**
 * @file ModInt.hpp
 * @brief mod構造体
 * @author btk15049
 * @date 2019/03/08
 * @details
 *  \todo verifyが足りない
 *  verify: CSA12E，RUPC day3 F
 */

//! [WARNING!] mod が入力で与えられる場合はconstexprを外す
#ifdef STATIC_MOD
constexpr int mod = STATIC_MOD;
#else
int mod;
#endif

/**
 * @brief mod構造体
 * @details
 * 整数をラップして，常に保持されているデータがmodされた状態になるよう管理．
 */
class ModInt {
  private:
    //! 中身
    int x;

  public:
    /**
     * @brief ゲッター
     * @details 出力時などは "cout << *ret << endl;"のようにやるとよい．
     */
    int64_t operator*() const { return x; }
    /**
     * @brief デフォルトコンストラクタ．0で初期化される．
     */
    ModInt() { x = 0; }

    /**
     * @brief intからのコンストラクタ
     * @param[in] y 設定したい値
     * @details
     * modをとらないので高速．ただしmodより大きい値や負の数を入れると事故るので注意．
     */
    ModInt(const int y) { x = y; }

    /**
     * @brief int64_tからのコンストラクタ
     * @param[in] y 設定したい値
     * @details 毎回modを取るので低速．
     */
    ModInt(const int64_t y) { x = (int)((mod + y % mod) % mod); }

    /**
     * @brief ModIntからの代入演算子
     * @param[in] o 設定したい値
     * @details 高速
     */
    ModInt(const ModInt& o) { this->x = *o; }
    /**
     * @brief 整数から高速にModIntを作りたいときに使う
     * @param[in] x 設定したい値
     * @details xが[0,mod)であることが保証されてないと正しく動かない．
     */
    static inline ModInt raw(const int64_t x) {
        // assert(x<mod);
        return ModInt((int)x);
    }

    /**
     * @brief 整数から安全にModIntを作りたいときに使う
     * @param[in] x 設定したい値
     * @details mod2回取るから遅い．負数でもOK．
     */
    static inline ModInt get(const int64_t x) { return ModInt(x); }

    /**
     * @brief intからの代入演算子
     * @param[in] o 設定したい値
     * @details
     * modをとらないので高速．ただしmodより大きい値や負の数を入れると事故るので注意．
     */
    ModInt& operator=(const int o) {
        this->x = o >= mod ? o - mod : o;
        return *this;
    }

    /**
     * @brief int64_tからの代入演算子
     * @param[in] o 設定したい値
     * @details mod2回取るから遅い．負数でもOK．
     */
    ModInt& operator=(const int64_t o) {
        this->x = (int)((mod + o % mod) % mod);
        return *this;
    }

    /**
     * @brief ModIntからの代入演算子
     * @param[in] o 設定したい値
     * @details 高速
     */
    ModInt& operator=(const ModInt o) {
        this->x = *o;
        return *this;
    }
};

/**
 * @param[in] l ModInt
 * @param[in] r ModInt
 * @details if文使って少し高速化．
 */
inline ModInt add(const ModInt l, const ModInt r) {
    const int64_t x = *l + *r;
    return ModInt::raw(x >= mod ? x - mod : x);
}

/**
 * @param[in] l ModInt
 * @param[in] r ModInt．
 */
inline ModInt mul(const ModInt l, const ModInt r) {
    return ModInt::raw(*l * *r % mod);
}

/**
 * @brief a^x %modを求める
 * @param[in] a ModInt
 * @param[in] x int64_t．
 */
inline ModInt pow(ModInt a, int64_t x) {
    ModInt ret = ModInt::raw(1);
    while (x) {
        if (x & 1) {
            ret = mul(ret, a);
        }
        a = mul(a, a);
        x >>= 1;
    }
    return ret;
}

/**
 * @brief x^-1 %modを求める
 * @param[in] x ModInt．
 * @details
 *   内部ではユークリッドの拡張互助法を使っている．
 *   O(log(mod))
 */
inline ModInt inv(const ModInt x) {
    int64_t a = *x, b = mod, u = 1, v = 0;
    while (b) {
        int64_t t = a / b;
        std::swap(a -= t * b, b);
        std::swap(u -= t * v, v);
    }
    return ModInt::get(u);
}

/**
 * @brief 負数を求める単項演算子
 * @param[in] x ModInt
 */
inline ModInt operator-(const ModInt x) { return add(mod, -*x); }

/**
 * @param[in] l ModInt
 * @param[in] r ModInt
 */
inline ModInt operator+(const ModInt l, const ModInt r) { return add(l, r); }

/**
 * @param[in] l ModInt
 * @param[in] r ModInt
 */
inline ModInt operator*(const ModInt l, const ModInt r) { return mul(l, r); }

/**
 * @param[in] l ModInt
 * @param[in] r ModInt
 */
inline ModInt operator-(const ModInt l, const ModInt r) { return add(l, -r); }

/**
 * @param[in] l ModInt
 * @param[in] r int
 * @details
 * 右辺は定数を想定しているのでmodをとらないrawを使ってModIntに変換している．ただしmodより大きい値や負の数を入れると事故るので注意．
 */
inline ModInt operator+(const ModInt l, const int r) {
    return add(l, ModInt::raw(r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 */
inline ModInt operator+(const ModInt l, const int64_t r) {
    return add(l, ModInt::get(r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 * @details
 * 右辺は定数を想定しているのでmodをとらないrawを使ってModIntに変換している．ただしmodより大きい値や負の数を入れると事故るので注意．
 */
inline ModInt operator*(const ModInt l, const int r) {
    return mul(l, ModInt::raw(r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 */
inline ModInt operator*(const ModInt l, const int64_t r) {
    return mul(l, ModInt::get(r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 * @details
 * 右辺は定数を想定しているのでmodをとらないrawを使ってModIntに変換している．ただしmodより大きい値や負の数を入れると事故るので注意．
 */
inline ModInt operator-(const ModInt l, const int r) {
    return add(l, ModInt::raw(mod - r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 */
inline ModInt operator-(const ModInt l, const int64_t r) {
    return add(l, -ModInt::get(r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 * @details
 * 右辺は定数を想定しているのでmodをとらないrawを使ってModIntに変換している．ただしmodより大きい値や負の数を入れると事故るので注意．
 */
inline ModInt operator/(const ModInt l, const int r) {
    return mul(l, inv(ModInt::raw(r)));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 */
inline ModInt operator/(const ModInt l, const int64_t r) {
    return mul(l, inv(ModInt::get(r)));
}

/**
* @param[in] l ModInt
* @param[in] r int64_t
* @details
*   pow(l,r)を呼び出すだけなのでpowを参照のこと．
    計算量はO(log mod)
*/
inline ModInt operator^(const ModInt l, const int64_t r) { return pow(l, r); }

/**
 * @brief
 * +=の実装、各operator+を呼ぶだけ
 * @tparam T
 * @param l ModInt
 * @param r 足すやつ
 * @return ModInt&
 */
template <typename T>
ModInt& operator+=(ModInt& l, T r) {
    l = l + r;
    return l;
}

/**
 * @brief
 * -=の実装、各operator-を呼ぶだけ
 * @tparam T
 * @param l ModInt
 * @param r 引くやつ
 * @return ModInt&
 */
template <typename T>
ModInt& operator-=(ModInt& l, T r) {
    l = l - r;
    return l;
}

/**
 * @brief
 * *=の実装、各operator*を呼ぶだけ
 * @tparam T
 * @param l ModInt
 * @param r かけるやつ
 * @return ModInt&
 */
template <typename T>
ModInt& operator*=(ModInt& l, T r) {
    l = l * r;
    return l;
}

/**
 * @namespace factorial
 * @brief 順列数関連の関数のまとめ
 * @details
 *   - combination
 *   - permutation
 *   - multiChoose
 */
namespace factorial {
    //! 順列数を格納する配列のサイズ
    constexpr int size =
#ifdef FACTORIAL_SIZE
        FACTORIAL_SIZE;
#else
        3123456;
#endif
    //! 前計算ができているかどうかのフラグ
    bool is_build = false;

    //! 順列数を格納する配列
    ModInt factorial[size];
    //! (順列数)^-1を格納する配列
    ModInt inverse_factorial[size];

    /**
     * @brief 順列数の前計算
     * @details
     *   順列数と，その逆元を[0,size)まで求める.
     *   計算量は，O(size + log(mod))
     */
    void build() {
        is_build     = true;
        factorial[0] = 1;
        for (int i = 1; i < size; i++) {
            factorial[i] = factorial[i - 1] * i;
        }
        inverse_factorial[size - 1] = inv(factorial[size - 1]);
        for (int i = size - 1; i >= 1; i--) {
            inverse_factorial[i - 1] = inverse_factorial[i] * i;
        }
    }

    /**
     * @brief nPkを求める
     * @details
     *   前計算がしてあれば O(1)．前計算してない場合は is_build
     * を読み取って前計算をする．
     */
    inline ModInt permutation(int n, int k) {
        if (k < 0 || k > n) return ModInt::raw(0);
        if (!is_build) build();
        return factorial[n] * inverse_factorial[n - k];
    }

    /**
     * @brief nCkを求める
     * @details
     *   前計算がしてあれば O(1)．前計算してない場合は is_build
     * を読み取って前計算をする．
     */
    inline ModInt combination(int n, int k) {
        if (k < 0 || k > n) return ModInt::raw(0);
        if (!is_build) build();
        return factorial[n] * inverse_factorial[k] * inverse_factorial[n - k];
    }

    /**
     * @brief 重複組合せ
     * @param n 何種類のものを (仕切りがn-1個)
     * @param r いくつ並べるか
     * @return ModInt nHr
     */
    ModInt multiChoose(int n, int r) {
        if (n == 0 && r == 0)return ModInt::raw(1);
        return combination(n + r - 1, r);
    }

        /**
     * @brief 上限付き重複組合せ
     * @details 包除原理を用いて，lim個以上の品物が1,2,...,i種類の場合を足したり引いたりしていく
     * 計算量は O(min(n, r / lim))
     * @param n 何種類のものを
     * @param r いくつ並べるか
     * @param lim 1種類のものを選べる上限
     * @return ModInt
     */
    ModInt multiChoose(int n, int r, int lim) {
        ModInt ret = 0;
        for (int i = 0; i <=n;i++) {
            if (i * (lim + 1) > r) break;
            ret += ((i & 1) ? mod - 1 : 1) * combination(n, i)
                   * multiChoose(n, r - i * (lim + 1));
        }
        return ret;
    }

} // namespace factorial