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

//first draft, can be prettier :3


class CratesStacks{
public:
    //PART 1

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
    void GetStacks(std::list<char>** stacks, std::ifstream& arrangement_list) {
        std::string line;
        std::getline(arrangement_list, line);
        //every crate annotation includes 3 chars ( '[''C'']') and a ' ' between them, we use that to get the number of
        //stacks and to insert the crates in the correct stack.
        while(!line.empty()) {
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '[') {
                    stacks[i / 4]->push_front(line[i + 1]);//we always insert to the beginning of the vector
                    i += 2; //move to the next char
                }
            }
            std::getline(arrangement_list, line);
        }
    }
    void GetParams(std::string move, int* quantity, int* from_stack,int* to_stack){
        std::string helper = move.substr(move.find(' ')+1);
        //after 'move'
        *quantity = stoi(helper.substr(0,helper.find(' ')));
        helper = helper.substr(helper.find(' ')+1);
        helper = helper.substr(helper.find(' ')+1);
        //after 'from'
        *from_stack = stoi(helper.substr(0, helper.find(' ')+1)) - 1;
        helper = helper.substr(helper.find(' ')+1);
        helper = helper.substr(helper.find(' ')+1);
        //after 'to'
        *to_stack = stoi(helper) - 1;
    }
    std::string FinalOrder(){
        int stack_number = GetNumberOfStacks();

        std::ifstream arrangement_list;
        //file.txt is in cmake-debug dir
        arrangement_list.open("Crate Arrangement Day 5.txt");
        if(!arrangement_list.is_open())
            std::cout << "File did not open" << std::endl;

        std::list<char>** stacks = new std::list<char>*[stack_number];
        for(int i =0 ;i<stack_number;i++){
            stacks[i] = new std::list<char>();
        }
        GetStacks(stacks,arrangement_list);

        std::string final_order;
        std::string move;
        std::getline(arrangement_list,move);

        while(arrangement_list) {
            int quantity, from_stack, to_stack;
            GetParams(move,&quantity, &from_stack,&to_stack);
            for(int i=0; i<quantity;i++){
                if((from_stack > stack_number) || (to_stack >stack_number))
                    return final_order;
                if(!(stacks[from_stack]->empty())){
                    char target_char = stacks[from_stack]->back();
                    stacks[from_stack]->pop_back();
                    stacks[to_stack]->push_back(target_char);
                }
            }
            std::getline(arrangement_list,move);
        }

        for(int i=0; i<stack_number;i++){
            if(!(stacks[i]->empty()))
                final_order += stacks[i]->back();
        }
        arrangement_list.close();
        for(int i =0 ;i<stack_number;i++){
            delete stacks[i];
        }
        delete[] stacks;

        return final_order;
    }

    //PART 2
    std::string FinalOrderCrateMover9001(){
        int stack_number = GetNumberOfStacks();

        std::ifstream arrangement_list;
        //file.txt is in cmake-debug dir
        arrangement_list.open("Crate Arrangement Day 5.txt");
        if(!arrangement_list.is_open())
            std::cout << "File did not open" << std::endl;

        std::list<char>** stacks = new std::list<char>*[stack_number];
        for(int i =0 ;i<stack_number;i++){
            stacks[i] = new std::list<char>();
        }
        GetStacks(stacks,arrangement_list);

        std::string final_order;
        std::string move;
        std::getline(arrangement_list,move);

        while(arrangement_list) {
            int quantity, from_stack, to_stack;
            std::string target_char;
            GetParams(move,&quantity, &from_stack,&to_stack);
            for(int i=0; i<quantity;i++){
                if((from_stack > stack_number) || (to_stack >stack_number))
                    return final_order;
                if(!(stacks[from_stack]->empty())){
                    target_char += stacks[from_stack]->back();
                    stacks[from_stack]->pop_back();
                }
            }
            std::reverse(target_char.begin(),target_char.end());
            for(int i=0; i<quantity && i<target_char.length(); i++){
                stacks[to_stack]->push_back(target_char[i]);
            }
            std::getline(arrangement_list,move);
        }

        for(int i=0; i<stack_number;i++){
            if(!(stacks[i]->empty()))
                final_order += stacks[i]->back();
        }
        arrangement_list.close();
        for(int i =0 ;i<stack_number;i++){
            delete stacks[i];
        }
        delete[] stacks;
        return final_order;
    }
};
#endif //ADVENT_OF_CODE_22_DAY_5_HPP
