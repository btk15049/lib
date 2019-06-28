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
        /**
         * @brief
         * 本体、ポインタで管理
         * \todo unique_ptrに変更
         */
        T* buf;

      public:
        /**
         * @brief Construct a new Buffer Manager object
         *
         * @param buf
         */
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

    /**
     * @brief 使った分だけメモリを使い捨てするmaneger
     * 使い回ししたい場合には不向き
     *
     * @tparam T
     */
    template <typename T>
    class DisposableBufferManager : public BufferManager<T> {
      private:
        //! どこまで使ったかを管理
        int ptr;

      public:
        /**
         * @brief Construct a new Disposable Buffer Manager object
         *
         * @param buf 配列を保持するポインタ
         */
        DisposableBufferManager(T* buf) : BufferManager<T>(buf), ptr(0){};

        /**
         * @brief ポインタを返して、使った分だけptrを進める
         *
         * @param size 欲しい領域のサイズ
         * @return T*
         */
        T* pop(int size) {
            ptr += size;
            return this->buf + ptr - size;
        }

        /**
         * @brief 何もしない
         *
         * @param p
         */
        void push(T* p) { unused_var(p); }

        /**
         * @brief ptrをリセット
         *
         */
        void clear() { ptr = 0; }

        /**
         * @brief Get the ptr object
         * 現在どこまで使っているかがわかる。主にデバッグ用
         * @return int
         */
        int get_ptr() { return ptr; }
    };

    /**
     * @def DisposableBuffer(type, size, var_name)
     * @brief
     * [var_name]という名前のDisposalBufferManagerを生成する
     */
#define DisposableBuffer(type, size, var_name) \
    type var_name##_mem[size];                 \
    DisposableBufferManager<type> var_name(var_name##_mem);

    /**
     * @brief
     * blocks*block_size分の領域をblocks個に区切って、やりくりする。
     * 使わなくなったらpopで返すのを忘れずに
     * @tparam T
     */
    template <typename T>
    class BlockBufferManager : public BufferManager<T> {
      private:
        //! 使われてないblockをキューで管理
        std::queue<T*> que;

      public:
        /**
         * @brief Construct a new Block Buffer Manager object
         *
         * @param buf
         * @param blocks
         * @param block_size
         */
        BlockBufferManager(T* buf, int blocks, int block_size)
            : BufferManager<T>(buf) {
            for (int i : range(blocks)) {
                que.push(this->buf + i * block_size);
            }
        };

        /**
         * @brief　blockを取得
         *
         * @param size 意味ないよ
         * @return T*
         */
        T* pop(int size = 0) {
            unused_var(size);
            T* ptr = que.front();
            que.pop();
            return ptr;
        }

        /**
         * @brief デストラクタとかでpush呼ぶのを忘れずに
         *
         * @param p
         */
        void push(T* p) { que.push(p); }

        /**
         * @brief 今の所何もしない
         * \todo 要検討
         */
        void clear() {}

        /**
         * @brief キューの残りサイズを取得 デバッグ用
         *
         * @return int
         */
        int get_queue_size() { return que.size(); }
    };

} // namespace _Buffer_
using namespace _Buffer_;

/**
 * @def BlockBuffer(type, blocks, block_size, var_name)
 * @brief
 * [var_name]という名前のBlockBufferManagerを生成する
 * type型で、大きさ　block_size の領域をblocks分生成
 */
#define BlockBuffer(type, blocks, block_size, var_name) \
    type var_name##_mem[(blocks) * (block_size)];       \
    BlockBufferManager<type> var_name(var_name##_mem, (blocks), (block_size));
