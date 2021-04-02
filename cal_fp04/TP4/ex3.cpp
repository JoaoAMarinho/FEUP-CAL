#include "exercises.h"

int nCoins(unsigned int array1[], int n){
    int a1=0;
    for (int i = 0; i < n; ++i) {
        a1+=array1[i];
    }
    return a1;
}
bool hasValue(unsigned int array1[], unsigned int C[], int n, int T){
    for (int i = 0; i < n; ++i) {
        T-=array1[i]*C[i];
    }
    return T==0;
}
bool isEmpty2(unsigned int arr[], int n){
    for (int i = 0; i < n; ++i) {
        if (arr[i]!=0) return false;
    }
    return true;
}

unsigned int min(unsigned int i1, unsigned int i2){
    if(i1<i2) return i1;
    else return i2;
}

bool changeMakingDP(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    // TODO

    unsigned int best[n][T+1][n];
    unsigned int max[n];
    for (int i = 0; i < n; ++i) {
        usedCoins[i]=0;
        if(i>=1)
            max[i]=Stock[i]*C[i]+max[i-1];
        else max[i]=Stock[i]*C[i];
        for (int j = 0; j < T+1; ++j) {
            for (int k = 0; k < n; ++k) {
                best[i][j][k]=0;
            }
        }
    }

    if(max[n-1]<T) return false;

    for (int i = 0; i < n; ++i) {
        for (int k = C[i]; k <= min(max[i],T); ++k) {

            best[i][k][i]+=min(Stock[i],k/C[i]);

            if(k!=(C[i]*best[i][k][i])){
                for (int j = i-1; j >= 0; --j) {
                    if(!isEmpty2(best[j][k-(C[i]*best[i][k][i])],n)) {
                        for (int l = 0; l < n; ++l) {
                            best[i][k][l]+=best[j][k-(C[i]*best[i][k][i])][l];
                        }
                        break;
                    }
                }
            }
        }
    }

    int coinsUsed=0;
    for (int i = n-1; i >= 0; --i) {
        if(hasValue(best[i][T],C,n,T)){
            if(coinsUsed==0 || nCoins(best[i][T],n)<coinsUsed){
                for (int j = 0; j < n; ++j) {
                    usedCoins[j]=best[i][T][j];
                }
                coinsUsed=nCoins(usedCoins,n);
            }
        }
    }
    return hasValue(usedCoins,C,n,T);
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex3, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP4_Ex3, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingDP(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP4_Ex3, hasNoChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingDP(C,Stock,n,1,usedCoins), false);
}