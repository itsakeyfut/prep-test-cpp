#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void countingSortByDigit(vector<int> &nums, int exp)
{
    vector<int> count(10, 0);

    for (int n : nums)
        ++count[(n / exp) % 10];

    for (int i = 1; i < 10; ++i)
        count[i] += count[i - 1];

    vector<int> output(nums.size());
    for (int i = static_cast<int>(nums.size()) - 1; i >= 0; --i)
    {
        int digit = (nums[i] / exp) % 10;
        output[--count[digit]] = nums[i];
    }

    nums = output;
}

void radixSort(vector<int> &nums)
{
    if (nums.empty())
        return;

    int maxVal = *max_element(nums.begin(), nums.end());
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSortByDigit(nums, exp);
}

void print(const vector<int> &nums)
{
    for (auto n : nums)
        cout << n << " ";
    cout << endl;
}

int main()
{
    vector<int> nums{170, 45, 75, 90, 802, 24, 2, 66};

    cout << "BEFORE: ";
    print(nums);

    radixSort(nums);

    cout << "AFTER: ";
    print(nums);

    return 0;
}
