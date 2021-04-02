#include "exercises.h"

bool solveBacktracking(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[], unsigned int index, unsigned int currCoins[]){
    if(T==0){
        int used=0,curr=0;
        for (int i = 0; i < n; ++i) {
            used+=usedCoins[i];
            curr+=currCoins[i];
        }
        if(curr<used || (used==0)){
            for (int i = 0; i < n; ++i) {
                usedCoins[i]=currCoins[i];
            }
        }
        return true;
    }
    if(index>=n) return false;

    if((int)(T-C[index])>=0){
        bool sol1,sol2;
        if(Stock[index]>currCoins[index]){
            currCoins[index]++;
            sol1 = solveBacktracking(C,Stock,n,T-C[index],usedCoins,index,currCoins);
            currCoins[index]--;
        }
        sol2 = solveBacktracking(C,Stock,n,T,usedCoins,index+1,currCoins);
        if(sol1 || sol2) return true;
    }
    return false;
}

bool changeMakingBacktracking(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    //TODO
    unsigned int x[n];
    for (int i = 0; i < n; ++i) {
        usedCoins[i]=0;
        x[i]=0;
    }

    return solveBacktracking(C,Stock,n,T,usedCoins,0,x);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBacktracking(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingBacktracking(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP2_Ex3, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingBacktracking(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBacktracking(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP2_Ex3, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,1,usedCoins), false);
}