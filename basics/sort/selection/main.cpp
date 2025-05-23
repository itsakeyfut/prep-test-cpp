#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

void selectionSort(vector<int> &nums)
{
    const size_t size = nums.size();

    for (size_t i{0}; i < size; ++i)
    {
        uint32_t min_idx = i;

        for (size_t j = i + 1; j < size; ++j)
        {
            if (nums[j] < nums[min_idx])
            {
                min_idx = j;
            }
        }

        if (i != min_idx)
            swap(nums[i], nums[min_idx]);
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

    selectionSort(nums);

    cout << "AFTER: ";
    print(nums);

    return 0;
}