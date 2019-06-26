/*<head>*/
#pragma once
#include "Template.hpp"
/*</head>*/

/**
 * @file Buffer.hpp
 * @brief メモリ管理クラス
 * @author btk15049
 * @date 2019/03/11
 * @details
 */
namespace _Buffer_ {
    /**
     * @brief
     * バッファは基本的にこれを継承する
     * @tparam T
     */
    template <typename T>
    class BufferManager {
      protected:
        T* buf;

      public:
        BufferManager(T* buf) : buf(buf) {}
        /**
         * @brief
         * size分バッファを取得
         * @param size
         * @return T*
         */
        virtual T* pop(int size) = 0;
        /**
         * @brief
         * 領域をマネージャに返却（解放）する
         * @param p
         */
        virtual void push(T* p) = 0;
        /**
         * @brief
         * マネージャのリセット
         */
        virtual void clear() = 0;
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

    /**
     * @brief
     * blocks*block_size分の領域をblocks個に区切って、やりくりする。
     * 使わなくなったらpopで返すのを忘れずに
     * @tparam T
     */
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

/**
 * @brief
 * [var_name]という名前のBlockBufferManagerを生成する
 * type型で、大きさ　block_size の領域をblocks分生成
 */
#define BlockBuffer(type, blocks, block_size, var_name) \
    type var_name##_mem[(blocks) * (block_size)];       \
    BlockBufferManager<type> var_name(var_name##_mem, (blocks), (block_size));
