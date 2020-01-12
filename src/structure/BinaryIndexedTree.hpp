/*<head>*/
#pragma once
#include <memory>
/*</head>*/

// namespace BinaryIndexedTreePreset
// constexpr auto addInt64 = [](int64_t l, int64_t r) { return l + r; };
// template <typename T>
// constexpr decltype(auto) buildAddFunction() {
//     return [](decltype(T) l, decltype(T) r) { return l + r; };
// }
// constexpr auto xorInt32 = [](int32_t l, int32_t r) { return l ^ r; };
// constexpr auto xorInt64 = [](int64_t l, int64_t r) { return l ^ r; };


template <typename T1, typename T2, typename T3>
class BinaryIndexedTree {
  private:
    const int _size;
    const T2 addOperation;
    const T3 invOperation;
    const std::unique_ptr<T1[]> value;

  public:
    BinaryIndexedTree(int _size, T2 addOperation, T3 invOperation, T1 zero);
    BinaryIndexedTree(int _size);

    int size() const;
    void add(int id, T1 v);
    T1 sum(int n) const;
    T1 sum(int l, int r) const;

  private:
    void _add(int id, T1 v);
    T1 _sum(int id) const;

    // v[1]+v[2]+...+v[x]>=wとなる最小のxを求める
    // int lowerbound(T w) {
    //    if (w <= 0) return 0;
    //    int x = 0;
    //    for (int k = (1 << (31 - __builtin_clz(sz))); k > 0; k >>= 1)
    //        if (x + k <= sz && bit[x + k] < w) {
    //            w -= bit[x + k];
    //            x += k;
    //        }
    //    return x + 1;
    // }
};

namespace BinaryIndexedTreePreset {
    namespace Int {
        using type = int32_t;
        namespace Sum {
            constexpr auto add  = [](type l, type r) { return l + r; };
            constexpr auto inv  = [](type v) { return -v; };
            constexpr type zero = 0;
            using Preset =
                BinaryIndexedTree<type, decltype(add), decltype(inv)>;
        } // namespace Sum
        namespace Xor {
            constexpr auto add  = [](type l, type r) { return l ^ r; };
            constexpr auto inv  = [](type v) { return v; };
            constexpr type zero = 0;
            using Preset =
                BinaryIndexedTree<type, decltype(add), decltype(inv)>;
        } // namespace Xor

    } // namespace Int

    namespace Long {
        using type = int64_t;
        namespace Sum {
            constexpr auto add  = [](type l, type r) { return l + r; };
            constexpr auto inv  = [](type v) { return -v; };
            constexpr type zero = 0;
            using Preset =
                BinaryIndexedTree<type, decltype(add), decltype(inv)>;
        } // namespace Sum

        namespace Xor {
            constexpr auto add  = [](type l, type r) { return l ^ r; };
            constexpr auto inv  = [](type v) { return v; };
            constexpr type zero = 0;
            using Preset =
                BinaryIndexedTree<type, decltype(add), decltype(inv)>;
        } // namespace Xor

    } // namespace Long
} // namespace BinaryIndexedTreePreset

/**
 * @brief int32, 加算を行うBIT の特殊化実装, Presetを使う用に定義
 * @param _size
 * @return [0, size) の範囲を扱うBIT
 */
template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Int::type,
                  decltype(BinaryIndexedTreePreset::Int::Sum::add),
                  decltype(BinaryIndexedTreePreset::Int::Sum::inv)>::
    BinaryIndexedTree(int _size);

/**
 * @brief int64, 加算を行うBIT の特殊化実装, Presetを使う用に定義
 * @param _size
 * @return [0, size) の範囲を扱うBIT
 */
template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Long::type,
                  decltype(BinaryIndexedTreePreset::Long::Sum::add),
                  decltype(BinaryIndexedTreePreset::Long::Sum::inv)>::
    BinaryIndexedTree(int _size);


/**
 * @brief int32, xor演算を行うBIT の特殊化実装, Presetを使う用に定義
 * @param _size
 * @return [0, size) の範囲を扱うBIT
 */
template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Int::type,
                  decltype(BinaryIndexedTreePreset::Int::Xor::add),
                  decltype(BinaryIndexedTreePreset::Int::Xor::inv)>::
    BinaryIndexedTree(int _size);


/**
 * @brief int64, xor演算を行うBIT の特殊化実装, Presetを使う用に定義
 * @param _size
 * @return [0, size) の範囲を扱うBIT
 */
template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Long::type,
                  decltype(BinaryIndexedTreePreset::Long::Xor::add),
                  decltype(BinaryIndexedTreePreset::Long::Xor::inv)>::
    BinaryIndexedTree(int _size);

/* ######################################################################################
 */


template <typename T1, typename T2, typename T3>
BinaryIndexedTree<T1, T2, T3>::BinaryIndexedTree(int _size, T2 addOperation,
                                                 T3 invOperation, T1 zero)
    : _size(_size),
      addOperation(addOperation),
      invOperation(invOperation),
      value(new T1[_size + 1]) {
    for (int i = 0; i <= _size; i++) {
        value[i] = zero;
    }
}

template <typename T1, typename T2, typename T3>
int BinaryIndexedTree<T1, T2, T3>::size() const {
    return _size;
}


template <typename T1, typename T2, typename T3>
void BinaryIndexedTree<T1, T2, T3>::_add(int id, T1 v) {
    while (id <= _size) {
        value[id] = addOperation(value[id], v);
        id += id & -id;
    }
}

template <typename T1, typename T2, typename T3>
T1 BinaryIndexedTree<T1, T2, T3>::_sum(int id) const {
    T1 s = 0;
    while (id > 0) {
        s = addOperation(s, value[id]);
        id -= id & -id;
    }
    return s;
}

template <typename T1, typename T2, typename T3>
T1 BinaryIndexedTree<T1, T2, T3>::sum(int id) const {
    return _sum(id);
}

template <typename T1, typename T2, typename T3>
T1 BinaryIndexedTree<T1, T2, T3>::sum(int l, int r) const {
    return addOperation(_sum(r), invOperation(_sum(l)));
}

template <typename T1, typename T2, typename T3>
void BinaryIndexedTree<T1, T2, T3>::add(int id, T1 v) {
    return _add(id + 1, v);
}


template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Int::type,
                  decltype(BinaryIndexedTreePreset::Int::Sum::add),
                  decltype(BinaryIndexedTreePreset::Int::Sum::inv)>::
    BinaryIndexedTree(int _size)
    : BinaryIndexedTree(_size, BinaryIndexedTreePreset::Int::Sum::add,
                        BinaryIndexedTreePreset::Int::Sum::inv,
                        BinaryIndexedTreePreset::Int::Sum::zero) {}

template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Long::type,
                  decltype(BinaryIndexedTreePreset::Long::Sum::add),
                  decltype(BinaryIndexedTreePreset::Long::Sum::inv)>::
    BinaryIndexedTree(int _size)
    : BinaryIndexedTree(_size, BinaryIndexedTreePreset::Long::Sum::add,
                        BinaryIndexedTreePreset::Long::Sum::inv,
                        BinaryIndexedTreePreset::Long::Sum::zero) {}

template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Int::type,
                  decltype(BinaryIndexedTreePreset::Int::Xor::add),
                  decltype(BinaryIndexedTreePreset::Int::Xor::inv)>::
    BinaryIndexedTree(int _size)
    : BinaryIndexedTree(_size, BinaryIndexedTreePreset::Int::Xor::add,
                        BinaryIndexedTreePreset::Int::Xor::inv,
                        BinaryIndexedTreePreset::Int::Xor::zero) {}

template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Long::type,
                  decltype(BinaryIndexedTreePreset::Long::Xor::add),
                  decltype(BinaryIndexedTreePreset::Long::Xor::inv)>::
    BinaryIndexedTree(int _size)
    : BinaryIndexedTree(_size, BinaryIndexedTreePreset::Long::Xor::add,
                        BinaryIndexedTreePreset::Long::Xor::inv,
                        BinaryIndexedTreePreset::Long::Xor::zero) {}