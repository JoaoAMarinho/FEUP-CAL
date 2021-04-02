#include "exercises.h"

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::overlaps(const Activity &a2) const {
    return (start < a2.finish) && (a2.start < finish);
}

bool solveActivity(std::vector<Activity> A,std::vector<Activity> &test,Activity onGoing,std::vector<Activity> &result,std::vector<bool> canUse){
    int available=0;
    for (int i = 0; i < A.size(); ++i) {
        if (canUse[i] &&  (A[i].start<onGoing.finish)){
            canUse[i]= false;
        }
        if(canUse[i]) {available++;}
    }
    //Founded solution
    if(available==0) {
        if(test.size()>result.size()) result=std::vector<Activity>(test);
        return true;
    }
    //Keep going
    for (int i = 0; i < A.size(); ++i) {
        if(canUse[i]){
            test.push_back(A[i]);
            canUse[i]= false;
            solveActivity(A,test,A[i], result,canUse);
            canUse[i]= true;
            test.pop_back();
        }
    }
    return true;
}

std::vector<Activity> activitySelectionBacktracking(std::vector<Activity> A) {
    //TODO
    std::vector<Activity> res;
    std::vector<Activity> test;
    std::vector<bool> canUse(A.size(),true);
    for (int i = 0; i < A.size(); ++i) {
        test={};
        canUse[i]= false;
        test.push_back(A[i]);
        solveActivity(A,test,A[i],res,canUse);
        canUse[i]= true;
    }
    return res;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

bool noOverlaps(const std::vector<Activity> &acts) {
    for(unsigned int i = 0; i < acts.size(); i++) {
        Activity A1 = acts.at(i);
        for(unsigned int j = i + 1; j < acts.size(); j++) {
            Activity A2 = acts.at(j);
            if(A1.overlaps(A2)) return false;
        }
    }
    return true;
}

TEST(TP2_Ex4, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = activitySelectionBacktracking(A);
    EXPECT_EQ(V.size(), 3 );
    EXPECT_EQ(noOverlaps(V), true);
}