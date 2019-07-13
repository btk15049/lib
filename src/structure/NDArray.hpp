/**
 * @file NDArray.hpp
 * @author btk
 * @brief PythonのNDArrayを模倣
 * @version 0.1
 * @date 2019-06-04
 * @todo テスト
 * @copyright Copyright (c) 2019
 *
 */

/*<head>*/
#pragma once
#include "template/Loop.hpp"
/*</head>*/

/**
 * @brief PythonのNDArray的なやつ
 * @tparam T 型を入れてね
 */
template <typename T>
class NDArray {
  private:
    //! メモリの場所
    T* ptr;
    //! 要素数
    int sizeAll;
    //! 各次元の要素数
    std::vector<int> dims;
    //! ランダムアクセス用に前計算したやつ
    std::vector<int> slices;

    /**
     * @brief indicesで得られた引数が，一次元配列で何番目かをforで計算
     * @Deprecated
     * @param indices
     * @return int
     */
    inline int computeIndex(std::vector<int>&& indices) {
        int index = 0;
        for (int i : range(slices.size())) {
            index += indices[i] * slices[i];
        }
        return index;
    }

    /**
     * @brief computeIndexRecurの終端
     *
     * @param di
     * @return int 必ず0
     */
    inline int computeIndexRecur(int di) { return di & 0; }

    /**
     * @brief indicesで得られた引数が，一次元配列で何番目かを再帰で計算
     * @tparam Ts
     * @param di
     * @param head
     * @param tail
     * @return int
     */
    template <typename... Ts>
    inline int computeIndexRecur(int di, int head, Ts&&... tail) {
        return head * slices[di] + computeIndexRecur(di + 1, tail...);
    }


    /**
     * @brief NDarrayの，indicesで表されるindexを返す
     * @tparam Ts
     * @param indices
     * @return int
     */
    template <typename... Ts>
    inline int computeIndex(Ts&&... indices) {
        return computeIndexRecur(0, indices...);
        // return computeIndex({indices...});
    }

  public:
    /**
     * @brief Construct a new NDArray object
     * @details
     * 1. ポインタセット
     * 2. dims初期化(paramsの値)
     * 3. slices初期化（dimsから計算）
     * 4. 全要素のサイズ計算
     * @tparam Ts
     * @param ptr
     * @param params
     */
    template <typename... Ts>
    NDArray(T* ptr, Ts&&... params) : ptr(ptr) {
        for (auto const& d : {params...}) {
            dims.push_back(d);
        }
        slices.resize(dims.size());
        slices.back() = 1;
        for (int di : !range(1, dims.size())) {
            slices[di - 1] = slices[di] * dims[di];
        }
        sizeAll = slices.front() * dims.front();
    }

    /**
     * @brief ランダムアクセスして，その要素の参照を返す
     * @tparam Ts
     * @param indices
     * @return T&
     */
    template <typename... Ts>
    inline T& random_access(Ts&&... indices) {
        return ptr[computeIndex(indices...)];
    }

    /**
     * @brief 要素取得
     * @see random_access
     * @tparam Ts
     * @param indices
     * @return T&
     */
    template <typename... Ts>
    inline T& operator()(Ts&&... indices) {
        return random_access(indices...);
    }

    /**
     * @brief 全要素をvで埋める
     * @param v
     */
    inline void fill(T&& v) { std::fill(ptr, ptr + sizeAll, v); }

    /**
     * @brief Get the Dim Info object
     * @details 各次元がいくつ要素を持つか返す（実態はdimsを返すだけ）
     * @return const vector<int>&
     */
    const vector<int>& getDimInfo() { return dims; }
};