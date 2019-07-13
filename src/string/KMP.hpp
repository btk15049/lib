/**
 * @file KMP.hpp
 * @author btk
 * @brief KMP
 * @date 2019-05-27
 *
 * @copyright Copyright (c) 2019
 *
 */


/*<head>*/
#pragma once
#include "template/Macro.hpp"
/*</head>*/

#include <string>
#include <vector>

/**
 * @brief KMPをするクラス
 */
class KMP {
  private:
    string keyword;
    vector<int> table;

  public:
    /**
     * @brief Construct a new KMP object
     * 番兵としてeowを末尾につける
     * @param keyword
     * @param eow
     */
    KMP(string keyword, string eow = "$") : keyword(keyword + eow) {
        const int n = this->keyword.size();
        table.resize(n);
        table[0] = -1;
        for (int i = 2, j = 0; i < n;) {
            if (keyword[i - 1] == keyword[j])
                table[i++] = ++j;
            else if (j > 0)
                j = table[j];
            else
                table[i++] = 0;
        }
    }

    /**
     * @brief
     * next_charを読んだときに
     * KMP テーブルのポインタ（どこまで一致しているか，reading_len) を進める
     * @param next_char
     * @param reading_len
     * @return true
     * @return false
     */
    inline bool advance(const char next_char, int& reading_len) {
        if (next_char != keyword[reading_len]) {
            while (reading_len >= 0 && keyword[reading_len] != next_char) {
                reading_len = table[reading_len];
            }
        }
        reading_len++;
        return reading_len == (int)keyword.size() - 1;
    }

    /**
     * @brief
     * 次のキーワードを見つける
     * @details
     * sentence のうち，tail_pos-reading_len 以降に現れる
     * 最初の keyword の末尾位置を返す ただし，
     * sentence[tail_pos-reading_len,tail_pos) == keyword[0,reading_len)
     * @param sentence
     * @param reading_len
     * @param tail_pos
     * @return int
     */
    inline int find(string& sentence, int& reading_len, int tail_pos = 0) {
        const int sentence_size = sentence.size();
        for (; tail_pos < sentence_size; tail_pos++) {
            if (advance(sentence[tail_pos], reading_len)) {
                return tail_pos + 1;
            }
        }
        return -1;
    }

    /**
     * @brief
     * sentence の中の keyword の開始位置を全部持ってくる
     * @param sentence
     * @details O(n+m)
     * @return vector<int>
     */
    vector<int> find_all(string sentence) {
        int reading_len = 0;
        int tail_pos    = 0;
        vector<int> position;
        while (1) {
            tail_pos = find(sentence, reading_len, tail_pos);
            if (tail_pos == -1) {
                break;
            }
            else {
                position.push_back(tail_pos - keyword.size() + 1);
            }
        }
        return position;
    }

    /**
     * @brief keyword[0,i)の最小周期を求める
     * @return int 最小周期長
     */
    int period(int i = 0) {
        if (i == 0) i = (int)keyword.size() - 1;
        return i - table[i];
    }
};
