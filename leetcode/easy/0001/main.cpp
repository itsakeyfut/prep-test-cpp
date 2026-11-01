#include <iostream>
#include <vector>
#include <string>

#include "BruteForce/lib.cpp"
#include "HashMap/lib.cpp"

void printResult(const std::string &label, const std::vector<int> &result)
{
    std::cout << "[" << label << "] ";
    if (!result.empty())
    {
        std::cout << "Indices: " << result[0] << ", " << result[1] << std::endl;
    }
    else
    {
        std::cout << "No solution found." << std::endl;
    }
}

int main()
{
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    BruteForceSolution bf;
    printResult("BruteForce", bf.twoSum(nums, target));

    HashMapSolution hm;
    printResult("HashMap  ", hm.twoSum(nums, target));

    return 0;
}
