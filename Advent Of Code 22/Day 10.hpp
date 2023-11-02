//
// Created by Aida on 11/2/2023.
//

#ifndef ADVENT_OF_CODE_22_DAY_10_HPP
#define ADVENT_OF_CODE_22_DAY_10_HPP
#include <string.h>
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>

#define NEXT_CYCLE 40

class Device{
    int reg_x;
    int current_cycle;
    int cycle_to_sample;
public:

    Device():reg_x(1),current_cycle(0),cycle_to_sample(20){};


    void checkForNewLine(){
        if(current_cycle%40 == 0){
            std::cout<< std::endl;
        }
    }
    int SumSignalStrength(){
        std::ifstream instructions_list;
        //file.txt is in cmake-debug dir
        instructions_list.open("Day 10.txt");
        if(!instructions_list.is_open())
            std::cout << "File did not open" << std::endl;

        std::string instr_str;
        std::getline(instructions_list,instr_str);
        int accum_signal_strength = 0;

        while(instructions_list){
            std::string instruction = instr_str.substr(0,instr_str.find(' '));
            if(instruction == "noop"){
                if((current_cycle == cycle_to_sample) && (cycle_to_sample <=220)){
                    accum_signal_strength+=reg_x * cycle_to_sample;
                    cycle_to_sample+=NEXT_CYCLE;
                }
                checkForNewLine();
                if ((current_cycle%40 == reg_x) || (current_cycle%40 == reg_x-1) || (current_cycle%40 ==reg_x+1)){
                    std::cout << "#";
                }else{
                    std::cout << ".";
                }
                current_cycle++;
            }else{
                if( ((current_cycle == cycle_to_sample) || (current_cycle == cycle_to_sample-1) || (current_cycle == cycle_to_sample-2))
                    && (cycle_to_sample <=220) ) {
                    accum_signal_strength+=reg_x * cycle_to_sample;

                    cycle_to_sample+=NEXT_CYCLE;

                }
                for(int i=0;i<2;i++,current_cycle++) {
                    if ((current_cycle % 40 == reg_x) ||
                        (current_cycle % 40 == reg_x - 1) ||
                        (current_cycle % 40 == reg_x + 1)) {
                        checkForNewLine();
                        std::cout << "#";
                    } else {
                        checkForNewLine();
                        std::cout << ".";
                    }
                }
                int value_to_add = stoi(instr_str.substr(instr_str.find(' ')));
                reg_x+=value_to_add;
            }

            std::getline(instructions_list,instr_str);

        }
        std::cout<< std::endl;
        instructions_list.close();
        return accum_signal_strength;
    }
};



#endif //ADVENT_OF_CODE_22_DAY_10_HPP
