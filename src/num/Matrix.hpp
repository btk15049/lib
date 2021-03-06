/**
 * @file Matrix.hpp
 * @author btk
 * @brief 行列累乗
 * @version 0.1
 * @date 2019-06-10
 *
 * @copyright Copyright (c) 2019
 *
 */

/*<head>*/
#pragma once
#include "template/Loop.hpp"
#include <algorithm>
#include <array>
/*</head>*/

/**
 * @brief
 * 行列クラス
 * @tparam T
 * @tparam row_size 縦
 * @tparam col_size 横
 * @details
 * 速度が気になるようであればバッファ管理はarrayからNDRangeに変えるかも
 */
template <typename T, size_t row_size, size_t col_size>
class Matrix {
  public:
    //! 行サイズを4の倍数に
    static constexpr int fixed_col_size = ((col_size + 3) / 4) * 4;
    //! 列サイズを4の倍数に
    static constexpr int fixed_row_size = ((row_size + 3) / 4) * 4;
    //! 行ベクトル 横
    using col_array = std::array<T, fixed_col_size>;
    //! 列ベクトル 縦
    using row_array = std::array<T, fixed_row_size>;
    //! 行列
    using matrix = std::array<col_array, fixed_row_size>;

  private:
    //! 本体
    matrix value;

  public:
    /**
     * @brief
     * idx行目の行ベクトルの参照を取得
     * @param idx
     * @return col_array&
     */
    inline col_array& operator[](const int idx) { return value[idx]; }

    /**
     * @brief
     * idx行目の行ベクトルのconst参照を取得
     * @param idx
     * @return col_array&
     */
    inline const col_array& operator[](const int idx) const {
        return value[idx];
    }


    /**
     * @brief Construct a new Matrix object
     */
    Matrix() {}

    /**
     * @brief ディープコピーをします
     * @param o
     * @return Matrix& コピー後のインスタンス
     */
    inline Matrix& operator=(const Matrix& o) {
        for (int i = 0; i < fixed_row_size; i++) value[i] = o[i];
        return *this;
    }

    /**
     * @brief コピーコンストラクタ
     * @param o
     */
    Matrix(const Matrix& o) {
        for (int i = 0; i < fixed_row_size; i++) {
            for (int j = 0; j < fixed_col_size; j++) {
                value[i][j] = o[i][j];
            }
        }
    }
};

/**
 * @brief
 * 行列積
 * @tparam T
 * @tparam r1
 * @tparam c1
 * @tparam c2
 * @param in1
 * @param in2
 * @param out
 */
template <typename T, size_t r1, size_t c1, size_t c2>
void mul(Matrix<T, r1, c1>& in1, Matrix<T, c1, c2>& in2,
         Matrix<T, r1, c2>& out) {
    for (int i : range(r1)) {
        for (int j : range(c2)) {
            out[i][j] = 0;
        }
    }
    T sum[4], tmp;
    for (int k : range(c1)) {
        for (size_t i = 0; i < r1; i += 4) {
            sum[0] = in1[i][k];
            sum[1] = in1[i + 1][k];
            sum[2] = in1[i + 2][k];
            sum[3] = in1[i + 3][k];
            for (int j : range(c2)) {
                tmp = in2[k][j];
                out[i + 0][j] += sum[0] * tmp;
                out[i + 1][j] += sum[1] * tmp;
                out[i + 2][j] += sum[2] * tmp;
                out[i + 3][j] += sum[3] * tmp;
            }
        }
    }
}

/**
 * @brief
 * 行列とベクトルの積
 * @tparam T
 * @tparam r
 * @tparam c
 * @param m
 * @param in
 * @param out
 */
template <typename T, size_t r, size_t c>
inline void mul(Matrix<T, r, c> m, std::array<T, c> in, std::array<T, r>& out) {
    for (int i : range(r)) {
        out[i] = 0;
        for (int j : range(c)) {
            out[i] += m[i][j] * in[j];
        }
    }
}

/**
 * @brief
 * 行列累乗用のクラス
 * @tparam T
 * @tparam r
 * @tparam size = 64
 */
template <typename T, size_t r, int size = 64>
class Chain {
    using matrix = Matrix<T, r, r>;
    using vec    = std::array<T, r>;

  private:
    matrix bin[size];

  public:
    /**
     * @brief Construct a new Chain object
     * 行列累乗用にビルドをしておく
     * @param m
     */
    Chain(matrix m) {
        bin[0] = m;
        for (int i : range(1, size)) {
            mul(bin[i - 1], bin[i - 1], bin[i]);
        }
    }

    /**
     * @brief
     * コンストラクタで与えた正方行列を M,
     * 引数のベクトルを v として M^n * v を計算
     * @param v
     * @param n
     * @return vec
     * @details
     * O(r^2 log n)
     */
    vec compute(vec v, unsigned long long n) {
        for (int i = 0; n > 0; i++, n >>= 1) {
            if (n & 1) {
                vec nv;
                mul(bin[i], v, nv);
                swap(v, nv);
            }
        }
        return v;
    }
};
