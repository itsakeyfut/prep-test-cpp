#include <iostream>
#include <vector>

using namespace std;

void heapify(vector<int> &nums, int size, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && nums[left] > nums[largest])
        largest = left;

    if (right < size && nums[right] > nums[largest])
        largest = right;

    if (largest != i)
    {
        swap(nums[i], nums[largest]);
        heapify(nums, size, largest);
    }
}

void heapSort(vector<int> &nums)
{
    int size = nums.size();

    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(nums, size, i);
    }

    for (int i = size - 1; i >= 0; i--)
    {
        swap(nums[0], nums[i]);
        heapify(nums, i, 0);
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

    heapSort(nums);

    cout << "AFTER: ";
    print(nums);

    return 0;
}