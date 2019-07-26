/**
 * @file Macro.WhenSubmit.test.cpp
 * @author btk
 * @brief submit時のMacro.hppをテスト
 * @version 0.1
 * @date 2019-07-26
 *
 * @copyright Copyright (c) 2019
 *
 */

//! @cond
#define BOOST_TEST_MAIN
//! @endcond
#undef BTK
#include "template/Macro.hpp"
#include <boost/test/included/unit_test.hpp>
BOOST_AUTO_TEST_SUITE(Macro)
/**
 * @brief 提出時にDebugマクロが消えるかどうかテスト
 */
BOOST_AUTO_TEST_CASE(WhenSubmit) { DEBUG BOOST_FAIL("ここには来ないはず"); }
BOOST_AUTO_TEST_SUITE_END()