#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

class Solution
{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums)
    {
        std::vector<std::vector<int>> res;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            int j = i + 1;
            int k = nums.size() - 1;

            while (j < k)
            {
                int total = nums[i] + nums[j] + nums[k];

                if (total > 0)
                    k--;
                else if (total < 0)
                    j++;
                else
                {
                    res.push_back({nums[i], nums[j], nums[k]});
                    j++;
                }

                while (nums[j] == nums[j - 1] && j < k)
                    j++;
            }
        }
        return res;
    }
};

void testThreeSum()
{
    Solution sol;

    {
        std::vector<int> nums{-1, 0, 1, 2, -1, -4};
        std::vector<std::vector<int>> expected{{-1, -1, 2}, {-1, 0, 1}};
        auto result = sol.threeSum(nums);

        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());

        assert(result == expected);
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main()
{
    testThreeSum();
    return 0;
}