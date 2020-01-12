/*<head>*/
#pragma once
#include <memory>
/*</head>*/

/**
 * @brief BinaryIndexedTreeの演算を抽象化したクラス。
 * 演算の型をtemplateに埋め込む必要があるため、宣言が大変。
 * そのために名前空間BinaryIndexedTreePreset
 * が用意してあり、基本的にはそちらを使うと良い。
 *
 * @tparam T 扱うデータの型
 * @tparam AddOperation
 * 加算に相当する演算、関数オブジェクトを作ってdecltypeをするとよい
 * @tparam InvOperation
 * 逆元を取るための単項演算子に相当する演算、関数オブジェクトを作ってdecltypeをするとよい
 */
template <typename T, typename AddOperation, typename InvOperation>
class BinaryIndexedTree {
  private:
    const int _size;
    const AddOperation addOperation;
    const InvOperation invOperation;
    const std::unique_ptr<T[]> value;

  public:
    BinaryIndexedTree(int _size, AddOperation addOperation,
                      InvOperation invOperation, T zero);
    /**
     * @brief [0, _size) の範囲を持つBITを生成する（特殊化の実装が必要）
     * @param _size 要素数
     */
    BinaryIndexedTree(int _size);

    /**
     * @brief コンストラクタで指定したBITに格納できる要素数を取得する
     *
     * @return int 要素数
     */
    int size() const;

    /**
     * @brief 位置idにvを加算する
     *
     * @param id 位置
     * @param v 加算する値
     */
    void add(int id, T v);

    /**
     * @brief [0,n) に加算された値の総和を計算する
     *
     * @param n パラメータ
     * @return T 総和
     */
    T sum(int n) const;

    /**
     * @brief [l,r) に加算された値の総和を計算する
     *
     * @param l パラメータ
     * @param r パラメータ
     * @return T 総和
     */
    T sum(int l, int r) const;

  private:
    void _add(int id, T v);
    T _sum(int id) const;

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


template <typename T, typename AddOperation, typename InvOperation>
BinaryIndexedTree<T, AddOperation, InvOperation>::BinaryIndexedTree(
    int _size, AddOperation addOperation, InvOperation invOperation, T zero)
    : _size(_size),
      addOperation(addOperation),
      invOperation(invOperation),
      value(new T[_size + 1]) {
    for (int i = 0; i <= _size; i++) {
        value[i] = zero;
    }
}

template <typename T, typename AddOperation, typename InvOperation>
int BinaryIndexedTree<T, AddOperation, InvOperation>::size() const {
    return _size;
}


template <typename T, typename AddOperation, typename InvOperation>
void BinaryIndexedTree<T, AddOperation, InvOperation>::_add(int id, T v) {
    while (id <= _size) {
        value[id] = addOperation(value[id], v);
        id += id & -id;
    }
}

template <typename T, typename AddOperation, typename InvOperation>
T BinaryIndexedTree<T, AddOperation, InvOperation>::_sum(int id) const {
    T s = 0;
    while (id > 0) {
        s = addOperation(s, value[id]);
        id -= id & -id;
    }
    return s;
}

template <typename T, typename AddOperation, typename InvOperation>
T BinaryIndexedTree<T, AddOperation, InvOperation>::sum(int id) const {
    return _sum(id);
}

template <typename T, typename AddOperation, typename InvOperation>
T BinaryIndexedTree<T, AddOperation, InvOperation>::sum(int l, int r) const {
    return addOperation(_sum(r), invOperation(_sum(l)));
}

template <typename T, typename AddOperation, typename InvOperation>
void BinaryIndexedTree<T, AddOperation, InvOperation>::add(int id, T v) {
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