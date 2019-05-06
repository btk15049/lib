#define BOOST_TEST_MAIN
#include "Buffer.hpp"
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(BufferTest)
BOOST_AUTO_TEST_CASE(test1) {
    const double v1 = 1.23456e28;
    const double v2 = 1.23457e28;

    BOOST_CHECK_CLOSE(v1, v2, 1);
}

BOOST_AUTO_TEST_CASE(test2) {
    const double v1 = 1.23456e28;
    const double v2 = 1.23457e28;

    BOOST_CHECK_CLOSE(v1, v2, 1);
}
BOOST_AUTO_TEST_SUITE_END()