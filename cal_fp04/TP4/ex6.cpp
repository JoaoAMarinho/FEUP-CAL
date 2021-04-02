#include "exercises.h"
#include <chrono>
#include <iostream>

int maxSubsequenceDP(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    // TODO
    int sum[n];
    int index[n];
    sum[0]=A[0];
    index[0]=0;

    for (int k = 1; k < n; ++k) {
        if(sum[k-1]+A[k]>A[k]){
            sum[k]=sum[k-1]+A[k];
            index[k]=index[k-1];
        }else{
            sum[k]=A[k];
            index[k]=k;
        }
    }
    int result = A[0];
    i=0;j=0;
    for (int k = 1; k < n; ++k) {
        if(result<sum[k]){
            result=sum[k];
            i=index[k];
            j=k;
        }

    }
    return result;
}

int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    // TODO
	// Copy-paste your solution for ex2 of TP1 HERE
    int maxSum=A[0];
    int testSum;
    i=0,j=0;
    for (int k = 0; k < n; ++k) {
        for (int l = k; l < n; ++l) {
            testSum=A[k];
            for (int m = k; m < l; ++m) {
                testSum += A[m + 1];
            }
            if(testSum>maxSum){maxSum=testSum; i=k; j=l;}
        }
    }

    return maxSum;
}
int solve(int A[],unsigned int n, int left, int right,unsigned int &i,unsigned int&j){

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
int maxSubsequenceDC(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    // TODO
	// Copy-paste your solution for ex2 of TP3 HERE
    return solve(A,n,0,n-1,i,j);
}

void testPerformanceMaxSubsequence() {
	// TODO
    int A1[] = {1, 2, 3, 4};
    int A2[] = {2, -1, -3, 4};
    int A3[] = {2, -1, 3, 4};
    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int i, j;

    std::cout << "Brute Force" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    maxSubsequenceBF(A1, 4, i, j);
    maxSubsequenceBF(A2, 4, i, j);
    maxSubsequenceBF(A3, 4, i, j);
    maxSubsequenceBF(A4, 9, i, j);
    maxSubsequenceBF(A4, 9, i, j);
    maxSubsequenceBF(A4, 9, i, j);
    auto finish = std::chrono::high_resolution_clock::now();

    auto nBF = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
    std::cout << "Time Elapsed: " << nBF << " ns" << std::endl;

    std::cout << "Divide & Conquer" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    maxSubsequenceDC(A1, 4, i, j);
    maxSubsequenceDC(A2, 4, i, j);
    maxSubsequenceDC(A3, 4, i, j);
    maxSubsequenceDC(A4, 9, i, j);
    maxSubsequenceDC(A4, 9, i, j);
    maxSubsequenceDC(A4, 9, i, j);
    finish = std::chrono::high_resolution_clock::now();

    auto nDC = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
    std::cout << "Time Elapsed: " << nDC << " ns" << std::endl;

    std::cout << "Dynamic Programming" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    maxSubsequenceDP(A1, 4, i, j);
    maxSubsequenceDP(A2, 4, i, j);
    maxSubsequenceDP(A3, 4, i, j);
    maxSubsequenceDP(A4, 9, i, j);
    maxSubsequenceDP(A4, 9, i, j);
    maxSubsequenceDP(A4, 9, i, j);
    finish = std::chrono::high_resolution_clock::now();

    auto nDP = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
    std::cout << "Time Elapsed: " << nDP << " ns" << std::endl;

}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex6, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceDP(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDP(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDP(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDP(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);

    testPerformanceMaxSubsequence();
}