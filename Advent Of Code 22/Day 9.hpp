//
// Created by Aida on 10/17/2023.
//

#ifndef ADVENT_OF_CODE_22_DAY_9_HPP
#define ADVENT_OF_CODE_22_DAY_9_HPP
#include <string.h>
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>

#define SNAKE_LENGTH 10

typedef struct {
    int rows;
    int cols;
    int start_i;
    int start_j;
} Dimensions;

class PositionsBoard{
    int** board;
    int rows;
    int cols;
    int counter;
    int head_current_i;
    int head_current_j;
    int tail_current_i;
    int tail_current_j;
    int** snake;
    bool is_snake;

public:
    PositionsBoard(int rows, int cols,int start_i,int start_j,bool is_snake):rows(rows),cols(cols),
                    counter(0),head_current_i(start_i),head_current_j(start_j),
                    tail_current_i(start_i), tail_current_j(start_j),is_snake(is_snake){
        board = new int*[rows];
        for (int i = 0; i < rows; i++) {
            board[i] = new int[cols];
        }
        for(int i=0;i<rows;i++) {
            for (int j = 0; j < cols; j++) {
                board[i][j] = 0;
            }
        }
        if(is_snake){
            snake = new int*[SNAKE_LENGTH];
            for(int i=0 ; i<SNAKE_LENGTH ; i++){
                snake[i] = new int[2];
            }
            for(int i=0;i<SNAKE_LENGTH;i++) {
                snake[i][0] = start_i;
                snake[i][1] = start_j;
            }
        }
    }
    ~PositionsBoard(){
        for (int i = 0; i < rows; i++) {
            delete[] board[i];
        }
        delete[] board;
    }


    void CheckAndIncCounter(bool is_tail){
        if( (board[tail_current_i][tail_current_j] == 0) && is_tail ){
            board[tail_current_i][tail_current_j] = ++counter;
        }

    }


    void updateBoard(bool is_tail){
        if( ( (abs(head_current_i-tail_current_i) == 1) && (abs(head_current_j - tail_current_j) == 1) ) ||
            ( (head_current_j == tail_current_j) && (head_current_i == tail_current_i) ) ||
            ( (abs(head_current_i-tail_current_i) == 1) && (head_current_j == tail_current_j) ) ||
            ( (abs(head_current_j - tail_current_j) == 1) && (head_current_i == tail_current_i) ) ){
            return;
        }
        if(abs(head_current_j - tail_current_j) > 1){
            if( abs(head_current_i - tail_current_i) == 1){
                CheckAndIncCounter(is_tail);
                tail_current_i = head_current_i;
                tail_current_j = head_current_j - tail_current_j > 0 ? tail_current_j+1 : tail_current_j -1;
            }else{
                CheckAndIncCounter(is_tail);
                tail_current_j = head_current_j - tail_current_j > 0 ? tail_current_j+1 : tail_current_j -1;
            }
        }
        else if(abs(head_current_i - tail_current_i) > 1){
            if(abs(head_current_j - tail_current_j) == 1){
                CheckAndIncCounter(is_tail);
                tail_current_j = head_current_j;
                tail_current_i = head_current_i - tail_current_i > 0 ? tail_current_i+1 : tail_current_i-1;
            }else{
                CheckAndIncCounter(is_tail);
                tail_current_i = head_current_i - tail_current_i > 0 ? tail_current_i+1 : tail_current_i-1;
            }
        }

    }

    ///WE DO NOT REINVENT THE WHEEL HERE.
    void snakeUpdateBoard(){
        snake[0][0] = head_current_i;
        snake[0][1] = head_current_j;
        for(int i=0;i <SNAKE_LENGTH-1;i++){
            head_current_i = snake[i][0];
            head_current_j = snake[i][1];
            tail_current_i = snake[i+1][0];
            tail_current_j = snake[i+1][1];

            if(i+1 == SNAKE_LENGTH-1){
                updateBoard(true);
            }
            else{
                updateBoard(false);
            }

            snake[i+1][0] = tail_current_i;
            snake[i+1][1] = tail_current_j;

        }
        head_current_i = snake[0][0];
        head_current_j = snake[0][1];

    }

    void MakeAMove(char dir,int num_steps){
        for(int i = 0 ; i<num_steps ;i++){
            if(dir == 'R') {
                head_current_j++;
            }
            else if(dir == 'L'){
                head_current_j--;
            }
            else if(dir == 'U'){
                head_current_i++;
            }
            else if(dir == 'D'){
                head_current_i--;
            }
            if(is_snake){
                snakeUpdateBoard();
            }
            else {
                updateBoard(true);
            }

        }

    }


    int CalculateTailVisits(){
        std::ifstream move_list;
        //file.txt is in cmake-debug dir
        move_list.open("Motions Day 9.txt");
        if(!move_list.is_open())
            std::cout << "File did not open" << std::endl;

        std::string move;
        std::getline(move_list,move);

        while(move_list){
            int num_steps = stoi(move.substr(2));
            MakeAMove(move[0],num_steps);
            std::getline(move_list,move);

        }

        move_list.close();
        return counter == 0 ? 1: counter+is_snake;
    }
};

class RopeMotions{
public:

    void GetRouteDimensions( Dimensions* dim){
        std::ifstream move_list;
        //file.txt is in cmake-debug dir
        move_list.open("Motions Day 9.txt");
        if(!move_list.is_open())
            std::cout << "File did not open" << std::endl;

        std::string move;
        std::getline(move_list,move);

        int horizontal = 0, vertical = 0, max_right=0, max_left =0, max_up =0, max_down =0, num_steps = 0;
        while(move_list){
            num_steps = stoi(move.substr(2));
            if(move[0] == 'R') {
                horizontal +=num_steps;
                if(horizontal > max_right)
                    max_right = horizontal;
            }
            else if(move[0] == 'L'){
                horizontal -= num_steps;
                if(horizontal < max_left)
                    max_left = horizontal;
            }
            else if(move[0] == 'U'){
                vertical += num_steps;
                if(vertical > max_up)
                    max_up = vertical;
            }
            else if(move[0] == 'D'){
                vertical -= num_steps;
                if(vertical<max_down)
                    max_down = vertical;
            }
            std::getline(move_list,move);
        }
        dim->rows = max_up - max_down + 1;
        dim->cols = max_right - max_left + 1;
        dim->start_i = - max_down;
        dim->start_j = - max_left;
        move_list.close();
    }

    //PART 1
    int ShortNumOfPositionsTailVisits(){
        Dimensions dim;
        GetRouteDimensions(&dim);
        PositionsBoard position_board(dim.rows, dim.cols,dim.start_i,dim.start_j,false);
        return position_board.CalculateTailVisits();
    }

    //PART 2 - DOES NOT WORK, I DO NOT UNDERSTAND WHAT THEY WANT, BUT THIS MAKES SENSE TO ME.
    int LongNumOfPositionsTailVisits(){
        Dimensions dim;
        GetRouteDimensions(&dim);
        PositionsBoard position_board(dim.rows, dim.cols,dim.start_i,dim.start_j,true);
        return position_board.CalculateTailVisits();
    }

};
#endif //ADVENT_OF_CODE_22_DAY_9_HPP
