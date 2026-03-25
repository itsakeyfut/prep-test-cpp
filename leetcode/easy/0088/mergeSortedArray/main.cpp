#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    void merge(std::vector<int> &nums1, int m, std::vector<int> &nums2, int n)
    {
        for (auto j = 0, i = m; j < n; j++)
        {
            nums1[i] = nums2[j];
            i++;
        }
        std::sort(nums1.begin(), nums1.end());
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    std::vector<int> nums2 = {2, 5, 6};

    int m = 3;
    int n = 3;

    solution.merge(nums1, m, nums2, n);

    std::cout << "Merged array: ";
    for (auto num : nums1)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
};