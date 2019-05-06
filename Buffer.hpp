/*<head>*/
#pragma once
#include "Template.hpp"
/*</head>*/

/**
 * @file Buffer.hpp
 * @brief メモリ管理クラス
 * @author btk15049
 * @date 2019/03/11
 * @datails
 */
namespace _Buffer_ {
    template <typename T>
    struct BufferManager {
        T* mem;
        int ptr;
        BufferManager(T* mem) {
            ptr       = 0;
            this->mem = mem;
        }
        T* get(int m) {
            ptr += m;
            return mem + ptr - m;
        }
        void reset() { ptr = 0; }
    };
} // namespace _Buffer_
using namespace _Buffer_;