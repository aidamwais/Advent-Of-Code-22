//
// Created by Aida on 10/14/2023.
//

#ifndef ADVENT_OF_CODE_22_DAY_6_HPP
#define ADVENT_OF_CODE_22_DAY_6_HPP
#include <string.h>
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#define MARKER_SIZE 4
#define MESSAGE_SIZE 14
#define ERR -1

//It's 3 am, two missiles were launched nearby, as well as a masscare down south
//and I am stress coding

class StartOfPacket{
public:
    //PART 1 & 2
    bool checkValid(std::list<char>& marker,int size){
        char current_marker[size];
        int i=0;
        std::list<char>::iterator it;
        for (it = marker.begin(); it != marker.end(); it++){
            current_marker[i++] = *it;
        }
        bool check = true; //CNF kaze
        for(i=0 ;i<size; i++){
            for(int j=i+1; j<size;j++){
                check = check && (current_marker[i]!=current_marker[j]);
            }
        }
        return check;
    }
    int GetIndexOfStartMarker(int size_of_marker){
        std::ifstream signal;
        //file.txt is in cmake-debug dir
        signal.open("Signal Day 6.txt");
        if(!signal.is_open())
            std::cout << "File did not open" << std::endl;

        std::list<char> marker;
        std::string signal_line;
        std::getline(signal,signal_line);

        for(int i=0; i< size_of_marker; i++){
            marker.push_back(signal_line[i]);
        }
        if(checkValid(marker,size_of_marker)){
            return size_of_marker;
        }
        while(signal){
            int check = signal_line.length();
            for(int i=size_of_marker; i < signal_line.length();i++){
                  marker.pop_front();
                  marker.push_back(signal_line[i]);
                  if(checkValid(marker, size_of_marker)){
                      return i + 1;
                  }
            }
        }
        return ERR;
    }
};

#endif //ADVENT_OF_CODE_22_DAY_6_HPP
