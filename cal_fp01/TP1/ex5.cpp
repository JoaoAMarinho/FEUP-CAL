// By: Gonçalo Leão

#include "exercises.h"
#include <vector>
#include <math.h>

unsigned int sumArray(unsigned int a[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

#include <iostream>

bool isCanonical(unsigned int C[], unsigned int n) {
    //TODO...
    if(n>2){
        int T;
        std::vector<int> greedySol;
        std::vector<int> exhaustiveSol;
        for(int x=C[2]+1;x<(C[n-2]+C[n-1]);x++){
            T=x;
            greedySol=std::vector<int> (n,0);
            exhaustiveSol=std::vector<int> (n,0);
            //find greedy sol
            for (int i = n-1; i >= 0 && T>0 ; --i) {
                if( C[i]<=T){
                    greedySol[i]=T/C[i];

                    T -= greedySol[i]*C[i];
                }
            }
            if(T==0){
                T=x;
                //find exaustive sol
                unsigned int Stock[n];
                int nCoins=0;
                std::vector<int> coins;
                int sum=0;

                unsigned int testResult[n];

                for (int i = 0; i < n; ++i) {
                    Stock[i]=3;
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
                                    coinsInUse+=exhaustiveSol[l];
                                    coinsInTest+=testResult[l];
                                }
                                if((coinsInUse == 0) || (coinsInTest<coinsInUse)){
                                    for (int l = 0; l < n; ++l) {
                                        exhaustiveSol[l]=testResult[l];
                                    }
                                }
                                break;
                            }
                        }
                }
                for (int l = 0; l < n; ++l) {
                    if(exhaustiveSol[l]!=greedySol[l]) return false;
                }
            }
        }

    }

    return true;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex5, canonicalTrue) {
    unsigned int C[] = {1,2,5};
    EXPECT_EQ(isCanonical(C,3), true);

    unsigned int C2[] = {1,2,5,10};
    EXPECT_EQ(isCanonical(C2,4), true);
}

TEST(TP1_Ex5, canonicalFalse) {
    unsigned int C[] = {1,4,5};
    EXPECT_EQ(isCanonical(C,3), false);
}