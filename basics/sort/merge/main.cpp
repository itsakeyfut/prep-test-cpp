#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int> &nums, int left, int mid, int right)
{
    vector<int> leftPart(nums.begin() + left, nums.begin() + mid);
    vector<int> rightPart(nums.begin() + mid, nums.begin() + right);

    int i = 0, j = 0, k = left;

    while (i < leftPart.size() && j < rightPart.size())
    {
        if (leftPart[i] <= rightPart[j])
            nums[k++] = leftPart[i++];
        else
            nums[k++] = rightPart[j++];
    }

    while (i < leftPart.size())
        nums[k++] = leftPart[i++];
    while (j < rightPart.size())
        nums[k++] = rightPart[j++];
}

void mergeSort(vector<int> &nums, int left, int right)
{
    if (right - left <= 1)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid, right);
    merge(nums, left, mid, right);
}

void mergeSort(vector<int> &nums)
{
    mergeSort(nums, 0, nums.size());
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

    mergeSort(nums);

    cout << "AFTER: ";
    print(nums);

    return 0;
}