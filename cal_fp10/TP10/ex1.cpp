#include "exercises.h"

#include <vector>
#include <iostream>
#include <fstream>

std::vector<int> computePrefix(std::string str){
    int m = str.size();
    std::vector<int> result(m);
    result[0]=-1;
    int k=-1;

    for (int i = 1; i < m; i++) {
        while (k>=0 && str[k+1]!=str[i]){
            k=result[k];
        }
        if (str[k+1]==str[i]){
            k++;
        }
        result[i]=k;
    }

    return result;
}

int kmpMatcher(std::string text, std::string pattern) {
    int n=text.size();
    int m=pattern.size();
    std::vector<int> prefix = computePrefix(pattern);
    int q=-1;
    int result=0;
    for (int i = 0; i < n; ++i) {
        while (q>=0 && pattern[q+1]!=text[i]){
            q=prefix[q];
        }
        if (pattern[q+1]==text[i]){
            q++;
        }
        if(q==m-1){
            result++;
            q=prefix[q];
        }
    }
    return result;
}

int numStringMatching(std::string filename, std::string toSearch) {
    std::ifstream fstream(filename);
    std::string str;
    int result=0;
    while (std::getline(fstream, str)){
        result+=kmpMatcher(str, toSearch);
    }
    return result;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP10_Ex1, testKmpMatcher) {
    EXPECT_EQ(3, kmpMatcher("aaabaabaacaabaa", "aabaa"));

    EXPECT_EQ(0, kmpMatcher("", "a"));
    EXPECT_EQ(1, kmpMatcher("a", "a"));
}

#define REL_PATH std::string("../TP10/") // relative path to the tests

TEST(TP10_Ex1, testNumStringMatching) {
    int num1 = numStringMatching(REL_PATH + "text1.txt", "estrutura de dados");
    EXPECT_EQ(3, num1);

    int num2=numStringMatching(REL_PATH +"text2.txt", "estrutura de dados");
    EXPECT_EQ(2,num2);
}