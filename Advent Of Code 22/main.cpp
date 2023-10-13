#include <iostream>
#include "Day 1.hpp"
#include "Day 2.hpp"
#include "Day 3.hpp"
#include "Day 4.hpp"
#include "Day 5.hpp"

int main() {
    //DAY 1
    ElfMostCalories result;
    std::cout << "Day 1, Part 1:" << result.GetMostCalories() << std::endl;
    std::cout << "Day 1, Part 2:" << result.GetTopThree() << std::endl << std::endl;

    //DAY 2
    RockPaperScissors GameResults;
    std::cout << "Day 2, Part 1:" << GameResults.CalculateTotalScore() << std::endl;
    std::cout << "Day 2, Part 2:" << GameResults.CalculateUltaStrategy() << std::endl << std::endl;

    //DAY 3
    Rucksack SumPriority;
    std::cout << "Day 3, Part 1:" << SumPriority.CalculateSumPrio() << std::endl;
    std::cout << "Day 3, Part 2:" << SumPriority.CalculateBadgeSumPrio() << std::endl << std::endl;

    //DAY 4
    CampCleanup Intersections;
    std::cout << "Day 4, Part 1:" <<Intersections.CalculateInclusionAssignments() << std::endl;
    std::cout << "Day 4, Part 1:" <<Intersections.CalculateOverlaps() << std::endl << std::endl;

    //DAY 5
    CratesStacks CrateOrder;
    std::cout << "Day 5, Part 1:" << CrateOrder.FinalOrderCrateMover9000() << std::endl;
    std::cout << "Day 5, Part 2:" << CrateOrder.FinalOrderCrateMover9001() << std::endl << std::endl;
    return 0;
}