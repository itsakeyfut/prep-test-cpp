#include <iostream>
#include <vector>
#include <algorithm>

void bubbleSort(std::vector<int> &nums)
{
    for (std::size_t i{0}; i < nums.size(); ++i)
    {
        for (std::size_t j{0}; j < nums.size() - 1 - i; ++j)
        {
            if (nums[j] > nums[j + 1])
            {
                std::swap(nums[j], nums[j + 1]);
            }
        }
    }
}

void print(const std::vector<int> &nums)
{
    for (int n : nums)
        std::cout << n << " ";
    std::cout << std::endl;
}

int main()
{
    std::vector<int> nums{3, 22, 19, 5, 6, 83, 43, 4, 3, 27};

    std::cout << "BEFORE: ";
    print(nums);
    bubbleSort(nums);

    std::cout << "AFTER: ";
    print(nums);

    return 0;
}
