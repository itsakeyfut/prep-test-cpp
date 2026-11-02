#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void countingSort(vector<int> &nums)
{
    if (nums.empty())
        return;

    int maxVal = *max_element(nums.begin(), nums.end());
    vector<int> count(maxVal + 1, 0);

    for (int n : nums)
        ++count[n];

    for (int i = 1; i <= maxVal; ++i)
        count[i] += count[i - 1];

    vector<int> output(nums.size());
    for (int i = static_cast<int>(nums.size()) - 1; i >= 0; --i)
    {
        output[--count[nums[i]]] = nums[i];
    }

    nums = output;
}

void print(const vector<int> &nums)
{
    for (auto n : nums)
        cout << n << " ";
    cout << endl;
}

int main()
{
    vector<int> nums{4, 2, 2, 8, 3, 3, 1, 0, 7, 5};

    cout << "BEFORE: ";
    print(nums);

    countingSort(nums);

    cout << "AFTER: ";
    print(nums);

    return 0;
}
