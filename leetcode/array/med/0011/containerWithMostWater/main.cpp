#include <iostream>
#include <vector>
#include <cassert>

class Solution
{
public:
    int maxArea(std::vector<int> &height)
    {
        int left = 0;
        int right = height.size() - 1;
        int maxArea = 0;

        while (left < right)
        {
            int currArea = std::min(height[left], height[right]) * (right - left);
            maxArea = std::max(maxArea, currArea);

            if (height[left] < height[right])
                left++;
            else
                right--;
        }
        return maxArea;
    }
};

void testMaxArea()
{
    Solution sol;

    {
        std::vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
        assert(sol.maxArea(height) == 49);
    }

    {
        std::vector<int> height = {1, 1};
        assert(sol.maxArea(height) == 1);
    }

    {
        std::vector<int> height = {4, 3, 2, 1, 4};
        assert(sol.maxArea(height) == 16);
    }

    {
        std::vector<int> height = {1, 2, 1};
        assert(sol.maxArea(height) == 2);
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main()
{
    testMaxArea();
    return 0;
}