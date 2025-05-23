#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

void insertionSort(vector<int> &nums)
{
    const size_t size = nums.size();

    for (size_t i{1}; i < size; ++i)
    {
        auto tmp = nums[i];
        size_t j = i;

        while (j > 0 && nums[j - 1] > tmp)
        {
            nums[j] = nums[j - 1];
            j -= 1;
        }
        nums[j] = tmp;
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

    insertionSort(nums);

    cout << "AFTER: ";
    print(nums);

    return 0;
}