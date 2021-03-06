/**
 * @file RollingHash.hpp
 * @brief ローリングハッシュ
 * @author btk15049
 * @date 2019/03/08
 * @details
 *  verify: CSA12E，RUPC day3 E
 */

/*<head>*/
#pragma once
#include "template/Macro.hpp"
/*</head>*/

#include <ostream>
#include <string>
#include <vector>

/**
 * @brief ローリングハッシュ
 * @details
 * ハッシュされている文字列のハッシュ値とポテンシャル（長さ）を管理．
 */
template <int base = 90001, int mod = 999999937>
class RollingHash {
  public:
    //! 文字列のハッシュ値
    long long hash;
    //! ハッシュ化されている文字列長をnとすると，base^n %mod
    long long potential;

    /**
     * @brief コンストラクタ
     * @details 引数無しで呼び出しは，空文字列のハッシュ化に相当する。
     */
    RollingHash(long long hash = 0, long long potential = 1)
        : hash(hash % mod), potential(potential) {}

    /**
     * @brief concatenation
     * @details
     *   ハッシュ値の合成を行う．ハッシュ化前の文字列を接続する操作にあたる．
     *   hash(s)+hash(t) == hash(s+t)
     */
    inline RollingHash operator+(const RollingHash o) const {
        return RollingHash((hash * o.potential + o.hash) % mod,
                           potential * o.potential % mod);
    }

    /**
     * @brief ハッシュ値の等価判定
     */
    inline bool operator==(const RollingHash o) const {
        return hash == o.hash && potential == o.potential;
    }

    /**
     * @brief 文字列をハッシュ化した配列を管理するクラス．
     */
    class Table {
      private:
        //! str[i] := hash(s[0,i))
        std::vector<RollingHash> str;

      public:
        /**
         * @brief デフォルトコンストラクタ
         */
        Table() {}
        /**
         * @brief コンストラクタ
         * @details O(n)でhash(s[0,i))を全部求める．
         */
        Table(const std::string s) {
            const int n = s.size();
            str.resize(n + 1);
            for (int i = 0; i < n; i++) {
                str[i + 1] = str[i] + RollingHash(s[i], base);
            }
        }

        /**
         * @brief 部分文字列のハッシュ値を取り出す
         * @details
         *   ハッシュ値の合成を行う．ハッシュ化前の文字列を接続する操作にあたる．
         *   hashtable(s).substr(lb,ub) == hash(s[lb,ub))
         */
        RollingHash substr(int lb, int ub) {
            return RollingHash(str[ub].hash
                                   - str[lb].hash * str[ub - lb].potential % mod
                                   + mod,
                               str[ub - lb].potential);
        }
    };
};

template <int i, int j>
std::ostream& operator<<(std::ostream& os, const RollingHash<i, j>& rh) {
    os << "RollingHash";
    os << "<";
    os << "base=" << i << ", ";
    os << "mod=" << j;
    os << ">";
    os << "(";
    os << "p=" << rh.potential << ", ";
    os << "h=" << rh.hash;
    os << ")";
    return os;
}
