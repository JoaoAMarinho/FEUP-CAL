// By: Gonçalo Leão

#include "exercises.h"
#include <algorithm>

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::operator<(const Activity &a2) const {
    return finish < a2.finish;
}

std::vector<Activity> earliestFinishScheduling(std::vector<Activity> A) {
    //TODO...
    //Activity = (start, finish);
    std::vector<Activity> res;
    while(!A.empty()){
        Activity firstFinish = A[0];
        int index=0;
        for(int i=0;i<A.size();i++){
            if (A[i].finish<firstFinish.finish){
                index=i;
                firstFinish=A[i];
            }
        }
        A.erase(A.begin()+index);
        res.push_back(firstFinish);
        for(int i=0;i<A.size();i++){
            if (A[i].start<firstFinish.finish){
                A.erase(A.begin()+i);
                i--;
            }
        }
    }

    return res;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex6, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = earliestFinishScheduling(A);
    EXPECT_EQ(V.size(), 3 );
    ASSERT_THAT(earliestFinishScheduling(A),  ::testing::ElementsAre(Activity(5, 15), Activity(30, 35), Activity(40, 50)));
}