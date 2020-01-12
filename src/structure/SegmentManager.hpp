/**
 * @file SegmentManager.hpp
 * @author btk
 * @brief 区間を追加したり削除したりするやつ
 * @version 0.1
 * @date 2020-01-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/*<head>*/
#pragma once
#include "template/MinMaxOperation.hpp"
#include <map>
#include <vector>
/*</head>*/

/**
 * @brief 
 * 区間を表す構造体
 * 半開区間[l,r)の形で管理される
 */
struct Segment {
    int64_t l;
    int64_t r;
    Segment(const int64_t l, const int64_t r) : l(l), r(r) {}
    Segment(const int64_t v = 0) : l(v), r(v + 1) {}
    inline int64_t len() { return r - l; }
};

/**
 * @brief 点が区間より左（座標が小さい）かどうかを判定
 * @param v 点
 * @param s 区間
 * @return true v < s.l
 * @return false v >= s.r
 */
inline bool isLeft(const int64_t v, const Segment& s) { return v < s.l; }

/**
 * @brief 点が区間より右（座標が大きい）かどうかを判定
 * @param v 点
 * @param s 区間
 * @return true v > s.l
 * @return false v <= s.r
 */
inline bool isRight(const int64_t v, const Segment& s) { return s.r <= v; }

/**
 * @brief 点が区間に対して厳密に外にあるかどうかを判定
 * @param v 点
 * @param s 区間
 * @return true v < s.l or s.r <= v
 * @return false s.l <= v and v < s.r
 */
inline bool out(const int64_t v, const Segment& s) {
    return isLeft(v, s) || isRight(v, s);
}

/**
 * @brief 点が区間に対して境界上または内にあるかどうかを判定
 * @param v 点
 * @param s 区間
 * @return false v < s.l or s.r <= v
 * @return true s.l <= v and v < s.r
 */
inline bool in(const int64_t v, const Segment s) { return !out(v, s); }

/**
 * @brief 区間s1が区間s2に対して境界上を含む内側にあるかどうかを判定
 * @param s1 区間
 * @param s2 区間
 * @return true s1がs2に完全に内包されている場合
 * @return それ以外
 */
inline bool in(const Segment s1, const Segment s2) { return in(s1.l, s2) && in(s1.r -1 , s2); }

/**
 * @brief 区間s1が区間s2に対して外側にあるかどうかを判定
 * @param s1 区間
 * @param s2 区間
 * @return true s2がs1に完全に内包されている場合
 * @return それ以外
 */
inline bool overlap(const Segment s1, const Segment s2) { return in(s2, s1); }

inline bool operator==(const Segment& l, const Segment& r) {
    return l.l == r.l && l.r == r.r;
}

namespace std{
    /**
     * @brief std::to_stringをオーバーロード、デバッグ用
     * @param s 区間
     * @return string 文字列
     */
    string to_string(Segment s) {
        return "{"+to_string(s.l) + ", " + to_string(s.r) + "}";
    }
}

/**
 * @brief 複数の区間を統合して管理するためのクラス
 * @details add, erase 共にならしO(logN)
 */
class SegmentManager {
  public:
  /**
   * @brief Construct a new Segment Manager object
   */
    SegmentManager();

    /**
     * @brief 現在の状態に対してsを追加し、変化があった差分を戻り値として返す
     * @param s 追加する区間
     * @return first 追加される区間の集合（入力とは異なる区間になる可能性があるので注意）
     * @return second 削除される区間の集合（もとの入力とは異なる区間になる可能性があるので注意）
     */
    std::pair<Segment, std::vector<Segment>> add(Segment s);

    /**
     * @brief 現在の状態からsに覆われた範囲を削除し、変化があった差分を戻り値として返す
     * @param s 削除する区間
     * @return first 追加される区間の集合（もとの入力とは異なる区間になる可能性があるので注意、高々サイズ2）
     * @return second 削除される区間の集合（もとの入力とは異なる区間になる可能性があるので注意）
     */
    std::pair<std::vector<Segment>, std::vector<Segment>> erase(Segment s);

    /**
     * @brief デバッグ用、全区間を取得
     * @return std::vector<Segment> 全区間（座標の昇順）
     */
    std::vector<Segment> all();

  private:
    std::map<int64_t, Segment> data;
};

SegmentManager::SegmentManager() {}

std::pair<Segment, std::vector<Segment>> SegmentManager::add(Segment s) {
    std::vector<Segment> deleted;
    for (auto it                                     = data.lower_bound(s.l);
         it != data.end() && it->second.l <= s.r; it = next(it)) {
        chmin(s.l, it->second.l);
        chmax(s.r, it->second.r);
        deleted.push_back(it->second);
    }
    for (auto& it : deleted) {
        data.erase(it.r);
    }
    data[s.r] = s;
    return std::make_pair(s, deleted);
}

std::pair<std::vector<Segment>, std::vector<Segment>>
SegmentManager::erase(Segment s) {
    std::vector<Segment> deleted;
    std::vector<Segment> inserted;

    for (auto it                                     = data.upper_bound(s.l);
         it != data.end() && it->second.l < s.r; it = next(it)) {
        if (it->second.l < s.l) {
            inserted.push_back(Segment(it->second.l, s.l));
        }
        if (it->second.r > s.r) {
            inserted.push_back(Segment(s.r, it->second.r));
        }
        deleted.push_back(it->second);
    }
    for (auto& it : deleted) {
        data.erase(it.r);
    }
    for (auto& it : inserted) {
        data[it.r] = it;
    }

    return std::make_pair(inserted, deleted);
}

std::vector<Segment> SegmentManager::all() {
    std::vector<Segment> result;
    for (auto &it:data){
        result.push_back(it.second);
    }
    return result;
}