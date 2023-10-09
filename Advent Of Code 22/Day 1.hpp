//
// Created by Aida on 10/9/2023.
//

/**
 * The Elves take turns writing down the number of Calories contained by the various meals,
 * snacks, rations, etc. that they've brought with them, one item per line.
 * Each Elf separates their own inventory from the previous Elf's inventory (if any) by a blank line.
 *
 * Find the Elf carrying the most Calories. How many total Calories is that Elf carrying?
 */
#ifndef ADVENT_OF_CODE_22_DAY_1_HPP
#define ADVENT_OF_CODE_22_DAY_1_HPP
#include <string.h>
#include <iostream>
#include <fstream>

class ElfMostCalories{
    unsigned int max_calories = 0;
public:
    int GetMostCalories(){
        std::ifstream calories_file;
        calories_file.open("Calories Day 1.txt");
        if(!calories_file.is_open())
            std::cout << "file did not open" << std::endl;

        std::string calories_str;
        unsigned int calorie_count = 0;
        std::getline(calories_file,calories_str);

        while (calories_file){
            if(calories_str.empty()){
                if(max_calories < calorie_count)
                    max_calories = calorie_count;
                calorie_count = 0;
                std::getline(calories_file,calories_str);
                continue;
            }
            calorie_count += stoi(calories_str);
            std::getline(calories_file,calories_str);
        }

        calories_file.close();
        return max_calories;
    }
};


#endif //ADVENT_OF_CODE_22_DAY_1_HPP
