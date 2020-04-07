/**
 * @file Macro.hpp
 * @author btk
 * @brief マクロとか，LLとか
 * @version 0.1
 * @date 2019-07-13
 *
 * @copyright Copyright (c) 2019
 *
 */

/*<head>*/
#pragma once
#include <vector>
/*</head>*/

//! LL
using LL = long long;

/**
 * @def DEBUG
 * @brief デバッグ用のif文 提出時はif(0)で実行されない
 */

/*</head>*/
#ifdef BTK
#    define DEBUG if (1)
#else
#    ifdef CIN_ONLY
#        define FAST_IO
#    endif
#    define DEBUG if (0)
#endif
/**
 * @def ALL(v)
 * @brief
 * ALLマクロ
 */
#define ALL(v) (v).begin(), (v).end()

/**
 * @def REC(ret, ...)
 * @brief
 * 再帰ラムダをするためのマクロ
 */
#define REC(ret, ...) std::function<ret(__VA_ARGS__)>

/**
 * @def VAR_NAME(var)
 * @brief 変数名を取得する
 */
#define VAR_NAME(var) #var

/**
 * @brief
 * rangeで生まれる使わない変数を消す用（警告消し）
 */
template <typename T>
inline T& unused_var(T& v) {
    return v;
}

template<typename T>
std::vector<T>nestingVector(std::size_t size){return std::vector<T>(size);}

template <typename T,typename... Ts>
inline auto nestingVector(std::size_t size, Ts... ts){
    return std::vector<decltype(nestingVector<T>(ts...))>(size, nestingVector<T>(ts...));
}
