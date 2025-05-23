#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void bubbleSort(vector<int> &nums)
{
    size_t size = nums.size();

    for (size_t i{0}; i < size; ++i)
    {
        for (size_t j{0}; j < size - 1 - i; ++j)
        {
            if (nums[j] > nums[j + 1])
            {
                swap(nums[j], nums[j + 1]);
            }
        }
    }
}

void print(const vector<int> &nums)
{
    for (int n : nums)
        cout << n << " ";
    cout << endl;
}

int main()
{
    vector<int> nums{3, 22, 19, 5, 6, 83, 43, 4, 3, 27};

    cout << "BEFORE: ";
    print(nums);
    bubbleSort(nums);

    cout << "AFTER: ";
    print(nums);

    return 0;
}