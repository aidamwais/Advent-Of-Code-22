//
// Created by Aida on 10/17/2023.
//

#ifndef ADVENT_OF_CODE_22_DAY_8_HPP
#define ADVENT_OF_CODE_22_DAY_8_HPP
#include <string.h>
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>

class TreesGrid{
public:

    void GetGridDim(int* rows, int* columns){
        std::ifstream grid;
        //file.txt is in cmake-debug dir
        grid.open("Trees Grid Day 8.txt");
        if(!grid.is_open())
            std::cout << "File did not open" << std::endl;

        std::string row;
        std::getline(grid,row);
        *rows = row.length();
        int col_num =0;
        while(grid){
            (*columns)++;
            std::getline(grid,row);
        }
        grid.close();
    }
    void FillForrest(int** forrest,int rows,int columns){
        std::ifstream grid;
        //file.txt is in cmake-debug dir
        grid.open("Trees Grid Day 8.txt");
        if(!grid.is_open())
            std::cout << "File did not open" << std::endl;

        std::string row;
        std::getline(grid,row);
        int i=0;
        while(grid){
            for(int j=0; j<columns;j++){
                forrest[i][j] = row[j] - '0';
            }
            i++;
            std::getline(grid,row);
        }

        grid.close();
    }
    bool HorizontalCheck(int** forrest, int i, int j,int rows,int columns){
        bool left=true, right=true;
        for(int k=0 ; (k<j) & left ;k++ ){
            if(forrest[i][k] >= forrest[i][j])
                left = false;
        }
        if(left)
            return true;
        for(int k=j+1; (k<columns) & right; k++){
            if(forrest[i][k] >= forrest[i][j])
                right = false;
        }

        return right;
    }
    bool VerticalCheck(int** forrest, int i, int j,int rows,int columns){
        bool top=true, bottom=true;
        for(int k=0 ; (k<i) & top ;k++ ){
            if(forrest[k][j] >= forrest[i][j])
                top = false;
        }
        if(top)
            return true;
        for(int k=i+1; (k<rows) & bottom; k++){
            if(forrest[k][j] >= forrest[i][j])
                bottom = false;
        }
        return bottom;
    }
    bool CheckIfVisible(int** forrest, int i, int j,int rows,int columns){
        return VerticalCheck(forrest,i,j,rows,columns) || HorizontalCheck(forrest,i,j,rows,columns);
    }
    int countVisible(int** forrest,int rows,int columns){
        int count = 2*(rows+columns)-4;
        for(int i=1; i<rows-1;i++ ){
            for(int j=1; j<columns-1;j++){
                if(forrest[i][j]!=0)
                    if(CheckIfVisible(forrest, i, j,rows,columns))
                        count++;
            }
        }
        return count;
    }
    int HorizontalScore(int** forrest, int i, int j,int rows,int columns){
        bool left_blocked=false, right_blocked=false;
        int left_counter = 0, right_counter = 0;
        for(int k=j-1 ; (k>=0) & !left_blocked ;k-- ){
            if(forrest[i][k] >= forrest[i][j]) {
                left_blocked = true;
                left_counter++;
            }
            else {
                left_counter++;
            }
        }

        for(int k=j+1; (k<columns) & !right_blocked; k++){
            if(forrest[i][k] >= forrest[i][j]) {
                right_blocked = true;
                right_counter++;
            }
            else {
                right_counter++;
            }
        }

        return left_counter * right_counter;
    }
    int VerticalScore(int** forrest, int i, int j,int rows,int columns){
        bool top_blocked=false, bottom_blocked=false;
        int top_counter = 0, bottom_counter = 0;
        for(int k=i-1 ; (k>=0) & !top_blocked ;k-- ){
            if(forrest[k][j] >= forrest[i][j]) {
                top_blocked = true;
                top_counter++;
            }
            else { //forrest[k][j] <= curr_highest
                top_counter++;
            }
        }

        for(int k=i+1; (k<rows) & !bottom_blocked; k++){
            if(forrest[k][j] >= forrest[i][j]) {
                bottom_blocked = true;
                bottom_counter++;
            }
            else {
                bottom_counter++;
            }
        }

        return top_counter * bottom_counter;
    }
    int GetScenicScore(int** forrest, int i, int j,int rows,int columns){
        return VerticalScore(forrest,i,j,rows,columns) *
                HorizontalScore(forrest,i,j,rows,columns);
    }
    int CalculateHighestScenicScore(int** forrest,int rows,int columns){
        int highest_score = 0;
        for(int i=1; i<rows-1;i++ ){
            for(int j=1; j<columns-1;j++){
                int current_score = GetScenicScore(forrest, i, j,rows,columns);
                if(current_score > highest_score)
                    highest_score = current_score;

            }
        }
        return highest_score;
    }
    //PART 1
    int NumVisibleTrees(){
        int rows = 0, columns = 0;
        GetGridDim(&rows,&columns);
        int** forrest = new int*[rows];
        for (int i = 0; i < rows; i++) {//memory leak
            forrest[i] = new int[columns];
        }

        FillForrest(forrest,rows,columns);
        return countVisible(forrest,rows,columns);
    }

    //PART 2
    int HighestScenicScore(){
        int rows = 0, columns = 0;
        GetGridDim(&rows,&columns);
        int** forrest = new int*[rows];
        for (int i = 0; i < rows; i++) {//memory leak
            forrest[i] = new int[columns];
        }

        FillForrest(forrest,rows,columns);
        return CalculateHighestScenicScore(forrest,rows,columns);
    }
};

#endif //ADVENT_OF_CODE_22_DAY_8_HPP
