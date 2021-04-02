#include "exercises.h"

std::string calcSum(int sequence[], unsigned long n) {
    // TODO
    //array sum
    //array index
    int sum[n];
    int index[n];
    for (int i = 0; i < n; ++i) {
        sum[i]=0;
        index[i]=0;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int sum_seq=0;
            for (int k = i; k < j+1; ++k) {
                sum_seq+=sequence[k];
            }
            if(sum[j-i]==0 || sum[j-i]>sum_seq){
                sum[j-i]=sum_seq;
                index[j-i]=i;
            }
        }
    }
    std::string result;
    for (int i = 0; i < n; ++i) {
        result+=std::to_string(sum[i])+","+std::to_string(index[i])+";";
    }
    return result;
}

void testPerformanceCalcSum() {
    //TODO
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex4, CalcSumArrayTest) {
    int sequence[5] = {4,7,2,8,1};
    int sequence2[9] = {6,1,10,3,2,6,7,2,4};

    EXPECT_EQ("1,4;9,1;11,2;18,1;22,0;",calcSum(sequence, 5));
    EXPECT_EQ("1,1;5,3;11,3;16,1;20,3;24,3;31,1;35,1;41,0;",calcSum(sequence2, 9));
	
	testPerformanceCalcSum();
}