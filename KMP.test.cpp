/**
 * @file KMP.test.cpp
 * @author btk
 * @brief KMPのテスト
 * @date 2019-05-27
 *
 * @copyright Copyright (c) 2019
 *
 */
#define BOOST_TEST_MAIN
#include "KMP.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(KMPClass)

/**
 * @brief Construct a new boost auto test case object
 *
 */
BOOST_AUTO_TEST_CASE(find1) {
    KMP finder("abc");
    string sentence = "---abc---";
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
    string sentence = "abaabc---";
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
    string sentence = "abababab";
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
    string sentence      = "abcabc";
    int reading_len      = 0;
    vector<int> actual   = finder.find_all(sentence);
    vector<int> expected = {0, 3};
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(actual), end(actual), begin(expected),
                                  end(expected));
}

/**
 * @brief Construct a new boost auto test case object
 *
 */
BOOST_AUTO_TEST_CASE(find_all2) {
    KMP finder("abc");
    string sentence      = "abc_abc";
    int reading_len      = 0;
    vector<int> actual   = finder.find_all(sentence);
    vector<int> expected = {0, 4};
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(actual), end(actual), begin(expected),
                                  end(expected));
}

/**
 * @brief Construct a new boost auto test case object
 *
 */
BOOST_AUTO_TEST_CASE(find_all3) {
    KMP finder("a");
    string sentence      = "aaaaa";
    int reading_len      = 0;
    vector<int> actual   = finder.find_all(sentence);
    vector<int> expected = {0, 1, 2, 3, 4};
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(actual), end(actual), begin(expected),
                                  end(expected));
}

/**
 * @brief Construct a new boost auto test case object
 *
 */
BOOST_AUTO_TEST_CASE(find_all4) {
    KMP finder("aa");
    string sentence      = "aaaaa";
    int reading_len      = 0;
    vector<int> actual   = finder.find_all(sentence);
    vector<int> expected = {0, 1, 2, 3};
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(actual), end(actual), begin(expected),
                                  end(expected));
}

/**
 * @brief Construct a new boost auto test case object
 *
 */
BOOST_AUTO_TEST_CASE(find_all5) {
    KMP finder("abcabc");
    string sentence      = "abcabcabcabc";
    int reading_len      = 0;
    vector<int> actual   = finder.find_all(sentence);
    vector<int> expected = {0, 3, 6};
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(actual), end(actual), begin(expected),
                                  end(expected));
}

/**
 * @brief Construct a new boost auto test case object
 *
 */
BOOST_AUTO_TEST_CASE(period) {
    KMP finder("abcabc");
    vector<int> actual(7);
    for (int i : range(7)) actual[i] = finder.period(i);
    vector<int> expected = {3, 1, 2, 3, 3, 3, 3};
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(actual), end(actual), begin(expected),
                                  end(expected));
}

BOOST_AUTO_TEST_SUITE_END()
