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
#include "Template.hpp"
/*</head>*/

namespace _KMP_ {
    class KMP {
      private:
        string keyword;
        vector<int> table;

      public:
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

        inline bool advance(const char next_char, int& reading_len) {
            if (next_char != keyword[reading_len]) {
                while (reading_len >= 0 && keyword[reading_len] != next_char) {
                    reading_len = table[reading_len];
                }
            }
            reading_len++;
            return reading_len == (int)keyword.size() - 1;
        }

        inline int find(string& sentence, int& reading_len, int tail_pos = 0) {
            const int sentence_size = sentence.size();
            for (; tail_pos < sentence_size; tail_pos++) {
                if (advance(sentence[tail_pos], reading_len)) {
                    return tail_pos + 1;
                }
            }
            return -1;
        }

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
} // namespace _KMP_
using namespace _KMP_;
/*
#include<bits/stdc++.h>
using namespace std;
typedef vector<int> V;
typedef vector<V> VV;
//KMP
int kmp_search(string S,string word,V& table){
    int n=S.size();
    int m=word.size();
    int i=0,j=0;
    for(;j<n&&i<m;i++,j++)
    while(i>=0&&word[i]!=S[j])i=table[i];
    if(i==m)return j-m;
    else return -1;
}


V kmp_table_build(string word){
    int n=word.size()+1;
    V table(n,0);
    table[0]=-1;
    for(int i=2,j=0;i<n;){
        if(word[i-1]==word[j])table[i++]=++j;
        else if(j>0)j=table[j];
        else table[i++]=0;
    }
    return table;
}
*/