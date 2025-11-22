#include <vector>

class Solution
{
public:
    int removeElement(std::vector<int> &nums, int val)
    {
        int idx = 0;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            if (nums[i] != val)
            {
                nums[idx] = nums[i];
                idx++;
            }
        }
        return idx;
    }
};