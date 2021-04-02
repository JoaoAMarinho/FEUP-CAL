#include "exercises.h"

int solve(int A[],unsigned int n, int left, int right, int &i,int&j){

    int middle=(left+right)/2;

    if(right-left==0){
        i=left;
        j=left;
        return A[left];
    }
    else{
        int testResLeft = solve(A,n,left,middle, i ,j);
        int testResRight=solve(A,n,middle+1,right,i,j);
        int testRes;
        if(testResLeft>testResRight) testRes = testResLeft;
        else testRes = testResRight;

        int temp=0;
        testResLeft=0,testResRight=0;
        int indexL=middle,indexR=middle+1;
        for (int k = middle; k >= left; --k) {
            temp+=A[k];
            if(temp > testResLeft) { testResLeft=temp;indexL=k;}
        }
        temp=0;
        for (int k = middle+1; k <= right; ++k) {
            temp+=A[k];
            if(temp>testResRight) {testResRight=temp;indexR=k;}
        }
        if(testResRight + testResLeft > testRes){ i=indexL;j=indexR; testRes= testResRight + testResLeft;}
        if(testResRight>testRes) {i=middle+1;j=indexR; testRes=testResRight;}
        if(testResLeft > testRes) { i=indexL;j=middle; testRes=testResLeft;}

        return testRes;
    }
}

int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    //TODO
    return solve(A,n,0,n-1,i,j);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex2, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    int i, j;
    EXPECT_EQ(maxSubsequenceDC(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDC(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDC(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDC(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}
