/**
 * @file Buffer.test.cpp
 * @author btk
 * @brief Buffer.hppのテスト
 * @date 2019-06-28
 *
 * @copyright Copyright (c) 2019
 *
 */
#define BOOST_TEST_MAIN
#include "Buffer.hpp"
#include <boost/test/included/unit_test.hpp>

/**
 * @brief BufferManagerからsize分メモリ領域を持ってくるクラス
 */
class BufferTest {
  private:
    //! メモリ領域借りてきたマネージャを保持（デストラクタでここに返す)
    BufferManager<int>& lender;
    //! 本体
    int* const p;

  public:
    /**
     * @brief コンストラクタ lenderからメモリ領域（ポインタを引っ張ってくる）
     *
     * @param lender
     * @param size
     */
    BufferTest(BufferManager<int>& lender, const int size)
        : lender(lender), p(lender.pop(size)) {}
    /**
     * @brief デストラクタ、借りたものを返す
     */
    ~BufferTest() { lender.push(p); }
    /**
     * @brief 配列アクセスできるようにするだけ
     *
     * @param i
     * @return int&
     */
    int& operator[](int i) { return p[i]; }
};

BOOST_AUTO_TEST_SUITE(Buffer)
BOOST_AUTO_TEST_SUITE(DisposableBufferManagerClass)
/**
 * @brief
 * テストで使うbufferを実体化
 */
DisposableBuffer(int, 50, disposable_buffer);

/**
 * @brief DisposableBufferManagerをとりあえず使うテスト
 *
 */
BOOST_AUTO_TEST_CASE(single_use) {
    BOOST_CHECK_EQUAL(disposable_buffer.get_ptr(), 0);
    auto p = disposable_buffer.pop(10);
    BOOST_CHECK_EQUAL(disposable_buffer.get_ptr(), 10);
    disposable_buffer.push(p);
    BOOST_CHECK_EQUAL(disposable_buffer.get_ptr(), 10);
    p[3] = 17;
    p[5] = 20;
    BOOST_CHECK_EQUAL(p[3], 17);
    BOOST_CHECK_EQUAL(p[5], 20);
    disposable_buffer.clear();
    BOOST_CHECK_EQUAL(disposable_buffer.get_ptr(), 0);
}

/**
 * @brief 複数同時に使う場合のテスト
 */
BOOST_AUTO_TEST_CASE(multi_use) {
    BOOST_CHECK_EQUAL(disposable_buffer.get_ptr(), 0);
    auto p = disposable_buffer.pop(6);
    BOOST_CHECK_EQUAL(disposable_buffer.get_ptr(), 6);
    auto q = disposable_buffer.pop(8);
    BOOST_CHECK_EQUAL(disposable_buffer.get_ptr(), 14);
    p[3] = 17;
    p[5] = 20;
    q[3] = 81;
    q[5] = 122;
    BOOST_CHECK_EQUAL(p[3], 17);
    BOOST_CHECK_EQUAL(p[5], 20);
    BOOST_CHECK_EQUAL(q[3], 81);
    BOOST_CHECK_EQUAL(q[5], 122);
    BOOST_CHECK_EQUAL(q - p, 6);
    disposable_buffer.clear();
    BOOST_CHECK_EQUAL(disposable_buffer.get_ptr(), 0);
}

/**
 * @brief クラスで領域管理する場合のテスト
 *
 */
BOOST_AUTO_TEST_CASE(class_use) {
    BOOST_CHECK_EQUAL(disposable_buffer.get_ptr(), 0);
    {
        BufferTest p(disposable_buffer, 6);
        BOOST_CHECK_EQUAL(disposable_buffer.get_ptr(), 6);
        BufferTest q(disposable_buffer, 8);
        BOOST_CHECK_EQUAL(disposable_buffer.get_ptr(), 14);
        p[3] = 17;
        p[5] = 20;
        q[3] = 81;
        q[5] = 122;
        BOOST_CHECK_EQUAL(p[3], 17);
        BOOST_CHECK_EQUAL(p[5], 20);
        BOOST_CHECK_EQUAL(q[3], 81);
        BOOST_CHECK_EQUAL(q[5], 122);
    }
    BOOST_CHECK_EQUAL(disposable_buffer.get_ptr(), 14);
    disposable_buffer.clear();
    BOOST_CHECK_EQUAL(disposable_buffer.get_ptr(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(BlockBufferManagerClass)
/**
 * @brief
 * テストで使うbufferを実体化
 */
BlockBuffer(int, 5, 6, block_buffer);

/**
 * @brief とりあえず使えるかテスト
 */
BOOST_AUTO_TEST_CASE(single_use) {
    BOOST_CHECK_EQUAL(block_buffer.get_queue_size(), 5);
    auto p = block_buffer.pop();
    BOOST_CHECK_EQUAL(block_buffer.get_queue_size(), 4);
    for (int i : range(6)) p[i] = i + 1;
    for (int i : range(6)) BOOST_CHECK_EQUAL(p[i], i + 1);

    block_buffer.push(p);
    BOOST_CHECK_EQUAL(block_buffer.get_queue_size(), 5);
}

/**
 * @brief 複数使う場合（領域が重複してないかとかをテスト）
 */
BOOST_AUTO_TEST_CASE(multi_use) {
    BOOST_CHECK_EQUAL(block_buffer.get_queue_size(), 5);
    auto p = block_buffer.pop();
    BOOST_CHECK_EQUAL(block_buffer.get_queue_size(), 4);

    auto q = block_buffer.pop();
    BOOST_CHECK_EQUAL(block_buffer.get_queue_size(), 3);

    for (int i : range(6)) p[i] = i + 1;
    for (int i : range(6)) q[i] = -(i + 1);

    for (int i : range(6)) BOOST_CHECK_EQUAL(p[i], i + 1);
    for (int i : range(6)) BOOST_CHECK_EQUAL(q[i], -(i + 1));

    block_buffer.push(p);
    BOOST_CHECK_EQUAL(block_buffer.get_queue_size(), 4);
    block_buffer.push(q);
    BOOST_CHECK_EQUAL(block_buffer.get_queue_size(), 5);
}

/**
 * @brief BlockBufferManagerをクラスに使用した場合のテスト
 * @details デストラクタでうまくqueueにポインタを戻せるかのテストがしたい
 * @see BufferTest
 */
BOOST_AUTO_TEST_CASE(class_use) {
    BOOST_CHECK_EQUAL(block_buffer.get_queue_size(), 5);
    {
        auto p = BufferTest(block_buffer, 6);
        BOOST_CHECK_EQUAL(block_buffer.get_queue_size(), 4);

        auto q = BufferTest(block_buffer, 6);
        BOOST_CHECK_EQUAL(block_buffer.get_queue_size(), 3);

        for (int i : range(6)) p[i] = i + 1;
        for (int i : range(6)) q[i] = -(i + 1);

        for (int i : range(6)) BOOST_CHECK_EQUAL(p[i], i + 1);
        for (int i : range(6)) BOOST_CHECK_EQUAL(q[i], -(i + 1));
    }
    BOOST_CHECK_EQUAL(block_buffer.get_queue_size(), 5);
}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()