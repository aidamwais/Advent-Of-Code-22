//
// Created by Aida on 10/11/2023.
//

#ifndef ADVENT_OF_CODE_22_DAY_3_HPP
#define ADVENT_OF_CODE_22_DAY_3_HPP
#include <string.h>
#include <iostream>
#include <fstream>

#define LETTERS 26
#define ERR -1
class Rucksack{
public:

    //PART 1
    void FillCompartmentsVectors(bool* first_comp, bool* second_comp, std::string items, int comp_len){
        for(int i = 0; i < comp_len ; i++){
            //Capital letters in the ASCII table are 65 -> 90 dec. and small letters are 97-122 dec.
            int curr_index = (items[i] - 'a') < 0 ? items[i] - 'A' + LETTERS : items[i]- 'a';
            first_comp[curr_index] = true;
            curr_index = (items[comp_len + i] - 'a') < 0 ? items[comp_len + i] - 'A' + LETTERS : items[comp_len+i]- 'a';
            second_comp[curr_index] = true;
        }
    }
    int CalculateVectorIntersection(bool* first_comp, bool* second_comp,int len){
        for(int i = 0; i < len ; i++){
            if(first_comp[i] && second_comp[i]){
                return i+1;
            }
        }
    }
    int CalculateSumPrio(){
        std::ifstream rucksack;
        //file.txt is in cmake-debug dir
        rucksack.open("Compartments Items Day 3.txt");
        if(!rucksack.is_open())
            std::cout << "file did not open" << std::endl;

        int sum_priority = 0;
        std::string items;
        std::getline(rucksack,items);
        while(rucksack) {
            int comp_len = items.length() / 2;
            bool first_comp[2*LETTERS]={false}, second_comp[2*LETTERS]={false}; //std::arr for easy initialization
            FillCompartmentsVectors(first_comp, second_comp,items,comp_len);
            sum_priority+= CalculateVectorIntersection(first_comp,second_comp,2*LETTERS);
            std::getline(rucksack,items);
        }

        rucksack.close();
        return sum_priority;
    }

    //PART 2

    void FillBPVector(bool* bp_letters, std::string bp){
        for(int i = 0; i<bp.length();i++){
            int curr_index = (bp[i] - 'a') < 0 ? bp[i] - 'A' + LETTERS : bp[i]- 'a';
            bp_letters[curr_index] = true;
        }
    }
    int CalculateVectorIntersection(bool* first,bool* second,bool* third,int len){//override
        for(int i = 0; i < len ; i++){
            if(first[i] && second[i] && third[i]){
                return i+1;
            }
        }
    }
    int CalculateBadgeSumPrio(){
        std::ifstream rucksack;
        //file.txt is in cmake-debug dir
        rucksack.open("Compartments Items Day 3.txt");
        if(!rucksack.is_open())
            std::cout << "file did not open" << std::endl;

        int sum_priority = 0;
        std::string first_bp, second_bp, third_bp;
        std::getline(rucksack,first_bp);
        std::getline(rucksack,second_bp);
        std::getline(rucksack,third_bp);

        //only works if the num of rows in the file are dividable by 3
        while(rucksack) {
            if(second_bp.empty() || third_bp.empty())
                return ERR;
            bool first_letters[2*LETTERS]={false},second_letters[2*LETTERS]={false},third_letters[2*LETTERS]={false};
            FillBPVector(first_letters,first_bp);
            FillBPVector(second_letters,second_bp);
            FillBPVector(third_letters,third_bp);

            sum_priority+= CalculateVectorIntersection(first_letters,second_letters,third_letters,2*LETTERS);
            std::getline(rucksack,first_bp);
            std::getline(rucksack,second_bp);
            std::getline(rucksack,third_bp);
        }

        rucksack.close();
        return sum_priority;
    }
};



#endif //ADVENT_OF_CODE_22_DAY_3_HPP
