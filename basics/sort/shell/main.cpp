#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void shellSort(vector<int> &nums)
{
    size_t size = nums.size();
    size_t gap = size / 2;

    for (size_t gap = size / 2; gap > 0; gap /= 2)
    {
        for (size_t i{gap}; i < size; ++i)
        {
            int tmp = nums[i];
            size_t j = i;

            while (j >= gap && nums[j - gap] > tmp)
            {
                nums[j] = nums[j - gap];
                j -= gap;
            }
            nums[j] = tmp;
        }
    }
}

void print(const vector<int> &nums)
{
    for (auto n : nums)
        cout << n << " ";
    cout << endl;
}

int main()
{
    vector<int> nums{3, 22, 19, 5, 6, 83, 43, 4, 3, 27};

    cout << "BEFORE: ";
    print(nums);

    shellSort(nums);

    cout << "AFTER: ";
    print(nums);

    return 0;
}