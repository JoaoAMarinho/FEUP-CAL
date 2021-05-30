#include "exercises.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

int min(std::vector<int> v){
    int min=v[0];
    for (int i = 0; i < v.size(); ++i) {
        if (v[i]<min)
            min = v[i];
    }
    return min;
}

int editDistance(std::string pattern, std::string text) {
    std::vector<std::vector<int>> vec(pattern.size()+1, std::vector<int>(text.size()+1, 0));

    for (int i = 0; i <= pattern.size(); ++i) {
        vec[i][0]=i;
    }
    for (int i = 0; i <= text.size(); ++i) {
        vec[0][i]=i;
    }

    for (int i = 0; i < pattern.size(); ++i) {
        for (int j = 0; j < text.size(); ++j) {
            if(pattern[i]==text[j])
                    vec[i+1][j+1]=vec[i][j];
            else {
                    std::vector<int> v;
                    v.push_back(vec[i][j]);
                    v.push_back(vec[i][j+1]);
                    v.push_back(vec[i+1][j]);
                    vec[i+1][j+1]=1+min(v);
            }
        }
    }

    return vec[pattern.size()][text.size()];
}

float numApproximateStringMatching(std::string filename, std::string toSearch) {
    std::ifstream fstream(filename);
    std::string str;
    float result=0;
    int numberOfWords=0;
    while (std::getline(fstream, str)){
        std::stringstream ss(str);
        while(ss>>str) {
            numberOfWords++;
            result += editDistance(toSearch, str);
        }
    }
    return result/numberOfWords;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP10_Ex2, testEditDistance) {
    EXPECT_EQ(3, editDistance("abcdefghijkl", "bcdeffghixkl"));
    EXPECT_EQ(3, editDistance("bcdeffghixkl", "abcdefghijkl"));

    EXPECT_EQ(1, editDistance("", "b"));
    EXPECT_EQ(1, editDistance("a", ""));
    EXPECT_EQ(1, editDistance("a", "b"));
    EXPECT_EQ(0, editDistance("", ""));
    EXPECT_EQ(0, editDistance("a", "a"));
}

#define REL_PATH std::string("../TP10/") // relative path to the tests

TEST(TP10_Ex2, testNumApproximateStringMatching) {
    const float delta = 0.01;

    const float expected1 = 7.76;
    float dist1 = numApproximateStringMatching(REL_PATH + "text1.txt", "estrutur");
    ASSERT_LE(expected1-delta, dist1);
    ASSERT_GE(expected1+delta, dist1);

    const float expected2 = 7.49;
    float dist2 = numApproximateStringMatching(REL_PATH + "text2.txt", "estrutur");
    ASSERT_LE(expected2-delta, dist2);
    ASSERT_GE(expected2+delta, dist2);
}