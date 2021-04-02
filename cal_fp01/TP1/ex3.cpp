// By: Gonçalo Leão

#include "exercises.h"
#include <vector>
#include <iostream>
#include <math.h>

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    //TODO...
    int nCoins=0;
    std::vector<int> coins;
    int sum=0;

    unsigned int testResult[n];

    for (int i = 0; i < n; ++i) {
        usedCoins[i]=0;
        for (int j = 0; j < Stock[i]; ++j) {
            coins.push_back(C[i]);
        }
    }
    for (int i = 1; i < pow(2,coins.size())-1; ++i) {
        sum=0;
        for (int j = 0; j < n; ++j) {
            testResult[j]=0;
        }
        for (int j = 0, k = 1; j < coins.size(); ++j, k <<= 1)
            if ((k & i) != 0){
                sum+=coins[j];
                for (int l = 0; l < n; ++l) {
                    if(C[l]==coins[j]){
                        testResult[l]++;
                        break;
                    }
                }
                if(sum == T){
                    int coinsInUse=0, coinsInTest=0;
                    for (int l = 0; l < n; ++l) {
                        coinsInUse+=usedCoins[l];
                        coinsInTest+=testResult[l];
                    }
                    if((coinsInUse == 0) || (coinsInTest<coinsInUse)){
                        for (int l = 0; l < n; ++l) {
                            usedCoins[l]=testResult[l];
                        }
                    }
                    break;
                }
            }
    }
    int x=0;
    for (int l = 0; l < n; ++l) {
        x+=usedCoins[l];
    }
    return (x>0);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex3, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP1_Ex3, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP1_Ex3, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}
