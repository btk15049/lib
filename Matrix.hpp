/**
 * @file Matrix.hpp
 * @author btk
 * @brief
 * @version 0.1
 * @date 2019-06-10
 *
 * @copyright Copyright (c) 2019
 *
 */

/*<head>*/
#pragma once
#include "Template.hpp"
/*</head>*/

namespace _MATRIX_ {
    template <typename T, size_t row_size, size_t col_size>
    class Matrix {
      public:
        static constexpr int fixed_col_size = ((col_size + 3) / 4) * 4;
        static constexpr int fixed_row_size = ((row_size + 3) / 4) * 4;
        using col_array                     = array<T, fixed_col_size>;
        using row_array                     = array<T, fixed_row_size>;
        using matrix                        = array<col_array, row_size>;

      private:
        matrix value;

      public:
        inline col_array& operator[](const int idx) { return value[idx]; }
    };

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

    template <typename T, size_t r, size_t c>
    inline void mul(Matrix<T, r, c> m, array<T, c> in, array<T, r>& out) {
        for (int i : range(r)) {
            out[i] = 0;
            for (int j : range(c)) {
                out[i] += m[i][j] * in[j];
            }
        }
    }

    template <typename T, size_t r, int size = 64>
    class Chain {
        using matrix = Matrix<T, r, r>;
        using vec    = array<T, r>;

      private:
        matrix bin[size];

      public:
        Chain(matrix m) {
            bin[0] = m;
            for (int i : range(1, size)) {
                mul(bin[i - 1], bin[i - 1], bin[i]);
            }
        }
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

} // namespace _MATRIX_


using namespace _MATRIX_;