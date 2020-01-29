//! @cond
#define BOOST_TEST_MAIN
//! @endcond
#include "structure/BinaryIndexedTree.hpp"
#include "template/Random.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(BinaryIndexedTreeClass)

template <typename T1, typename T2, typename T3>
void validate_add(const BinaryIndexedTree<T1, T2, T3>& actual,
                  const std::vector<T1>& expected) {
    BOOST_CHECK_EQUAL(static_cast<int>(actual.size()),
                      static_cast<int>(expected.size()));
    for (int i = 0; i < actual.size(); i++) {
        for (int j = i; j <= actual.size(); j++) {
            T1 expected_sum = 0;
            for (int k = i; k < j; k++) {
                expected_sum += expected[k];
            }
            BOOST_CHECK_EQUAL(actual.sum(i, j), expected_sum);
            if (i == 0) {
                BOOST_CHECK_EQUAL(actual.sum(j), expected_sum);
            }
        }
    }
}

template <typename T1, typename T2, typename T3>
void validate_xor(const BinaryIndexedTree<T1, T2, T3>& actual,
                  const std::vector<T1>& expected) {
    BOOST_CHECK_EQUAL(static_cast<int>(actual.size()),
                      static_cast<int>(expected.size()));
    for (int i = 0; i < actual.size(); i++) {
        for (int j = i; j <= actual.size(); j++) {
            T1 expected_sum = 0;
            for (int k = i; k < j; k++) {
                expected_sum ^= expected[k];
            }
            BOOST_CHECK_EQUAL(actual.sum(i, j), expected_sum);
            if (i == 0) {
                BOOST_CHECK_EQUAL(actual.sum(j), expected_sum);
            }
        }
    }
}
template <typename T1, typename T2, typename T3>
void validate_max(const BinaryIndexedTree<T1, T2, T3>& actual,
                  const std::vector<T1>& expected) {
    BOOST_CHECK_EQUAL(static_cast<int>(actual.size()),
                      static_cast<int>(expected.size()));
    for (int j = 0; j <= actual.size(); j++) {
        T1 expected_sum = 0;
        for (int k = 0; k < j; k++) {
            expected_sum = std::max(expected_sum, expected[k]);
        }
        BOOST_CHECK_EQUAL(actual.sum(0, j), expected_sum);
        BOOST_CHECK_EQUAL(actual.sum(j), expected_sum);
    }
}


BOOST_AUTO_TEST_CASE(INT_SUM) {
    using namespace BinaryIndexedTreePreset::Int::Sum;
    // コンストラクタの検証
    // 普通にやる場合
    BinaryIndexedTree<int32_t, decltype(add), decltype(inv)> tree1(5, add, inv,
                                                                   zero);
    // presetを使う場合
    Preset tree2(10);

    // sizeメソッド
    BOOST_CHECK_EQUAL(tree1.size(), 5);
    BOOST_CHECK_EQUAL(tree2.size(), 10);

    BOOST_CHECK_EQUAL(tree1.sum(1), 0);
    tree1.add(0, 7);
    BOOST_CHECK_EQUAL(tree1.sum(1), 7);
    BOOST_CHECK_EQUAL(tree1.sum(0, 1), 7);
    tree1.add(4, 15);
    BOOST_CHECK_EQUAL(tree1.sum(5), 22);
    BOOST_CHECK_EQUAL(tree1.sum(4, 5), 15);
    validate_add(tree1, {7, 0, 0, 0, 15});
    std::vector<int> expected(10);
    XorShift32 rGen;
    for (int i = 0; i < 1000; i++) {
        int p = rGen.next_int<>() % 10;
        int r = rGen.next_signed<18>();
        tree2.add(p, r);
        expected[p] += r;
        validate_add(tree2, expected);
    }
}

BOOST_AUTO_TEST_CASE(INT_MAXIMUM) {
    using namespace BinaryIndexedTreePreset::Int::Max;
    // コンストラクタの検証
    // 普通にやる場合
    BinaryIndexedTree<int32_t, decltype(add), decltype(inv)> tree1(5, add, inv,
                                                                   zero);
    // presetを使う場合
    Preset tree2(10);

    // sizeメソッド
    BOOST_CHECK_EQUAL(tree1.size(), 5);
    BOOST_CHECK_EQUAL(tree2.size(), 10);

    BOOST_CHECK_EQUAL(tree1.sum(1), 0);
    tree1.add(0, 7);
    BOOST_CHECK_EQUAL(tree1.sum(1), 7);
    BOOST_CHECK_EQUAL(tree1.sum(0, 1), 7);
    tree1.add(4, 15);
    BOOST_CHECK_EQUAL(tree1.sum(5), 15);
    BOOST_CHECK_EQUAL(tree1.sum(4, 5), 15);
    validate_max(tree1, {7, 0, 0, 0, 15});
    std::vector<int> expected(10);
    XorShift32 rGen;
    for (int i = 0; i < 1000; i++) {
        int p = rGen.next_int<>() % 10;
        int r = rGen.next_signed<18>();
        tree2.add(p, r);
        expected[p] = std::max(expected[p], r);
        validate_max(tree2, expected);
    }
}


BOOST_AUTO_TEST_CASE(LONG_SUM) {
    using namespace BinaryIndexedTreePreset::Long::Sum;
    // コンストラクタの検証
    // 普通にやる場合
    BinaryIndexedTree<int64_t, decltype(add), decltype(inv)> tree1(5, add, inv,
                                                                   zero);
    // presetを使う場合
    Preset tree2(10);

    // sizeメソッド
    BOOST_CHECK_EQUAL(tree1.size(), 5);
    BOOST_CHECK_EQUAL(tree2.size(), 10);

    BOOST_CHECK_EQUAL(tree1.sum(1), 0);
    tree1.add(0, 7);
    BOOST_CHECK_EQUAL(tree1.sum(1), 7);
    BOOST_CHECK_EQUAL(tree1.sum(0, 1), 7);
    tree1.add(4, 15);
    BOOST_CHECK_EQUAL(tree1.sum(5), 22);
    BOOST_CHECK_EQUAL(tree1.sum(4, 5), 15);
    validate_add(tree1, {7, 0, 0, 0, 15});
    std::vector<int64_t> expected(10);
    XorShift32 rGen;
    for (int i = 0; i < 1000; i++) {
        int p = rGen.next_int<>() % 10;
        int r = rGen.next_signed<18>();
        tree2.add(p, r);
        expected[p] += r;
        validate_add(tree2, expected);
    }
}

BOOST_AUTO_TEST_CASE(INT_XOR) {
    using namespace BinaryIndexedTreePreset::Int::Xor;
    // コンストラクタの検証
    // 普通にやる場合
    BinaryIndexedTree<int32_t, decltype(add), decltype(inv)> tree1(5, add, inv,
                                                                   zero);
    // presetを使う場合
    Preset tree2(10);

    // sizeメソッド
    BOOST_CHECK_EQUAL(tree1.size(), 5);
    BOOST_CHECK_EQUAL(tree2.size(), 10);

    BOOST_CHECK_EQUAL(tree1.sum(1), 0);
    tree1.add(0, 7);
    BOOST_CHECK_EQUAL(tree1.sum(1), 7);
    BOOST_CHECK_EQUAL(tree1.sum(0, 1), 7);
    tree1.add(4, 15);
    BOOST_CHECK_EQUAL(tree1.sum(5), 8);
    BOOST_CHECK_EQUAL(tree1.sum(4, 5), 15);
    validate_xor(tree1, {7, 0, 0, 0, 15});
    std::vector<int> expected(10);
    XorShift32 rGen;
    for (int i = 0; i < 1000; i++) {
        int p = rGen.next_int<>() % 10;
        int r = rGen.next_int();
        tree2.add(p, r);
        expected[p] ^= r;
        validate_xor(tree2, expected);
    }
}

BOOST_AUTO_TEST_CASE(LONG_XOR) {
    using namespace BinaryIndexedTreePreset::Long::Xor;
    // コンストラクタの検証
    // 普通にやる場合
    BinaryIndexedTree<int64_t, decltype(add), decltype(inv)> tree1(5, add, inv,
                                                                   zero);
    // presetを使う場合
    Preset tree2(10);

    // sizeメソッド
    BOOST_CHECK_EQUAL(tree1.size(), 5);
    BOOST_CHECK_EQUAL(tree2.size(), 10);

    BOOST_CHECK_EQUAL(tree1.sum(1), 0);
    tree1.add(0, 7);
    BOOST_CHECK_EQUAL(tree1.sum(1), 7);
    BOOST_CHECK_EQUAL(tree1.sum(0, 1), 7);
    tree1.add(4, 15);
    BOOST_CHECK_EQUAL(tree1.sum(5), 8);
    BOOST_CHECK_EQUAL(tree1.sum(4, 5), 15);
    validate_xor(tree1, {7, 0, 0, 0, 15});
    std::vector<int64_t> expected(10);
    XorShift32 rGen;
    for (int i = 0; i < 1000; i++) {
        int p = rGen.next_int<>() % 10;
        int r = rGen.next_int();
        tree2.add(p, r);
        expected[p] ^= r;
        validate_xor(tree2, expected);
    }
}

BOOST_AUTO_TEST_SUITE_END()