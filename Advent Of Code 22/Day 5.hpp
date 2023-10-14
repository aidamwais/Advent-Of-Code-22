//
// Created by Aida on 10/13/2023.
//

#ifndef ADVENT_OF_CODE_22_DAY_5_HPP
#define ADVENT_OF_CODE_22_DAY_5_HPP
#include <string.h>
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>

class Stacks {
    std::list<char>** stacks;
    int stacks_number;
public:
    explicit Stacks(int stacks_number):stacks_number(stacks_number){
        stacks = new std::list<char>*[stacks_number];
        for(int i =0 ;i<stacks_number;i++){
            stacks[i] = new std::list<char>();
        }
    }
    ~Stacks(){
        for(int i =0 ;i<stacks_number;i++){
            delete stacks[i];
        }
        delete[] stacks;
    }

    void MoveCrates(int from_stack, int to_stack,int quantity,bool reverse){
        std::string target_chars;
        for(int i=0; i<quantity;i++) {
            if ((from_stack > stacks_number) || (to_stack > stacks_number))
                return;
            if (!(stacks[from_stack]->empty())) {
                target_chars += stacks[from_stack]->back();
                stacks[from_stack]->pop_back();
            }
        }
        if(reverse) {
            std::reverse(target_chars.begin(), target_chars.end());
        }

        for(int i=0; i<quantity && i<target_chars.length(); i++){
            stacks[to_stack]->push_back(target_chars[i]);
        }
    }
    void StackInsert(int i, char target){
        stacks[i / 4]->push_front(target);
    }
    std::string GetFinalOrder(){
        std::string final_order;
        for(int i=0; i<stacks_number;i++){
            if(!(stacks[i]->empty()))
                final_order += stacks[i]->back();
        }
        return final_order;
    }

};

class CratesStacks{
public:
    int GetNumberOfStacks(){
        std::ifstream arrangement_list;
        //file.txt is in cmake-debug dir
        arrangement_list.open("Crate Arrangement Day 5.txt");
        if(!arrangement_list.is_open())
            std::cout << "File did not open" << std::endl;
        int stack_num = 0;
        std::string line;
        std::getline(arrangement_list, line);
        while(!line.empty()) {
            if(line[1] == '1'){
                stack_num = line.length()/4;
            }
            std::getline(arrangement_list, line);
        }
        arrangement_list.close();
        return stack_num+1;

    }
    void GetStacks(Stacks& stacks, std::ifstream& arrangement_list) {
        std::string line;
        std::getline(arrangement_list, line);
        //every crate annotation includes 3 chars ( '[''C'']') and a ' ' between them, which means 4 chars per crate.
        //we use that to get the number of stacks and to insert the crates in the correct stack.
        while(!line.empty()) {
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '[') {
                    stacks.StackInsert(i,line[i+1]);//we always insert to the beginning of the vector
                    i += 2; //move to the next char
                }
            }
            std::getline(arrangement_list, line);
        }
    }
    void GetParams(std::string move, int* quantity, int* from_stack,int* to_stack){
        std::string helper = move.substr(move.find("move ")+5); //5 = size of "move "
        //after 'move'
        *quantity = stoi(helper.substr(0,helper.find(' ')));
        helper = helper.substr(helper.find("from ") + 5); // 5 = size of "from "
        //after 'from'
        *from_stack = stoi(helper.substr(0, helper.find(' '))) - 1;
        helper = helper.substr(helper.find("to ")+ 3); // 3 = size of "to "
        //after 'to'
        *to_stack = stoi(helper) - 1;
    }
    //PART 1 & 2 (Part 1 with reverse = false, and Part 2 with reverse = true)
    std::string FinalOrderCrateMover(bool reverse){
        int stacks_number = GetNumberOfStacks();

        std::ifstream arrangement_list;
        //file.txt is in cmake-debug dir
        arrangement_list.open("Crate Arrangement Day 5.txt");
        if(!arrangement_list.is_open())
            std::cout << "File did not open" << std::endl;

        Stacks stacks(stacks_number);
        GetStacks(stacks,arrangement_list);

        std::string move;
        std::getline(arrangement_list,move);

        while(arrangement_list) {
            int quantity, from_stack, to_stack;
            GetParams(move,&quantity, &from_stack,&to_stack);
            stacks.MoveCrates(from_stack,to_stack,quantity,reverse);
            std::getline(arrangement_list,move);
        }

        arrangement_list.close();
        return stacks.GetFinalOrder();
    }

};
#endif //ADVENT_OF_CODE_22_DAY_5_HPP
