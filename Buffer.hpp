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
    class BufferManager {
      protected:
        T* buf;

      public:
        BufferManager(T* buf) : buf(buf) {}
        virtual T* pop(int size) = 0;
        virtual void push(T* p)  = 0;
        virtual void clear()     = 0;
    };

    template <typename T>
    class DisposableBufferManager : public BufferManager<T> {
      private:
        int ptr;

      public:
        DisposableBufferManager(T* buf) : BufferManager<T>(buf), ptr(0){};

        T* pop(int size) {
            ptr += size;
            return this->buf + ptr - size;
        }

        void push(T* p) {}

        void clear() { ptr = 0; }
    };

    template <typename T>
    class BlockBufferManager : public BufferManager<T> {
      private:
        std::queue<T*> que;

      public:
        BlockBufferManager(T* buf, int blocks, int block_size)
            : BufferManager<T>(buf) {
            for (int i : range(blocks)) {
                que.push(this->buf + i * block_size);
            }
        };

        T* pop(int size = 0) {
            T* ptr = que.front();
            que.pop();
            return ptr;
        }

        void push(T* p) { que.push(p); }

        void clear() {}
    };

} // namespace _Buffer_
using namespace _Buffer_;

#define BlockBuffer(type, blocks, block_size, var_name) \
    type var_name##_mem[(blocks) * (block_size)];       \
    BlockBufferManager<type> var_name(var_name##_mem, (blocks), (block_size));
