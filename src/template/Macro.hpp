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
/*</head>*/

using namespace std;

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
 * @brief
 * rangeで生まれる使わない変数を消す用（警告消し）
 */
template <typename T>
inline T& unused_var(T& v) {
    return v;
}
