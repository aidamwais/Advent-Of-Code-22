//
// Created by Aida on 10/10/2023.
//


/**
 * Part 1:
 * one Elf gives you an encrypted strategy guide (your puzzle input) that they say
 * will be sure to help you win. "The first column is what your opponent is going to play:
 * A for Rock, B for Paper, and C for Scissors. The second column, you reason,
 * must be what you should play in response: X for Rock, Y for Paper, and Z for Scissors.
 * Winning every time would be suspicious, so the responses must have been carefully chosen.
 * The winner of the whole tournament is the player with the highest score.
 *
 * Your total score is the sum of your scores for each round. The score for a single round
 * is the score for the shape you selected (1 for Rock, 2 for Paper, and 3 for Scissors)
 * plus the score for the outcome of the round (0 if you lost, 3 if the round was a draw, and 6 if you won).
 *
 *
 * Part 2:
 * "the second column says how the round needs to end: X means you need to lose,
 * Y means you need to end the round in a draw, and Z means you need to win "
 * Following the Elf's instructions for the second column,
 * what would your total score be if everything goes exactly according to your strategy guide?
 */
#ifndef ADVENT_OF_CODE_22_DAY_2_HPP
#define ADVENT_OF_CODE_22_DAY_2_HPP
#include <string.h>
#include <iostream>
#include <fstream>
//replace with enum, easier
#define ROCK 1
#define PAPER 2
#define SCISSORS 3
#define LOSS 0
#define DRAW 3
#define WIN 6
#define LOSS_MOVE 1
#define DRAW_MOVE 2
#define WIN_MOVE 3

class RockPaperScissors{
public:

    //PART 1
    int CharToPoints(char input) {
        switch (input) {
        case 'A': return ROCK;
            break;
        case 'B': return PAPER;
            break;
        case 'C': return SCISSORS;
            break;
        case 'X': return ROCK;
            break;
        case 'Y': return PAPER;
            break;
        case 'Z': return SCISSORS;
            break;
        }
    }
    int CalculatePoints(int opponent_pick, int player_pick){
        //case for loss
        if( ((opponent_pick == ROCK) && (player_pick == SCISSORS)) ||
            ((opponent_pick == SCISSORS) && (player_pick == PAPER)) ||
            ((opponent_pick == PAPER) && (player_pick == ROCK))){
            return player_pick;
        }
        //case for draw
        else if( ((opponent_pick == ROCK) && (player_pick == ROCK)) ||
                 ((opponent_pick == SCISSORS) && (player_pick == SCISSORS)) ||
                 ((opponent_pick == PAPER) && (player_pick == PAPER))) {
            return player_pick + DRAW;
        }
        else{
            return player_pick + WIN;
        }
    }
    int CalculateTotalScore(){
        std::ifstream strat_guide;
        //file.txt is in cmake-debug dir
        strat_guide.open("Strategy Guide Day 2.txt");
        if(!strat_guide.is_open())
            std::cout << "file did not open" << std::endl;

        int sum_of_scores = 0;
        std::string round;
        std::getline(strat_guide,round);

        while (strat_guide){
            int opponent_pick = CharToPoints(round[0]);
            int player_pick = CharToPoints(round[2]);
            sum_of_scores += CalculatePoints(opponent_pick, player_pick);

            std::getline(strat_guide,round);
        }

        strat_guide.close();
        return sum_of_scores;
    }

    //PART 2
    int CalculateMovePoints(int opponent_pick, int best_move){
        if(best_move == WIN_MOVE){
            return WIN + ((opponent_pick%3) + 1) ;
        }else if(best_move == DRAW_MOVE){
            return DRAW + opponent_pick;
        }else{
            //trust me it works
            return LOSS + ( (opponent_pick + 1)%3 + 1);
        }
    }

    int CalculateUltaStrategy(){
        std::ifstream strat_guide;
        //file.txt is in cmake-debug dir
        strat_guide.open("Strategy Guide Day 2.txt");
        if(!strat_guide.is_open())
            std::cout << "file did not open" << std::endl;

        int sum_of_scores = 0;
        std::string round;
        std::getline(strat_guide,round);

        while (strat_guide){
            int opponent_pick = CharToPoints(round[0]);
            int best_move = CharToPoints(round[2]);
            sum_of_scores += CalculateMovePoints(opponent_pick, best_move);

            std::getline(strat_guide,round);
        }

        strat_guide.close();
        return sum_of_scores;
    }


};
#endif //ADVENT_OF_CODE_22_DAY_2_HPP
