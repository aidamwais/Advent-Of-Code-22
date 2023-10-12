//
// Created by Aida on 10/12/2023.
//

#ifndef ADVENT_OF_CODE_22_DAY_4_HPP
#define ADVENT_OF_CODE_22_DAY_4_HPP
#include <string.h>
#include <iostream>
#include <fstream>

class CampCleanup{
public:
    //PART 1
    void GetRanges(int* first_range, int* second_range,std::string pair){
        size_t first_digits = pair.find(',');
        std::string first_range_str = pair.substr(0,first_digits);
        std::string second_range_str = pair.substr(first_digits+1);

        size_t first_range_pos = first_range_str.find('-');
        first_range[0] = stoi(first_range_str.substr(0, first_range_pos));
        first_range[1] = stoi(first_range_str.substr(first_range_pos+1));

        size_t second_range_pos = second_range_str.find('-');
        second_range[0] = stoi(second_range_str.substr(0,second_range_pos));
        second_range[1] = stoi(second_range_str.substr(second_range_pos+1));
    }
    bool CheckForInclusion(int* first_range, int* second_range){
        //for first_range [a,b] and second_range [c,d] check:
        // if a<c ^ b>d
        // or a>c ^ b<d
        return ( ((first_range[0] <= second_range[0]) && (first_range[1] >= second_range[1])) ||
                ((first_range[0] >= second_range[0]) && (first_range[1] <= second_range[1])) );
    }
    int CalculateInclusionAssignments(){
        std::ifstream assignment;
        //file.txt is in cmake-debug dir
        assignment.open("Assigned Sections Day 4.txt");
        if(!assignment.is_open())
            std::cout << "File did not open" << std::endl;

        int intersections_counter = 0;
        std::string pair;
        std::getline(assignment,pair);
        while(assignment) {
            int first_range[2], second_range[2];
            GetRanges(first_range,second_range, pair);
            intersections_counter+=CheckForInclusion(first_range,second_range);
            std::getline(assignment,pair);
        }

        assignment.close();
        return intersections_counter;
    }

    //PART 2

    bool CheckForOverLap(int* first_range, int* second_range){
        //for first_range [a,b] and second_range [c,d] check:
        // if one is included in the other
        // or a<c<b<d
        // or c<a<d<b
        return ( (CheckForInclusion(first_range,second_range))||
                ((first_range[0] <= second_range[0]) && (second_range[0] <= first_range[1]) && (first_range[1] <= second_range[1])) ||
                ((second_range[0] <= first_range[0]) && (first_range[0] <= second_range[1]) && (second_range[1] <= first_range[1] )) );
    }

    int CalculateOverlaps(){
        std::ifstream assignment;
        //file.txt is in cmake-debug dir
        assignment.open("Assigned Sections Day 4.txt");
        if(!assignment.is_open())
            std::cout << "File did not open" << std::endl;

        int intersections_counter = 0;
        std::string pair;
        std::getline(assignment,pair);
        while(assignment) {
            int first_range[2], second_range[2];
            GetRanges(first_range,second_range, pair);
            intersections_counter+=CheckForOverLap(first_range,second_range);
            std::getline(assignment,pair);
        }

        assignment.close();
        return intersections_counter;
    }
};


#endif //ADVENT_OF_CODE_22_DAY_4_HPP
