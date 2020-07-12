/**
 * @file Strings.hpp
 * @author btk
 * @brief 文字列を扱いやすくするライブラリ
 */

/*<head>*/
#pragma once
#include "template/Macro.hpp"
#include <sstream>
#include <tuple>
#include <vector>
/*</head>*/

/**
 * @brief コレクションを文字列に変換する関数
 * @tparam T コレクションの型、range-based for に対応している必要あり
 * @tparam DelimiterType 区切り文字の型
 * @param v コレクション
 * @param delimiter 区切り文字
 * @return std::string delimiterで結合された文字列
 */
template <typename T, typename DelimiterType>
std::string join(const T& v, const DelimiterType& delimiter) {
    std::stringstream ss;
    bool isFirst = true;
    for (auto& it : v) {
        if (!isFirst) {
            ss << delimiter;
        }
        isFirst = false;
        ss << it;
    }
    return ss.str();
}

/**
 * @brief コレクションを文字列に変換する関数（イテレータ版）
 * @tparam ITR イテレータ型
 * @tparam DelimiterType 区切り文字の型
 * @param bg 開始
 * @param ed 終了
 * @param delimiter 区切り文字
 * @return std::string delimiterで結合された文字列
 */
template <typename ITR, typename DelimiterType>
std::string join(const ITR bg, const ITR ed, const DelimiterType& delimiter) {
    std::stringstream ss;
    bool isFirst = true;
    for (auto it = bg; it != ed; ++it) {
        if (!isFirst) {
            ss << delimiter;
        }
        isFirst = false;
        ss << *it;
    }
    return ss.str();
}

/**
 * @brief Strings.hppの内部関数
 */
namespace strings {

    /**
     * @brief std::size_tをWrapする構造体
     * @tparam i 本体
     */
    template <std::size_t i>
    struct IndexWrapper {};

    /**
     * @brief tuple用のjoin関数の内部で使われるテンプレート構造体（関数）
     * @tparam CurrentIndex 現在のindex
     * @tparam LastIndex 最後のindex
     * @tparam DelimiterType 区切り文字
     * @tparam Ts tupleに使用するパラメータパック
     */
    template <typename CurrentIndex, typename LastIndex, typename DelimiterType,
              typename... Ts>
    struct JoinFunc;


    /**
     * @brief tuple用join関数の再帰末尾用構造体 .joinが本体
     * @tparam i 現在のid = tupleの最後の要素のid
     * @tparam DelimiterType 区切り文字
     * @tparam Ts tupleに使用するパラメータパック
     */
    template <std::size_t i, typename DelimiterType, typename... Ts>
    struct JoinFunc<IndexWrapper<i>, IndexWrapper<i>, DelimiterType, Ts...> {
        /**
         * @brief tuple用join関数の末尾再帰
         * @param ss stringstream
         * @param values 文字列化したいtuple
         * @param delimiter 区切り文字
         * @return std::stringstream& 引数で渡したもの
         */
        static std::stringstream& join(std::stringstream& ss,
                                       const std::tuple<Ts...>& values,
                                       const DelimiterType& delimiter) {
            unused_var(delimiter);
            ss << std::get<i>(values);
            return ss;
        }
    };

    /**
     * @brief tuple用join関数の内部構造体
     * @tparam i 現在のid
     * @tparam j tupleの最後の要素のid
     * @tparam DelimiterType 区切り文字
     * @tparam Ts パラメータパック
     */
    template <std::size_t i, std::size_t j, typename DelimiterType,
              typename... Ts>
    struct JoinFunc<IndexWrapper<i>, IndexWrapper<j>, DelimiterType, Ts...> {
        /**
         * @brief tuple用join関数の本体
         * @param ss stringstream
         * @param values 文字列化したいtuple
         * @param delimiter 区切り文字
         * @return std::stringstream& 引数で渡したもの
         */
        static std::stringstream& join(std::stringstream& ss,
                                       const std::tuple<Ts...>& values,
                                       const DelimiterType& delimiter) {
            ss << std::get<i>(values);
            ss << delimiter;
            return JoinFunc<IndexWrapper<i + 1>, IndexWrapper<j>, DelimiterType,
                            Ts...>::join(ss, values, delimiter);
        }
    };
} // namespace strings


/**
 * @brief 複数の値をjoinする関数
 * @tparam DelimiterType 区切り文字の型
 * @tparam Ts パラメータパック
 * @param values 文字列として結合したいタプル
 * @param delimiter 区切り文字
 * @return std::string 結合後の文字列
 */
template <typename DelimiterType, typename... Ts>
std::string join(const std::tuple<Ts...>& values,
                 const DelimiterType& delimiter) {
    std::stringstream ss;
    constexpr std::size_t lastIndex =
        std::tuple_size<std::tuple<Ts...>>::value - 1u;
    return strings::JoinFunc<strings::IndexWrapper<0>,
                             strings::IndexWrapper<lastIndex>, DelimiterType,
                             Ts...>::join(ss, values, delimiter)
        .str();
}
