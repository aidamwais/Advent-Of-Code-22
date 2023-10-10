#include <iostream>
#include "Day 1.hpp"
#include "Day 2.hpp"
int main() {
    //DAY 1
    ElfMostCalories result;
    std::cout << "Day 1, Part 1:" << result.GetMostCalories() << std::endl;
    std::cout << "Day 1, Part 2:" << result.GetTopThree() << std::endl;

    //DAY 2
    RockPaperScissors GameResults;
    std::cout << "Day 2, Part 1:" << GameResults.CalculateTotalScore() << std::endl;
    std::cout << "Day 2, Part 2:" << GameResults.CalculateUltaStrategy() << std::endl;


    return 0;
}