#include "exercises.h"

unsigned long s_recursive(unsigned int n, unsigned int k) {
    // TODO
    if(k==1 || k==n) return 1;
    else return s_recursive(n-1,k-1)+k*s_recursive(n-1,k);
}

unsigned long b_recursive(unsigned int n) {
    // TODO
    unsigned long result=0;
    for (int i = 1; i <= n; ++i) {
        result+=s_recursive(n,i);
    }
    return result;
}

unsigned long s_dynamic(unsigned int n, unsigned int k) {
    // TODO
    if(k==1 || k==n) return 1;
    unsigned int result[n+1][k+1];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k && j<=i; ++j) {
            result[i][j] = (j==1 || j==i) ? 1 : result[i-1][j-1]+j*result[i-1][j];
        }
    }
    return result[n][k];
}

unsigned long b_dynamic(unsigned int n) {
    // TODO
    unsigned long B[n+1][n+1];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n && j<=i; ++j) {
            B[i][j] = (j==1 || j==i) ? 1 : B[i-1][j-1]+j*B[i-1][j];
        }
    }
    unsigned long result=0;
    for (int i = 1; i <= n; ++i) {
        result+=B[n][i];
    }
    return result;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex5, testPartitioningRecursive) {
    EXPECT_EQ(1,s_recursive(3,3));
    EXPECT_EQ(3025,s_recursive(9,3));
    EXPECT_EQ(22827,s_recursive(10,6));

    EXPECT_EQ(5,b_recursive(3));
    EXPECT_EQ(203,b_recursive(6));
    EXPECT_EQ(1382958545,b_recursive(15));
}

TEST(TP4_Ex5, testPartitioningDynamic) {
    EXPECT_EQ(1,s_dynamic(3,3));
    EXPECT_EQ(3025,s_dynamic(9,3));
    EXPECT_EQ(22827,s_dynamic(10,6));

    EXPECT_EQ(5,b_dynamic(3));
    EXPECT_EQ(203,b_dynamic(6));
    EXPECT_EQ(1382958545,b_dynamic(15));
}