#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void cocktailSort(vector<int> &nums)
{
    size_t start{0};
    size_t end = nums.size() - 1;
    bool swapped = true;

    while (swapped)
    {
        swapped = false;

        for (size_t i{start}; i < end; ++i)
        {
            if (nums[i] > nums[i + 1])
            {
                swap(nums[i], nums[i + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;

        --end;
        swapped = false;

        for (size_t i{end}; i > start; --i)
        {
            if (nums[i - 1] > nums[i])
            {
                swap(nums[i - 1], nums[i]);
                swapped = true;
            }
        }

        ++start;
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

    cocktailSort(nums);

    cout << "AFTER: ";
    print(nums);

    return 0;
}