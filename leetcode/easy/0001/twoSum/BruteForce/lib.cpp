#include <vector>

class BruteForceSolution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                if (nums[i] == target - nums[j]) {
                    return {i, j};
                }
            }
        }
        return {};
    }
};
