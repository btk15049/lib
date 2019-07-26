/**
 * @file Macro.test.cpp
 * @author btk
 * @brief
 * @version 0.1
 * @date 2019-07-26
 *
 * @copyright Copyright (c) 2019
 *
 */
//! @cond
#define BOOST_TEST_MAIN
//! @endcond

#include "template/Macro.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Macro)
BOOST_AUTO_TEST_CASE(VarName) {
    int a = 0;
    unused_var(a);
    BOOST_CHECK_EQUAL(VAR_NAME(a), "a");
}
BOOST_AUTO_TEST_SUITE_END()