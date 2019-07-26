/**
 * @file KMP.test.cpp
 * @author btk
 * @brief KMP.hpp のテスト
 * @date 2019-05-27
 *
 * @copyright Copyright (c) 2019
 *
 */
//! @cond
#define BOOST_TEST_MAIN
//! @endcond

#include "string/KMP.hpp"
#include "template/Loop.hpp"
#include <boost/test/included/unit_test.hpp>
#include <string>

BOOST_AUTO_TEST_SUITE(KMPClass)

/**
 * @brief Construct a new boost auto test case object
 *
 */
BOOST_AUTO_TEST_CASE(find1) {
    KMP finder("abc");
    std::string sentence = "---abc---";
    int reading_len = 0;
    BOOST_CHECK_EQUAL(finder.find(sentence, reading_len), 6);
    BOOST_CHECK_EQUAL(reading_len, 3);
}

/**
 * @brief Construct a new boost auto test case object
 *
 */
BOOST_AUTO_TEST_CASE(find2) {
    KMP finder("abc");
    std::string sentence = "abaabc---";
    int reading_len = 0;
    BOOST_CHECK_EQUAL(finder.find(sentence, reading_len), 6);
    BOOST_CHECK_EQUAL(reading_len, 3);
}

/**
 * @brief Construct a new boost auto test case object
 *
 */
BOOST_AUTO_TEST_CASE(find3) {
    KMP finder("abc");
    std::string sentence = "abababab";
    int reading_len = 0;
    BOOST_CHECK_EQUAL(finder.find(sentence, reading_len), -1);
    BOOST_CHECK_EQUAL(reading_len, 2);
}

/**
 * @brief Construct a new boost auto test case object
 *
 */
BOOST_AUTO_TEST_CASE(find_all1) {
    KMP finder("abc");
    std::string sentence      = "abcabc";
    std::vector<int> actual   = finder.find_all(sentence);
    std::vector<int> expected = {0, 3};
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(actual), std::end(actual), std::begin(expected),
                                  std::end(expected));
}

/**
 * @brief Construct a new boost auto test case object
 *
 */
BOOST_AUTO_TEST_CASE(find_all2) {
    KMP finder("abc");
    std::string sentence      = "abc_abc";
    std::vector<int> actual   = finder.find_all(sentence);
    std::vector<int> expected = {0, 4};
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(actual), std::end(actual), std::begin(expected),
                                  std::end(expected));
}

/**
 * @brief Construct a new boost auto test case object
 *
 */
BOOST_AUTO_TEST_CASE(find_all3) {
    KMP finder("a");
    std::string sentence      = "aaaaa";
    std::vector<int> actual   = finder.find_all(sentence);
    std::vector<int> expected = {0, 1, 2, 3, 4};
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(actual), std::end(actual), std::begin(expected),
                                  std::end(expected));
}

/**
 * @brief Construct a new boost auto test case object
 *
 */
BOOST_AUTO_TEST_CASE(find_all4) {
    KMP finder("aa");
    std::string sentence      = "aaaaa";
    std::vector<int> actual   = finder.find_all(sentence);
    std::vector<int> expected = {0, 1, 2, 3};
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(actual), std::end(actual), std::begin(expected),
                                  std::end(expected));
}

/**
 * @brief Construct a new boost auto test case object
 *
 */
BOOST_AUTO_TEST_CASE(find_all5) {
    KMP finder("abcabc");
    std::string sentence      = "abcabcabcabc";
    std::vector<int> actual   = finder.find_all(sentence);
    std::vector<int> expected = {0, 3, 6};
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(actual), std::end(actual), std::begin(expected),
                                  std::end(expected));
}

/**
 * @brief Construct a new boost auto test case object
 *
 */
BOOST_AUTO_TEST_CASE(period) {
    KMP finder("abcabc");
   std::vector<int> actual(7);
    for (int i : range(7)) actual[i] = finder.period(i);
    std::vector<int> expected = {3, 1, 2, 3, 3, 3, 3};
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(actual), std::end(actual), std::begin(expected),
                                  std::end(expected));
}

BOOST_AUTO_TEST_SUITE_END()
