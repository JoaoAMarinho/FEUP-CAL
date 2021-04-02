#include "exercises.h"

Labyrinth::Labyrinth(int values[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            labyrinth[i][j] = values[i][j];
    this->initializeVisited();
}
Labyrinth::Labyrinth(const Labyrinth &l) {
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            this->labyrinth[i][j] = l.labyrinth[i][j];
            this->visited[i][j]=l.visited[i][j];
        }
    }
}

#include <iostream>

void  Labyrinth::print() const {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::cout << visited[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void Labyrinth::visit(int x, int y) {
    this->visited[y][x]= true;
}

bool Labyrinth::findGoal(int x, int y) {
    //TODO
    if((x<0 || x>9)||(y<0||y>9)) return false;
    if(this->labyrinth[y][x]==2){
        std::cout << "Exit found" << std::endl;
        return true;
    }else if(this->labyrinth[y][x]==1){
        if(this->visited[y][x]) return false;
        else
            this->visit(x,y);
    }else if(this->labyrinth[y][x]==0){
        return false;
    }

    if(findGoal(x+1,y)) return true;
    if(findGoal(x-1,y)) return true;
    if(findGoal(x,y+1)) return true;
    if(findGoal(x,y-1)) return true;
    return false;
}

void Labyrinth::initializeVisited() {
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            visited[i][j] = false;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex1, testLabyrinthPossible) {
    // This test assumes that the mazes only have a possible path to the exit
    int lab1[10][10] ={
        {0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,0,1,0,0},
        {0,1,0,0,0,1,0,1,0,0},
        {0,1,1,0,1,1,1,1,1,0},
        {0,1,0,0,0,1,0,0,0,0},
        {0,1,0,1,0,1,1,1,1,0},
        {0,1,1,1,0,0,1,0,1,0},
        {0,1,0,0,0,0,1,0,1,0},
        {0,1,1,1,0,0,1,2,0,0},
        {0,0,0,0,0,0,0,0,0,0}};

    Labyrinth l1(lab1);
    EXPECT_EQ(l1.findGoal(1,1),true);
}

TEST(TP2_Ex1, testLabyrinthImpossible) {
    int lab1[10][10] ={
            {0,0,0,0,0,0,0,0,0,0},
            {0,1,1,1,1,1,0,1,0,0},
            {0,1,0,0,0,1,0,1,0,0},
            {0,1,1,0,1,1,1,1,1,0},
            {0,1,0,0,0,1,0,0,0,0},
            {0,1,0,1,0,1,1,1,1,0},
            {0,1,1,1,0,0,1,0,1,0},
            {0,1,0,0,0,0,1,0,1,0},
            {0,1,1,1,0,0,0,2,0,0},
            {0,0,0,0,0,0,0,0,0,0}};

    Labyrinth l1(lab1);
    EXPECT_EQ(l1.findGoal(1,1),false);
}