#include "exercises.h"
#include <iostream>
bool betterValue(unsigned int array1[], unsigned int array2[], int n){
    int a1=0;
    int a2=0;
    for (int i = 0; i < n; ++i) {
        a1+=array1[i];
        a2+=array2[i];
    }
    return a1<=a2;
}
bool isEmpty(unsigned int arr[], int n){
    for (int i = 0; i < n; ++i) {
        if (arr[i]!=0) return false;
    }
    return true;
}
bool changeMakingUnlimitedDPBestArray(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    // TODO
    unsigned int test[n];
    unsigned int best[T+1][n];
    for (int i = 0; i < T+1; ++i) {
        for (int j = 0; j < n; ++j) {
            best[i][j]=0;
        }
        if(i<n)
            usedCoins[i]=0;
    }

    for (int i = 0; i <= n; ++i) {
        for (int k = C[i]; k <= T; ++k) {
            if(isEmpty(best[k],n)){
                for (int j = 0; j < n; ++j) {
                    if(j==i){
                        best[k][j]+=1;
                    }
                    best[k][j] += best[k - C[i]][j];
                }
            }else{
                for (int j = 0; j < n; ++j) {
                    if(j==i)
                        test[j]=1+best[k-C[i]][j];
                    else
                        test[j]=best[k-C[i]][j];
                }
                if(betterValue(test,best[k],n)){
                    for (int j = 0; j < n; ++j) {
                        best[k][j]=test[j];
                    }
                }

            }
        }
    }
    if(isEmpty(best[T],n)) return false;
    int troco=T;
    for (int i = 0; i < n; ++i) {
        usedCoins[i]=best[T][i];
        troco-=usedCoins[i]*C[i];
    }
	return troco==0;
}

bool changeMakingUnlimitedDP(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    // TODO
    unsigned int min_coins[T+1];
    unsigned int last_coin[T+1];
    for (int i = 0; i < T+1; ++i) {
        min_coins[i]=0;
        last_coin[i]=0;
        if(i<n)
            usedCoins[i]=0;
    }

    for (int i = 0; i < n; ++i) {
        for (int k = C[i]; k <= T; ++k) {

            if(min_coins[k]==0){
                min_coins[k]=k/C[i]+min_coins[k%C[i]];
                last_coin[k]=i;
            }else if (min_coins[k]>(k/C[i]+min_coins[k%C[i]])){
                min_coins[k]=k/C[i]+min_coins[k%C[i]];
                last_coin[k]=i;
            }
        }
    }
    if(min_coins[T]==0) return false;
    for (int i = n-1; i>=0; --i) {
        if(last_coin[T]==i){
            usedCoins[i] += T/C[i];
            T=T%C[i];
        }
    }
    return T==0;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex2, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 1);
    EXPECT_EQ(usedCoins[3], 3);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP4_Ex2, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);
}

TEST(TP4_Ex2, hasNoChange) {
    unsigned int C[] = {5,10};
    unsigned int n = 2;
    unsigned int usedCoins[2];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,1,usedCoins), false);
}