/**
 * @file Loop.hpp
 * @author btk
 * @brief rangeとかループ系のクラス
 * @version 0.1
 * @date 2019-07-13
 *
 * @copyright Copyright (c) 2019
 *
 */

/*<head>*/
#pragma once
/*</head>*/

/**
 * @brief
 * rangeを逆向きに操作したいとき用
 * @details
 * ループの範囲は[bg,ed)なので注意
 * @see range
 */
class reverse_range {
  private:
    struct I {
        int x;
        int operator*() { return x - 1; }
        bool operator!=(I& lhs) { return x > lhs.x; }
        void operator++() { --x; }
    };
    I i, n;

  public:
    /**
     * @brief Construct a new reverse range object
     *
     * @param n
     */
    reverse_range(int n) : i({0}), n({n}) {}
    /**
     * @brief Construct a new reverse range object
     *
     * @param i
     * @param n
     */
    reverse_range(int i, int n) : i({i}), n({n}) {}
    /**
     * @brief
     * begin iterator
     * @return I&
     */
    I& begin() { return n; }
    /**
     * @brief
     * end iterator
     * @return I&
     */
    I& end() { return i; }
};
/**
 * @brief
 * python みたいな range-based for を実現
 * @details
 * ループの範囲は[bg,ed)なので注意
 * !つけると逆向きにループが回る (reverse_range)
 * 空間計算量はO(1)
 * 使わない変数ができて警告が出がちなので，unused_varとかを使って警告消しするとよい
 */
class range {
  private:
    struct I {
        int x;
        int operator*() { return x; }
        bool operator!=(I& lhs) { return x < lhs.x; }
        void operator++() { ++x; }
    };
    I i, n;

  public:
    /**
     * @brief Construct a new range object
     *
     * @param n
     */
    range(int n) : i({0}), n({n}) {}
    /**
     * @brief Construct a new range object
     *
     * @param i
     * @param n
     */
    range(int i, int n) : i({i}), n({n}) {}
    /**
     * @brief
     * begin iterator
     * @return I&
     */
    I& begin() { return i; }
    /**
     * @brief
     * end iterator
     * @return I&
     */
    I& end() { return n; }
    /**
     * @brief
     * 逆向きに参照するrange(reverse_rangeを取得できるs)
     * @return reverse_range
     */
    reverse_range operator!() { return reverse_range(*i, *n); }
};
