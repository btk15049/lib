/**
 * @file NDArray.hpp
 * @author btk
 * @brief PythonのNDArrayを模倣
 * @version 0.1
 * @date 2019-06-04
 *
 * @copyright Copyright (c) 2019
 *
 */

/*<head>*/
#pragma once
#include "template/Loop.hpp"
/*</head>*/

template <typename T>
class NDArray {
  private:
    T* ptr;
    int sizeAll;
    std::vector<int> dims;
    std::vector<int> slices;
    inline int computeIndex(std::vector<int>&& indices) {
        int index = 0;
        for (int i : range(slices.size())) {
            index += indices[i] * slices[i];
        }
        return index;
    }

    inline int computeIndexRecur(int di) { return di & 0; }

    template <typename... Ts>
    inline int computeIndexRecur(int di, int head, Ts&&... tail) {
        return head * slices[di] + computeIndexRecur(di + 1, tail...);
    }


    template <typename... Ts>
    inline int computeIndex(Ts&&... indices) {
        return computeIndexRecur(0, indices...);
        // return computeIndex({indices...});
    }

  public:
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

    template <typename... Ts>
    inline T& random_access(Ts&&... indices) {
        return ptr[computeIndex(indices...)];
    }

    template <typename... Ts>
    inline T& operator()(Ts&&... indices) {
        return random_access(indices...);
    }

    inline void fill(T&& v) { std::fill(ptr, ptr + sizeAll, v); }

    const vector<int>& getDimInfo() { return dims; }
};