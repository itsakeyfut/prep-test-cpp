#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int> &nums, int low, int high)
{
    int pivot = nums[high];
    int i = low - 1;

    for (size_t j = low; j < high; ++j)
    {
        if (nums[j] <= pivot)
        {
            ++i;
            swap(nums[i], nums[j]);
        }
    }

    swap(nums[i + 1], nums[high]);
    return i + 1;
}

void quickSort(vector<int> &nums, int low, int high)
{
    if (low < high)
    {
        int pi = partition(nums, low, high);
        quickSort(nums, low, pi - 1);
        quickSort(nums, pi + 1, high);
    }
}

void quickSort(vector<int> &nums)
{
    if (!nums.empty())
        quickSort(nums, 0, nums.size() - 1);
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

    quickSort(nums);

    cout << "AFTER: ";
    print(nums);

    return 0;
}