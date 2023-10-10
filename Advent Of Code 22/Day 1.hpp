//
// Created by Aida on 10/9/2023.
//

/**
 * Part 1:
 * The Elves take turns writing down the number of Calories contained by the various meals,
 * snacks, rations, etc. that they've brought with them, one item per line.
 * Each Elf separates their own inventory from the previous Elf's inventory (if any) by a blank line.
 *
 * Find the Elf carrying the most Calories. How many total Calories is that Elf carrying?
 *
 *
 * Part 2:
 * Find the top three Elves carrying the most Calories.
 * How many Calories are those Elves carrying in total?
 */
#ifndef ADVENT_OF_CODE_22_DAY_1_HPP
#define ADVENT_OF_CODE_22_DAY_1_HPP
#include <string.h>
#include <iostream>
#include <fstream>

class ElfMostCalories{

public:
    //Part 1
    int GetMostCalories(){
        int max_calories = 0;
        std::ifstream calories_file;
        calories_file.open("Calories Day 1.txt");
        if(!calories_file.is_open())
            std::cout << "file did not open" << std::endl;

        std::string calories_str;
        int calorie_count = 0;
        std::getline(calories_file,calories_str);

        while (calories_file){
            if(calories_str.empty()){
                if(max_calories < calorie_count)
                    max_calories = calorie_count;
                calorie_count = 0;
            }
            else{
                calorie_count += stoi(calories_str);
            }

            std::getline(calories_file, calories_str);
        }

        calories_file.close();
        return max_calories;
    }


    //Part 2
    int SortTopThree(int calorie_count, int top_three[]){
        if(calorie_count > top_three[0]){
            top_three[2] = top_three[1];
            top_three[1] = top_three[0];
            top_three[0] = calorie_count;
        }else if(calorie_count > top_three[1]){
            top_three[2] = top_three[1];
            top_three[1] = calorie_count;
        }else if(calorie_count > top_three[2])
            top_three[2] = calorie_count;
        return top_three[0]+top_three[1]+top_three[2];
    }

    int GetTopThree(){
        int top_three[3]={0};
        int max_calories = 0;

        std::ifstream calories_file;
        calories_file.open("Calories Day 1.txt");
        if(!calories_file.is_open())
            std::cout << "file did not open" << std::endl;

        std::string calories_str;
        unsigned int calorie_count = 0;
        std::getline(calories_file,calories_str);

        while (calories_file){
            if(calories_str.empty()){
                max_calories = SortTopThree(calorie_count, top_three);
                calorie_count = 0;
            }
            else {
                calorie_count += stoi(calories_str);
            }
            std::getline(calories_file,calories_str);
        }

        calories_file.close();
        return max_calories;

    }
};


#endif //ADVENT_OF_CODE_22_DAY_1_HPP
