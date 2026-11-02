#include <iostream>
#include <vector>

using namespace std;

void insertionSort(vector<double> &bucket)
{
    for (size_t i = 1; i < bucket.size(); ++i)
    {
        double key = bucket[i];
        size_t j = i;
        while (j > 0 && bucket[j - 1] > key)
        {
            bucket[j] = bucket[j - 1];
            --j;
        }
        bucket[j] = key;
    }
}

void bucketSort(vector<double> &nums)
{
    size_t n = nums.size();
    if (n == 0)
        return;

    vector<vector<double>> buckets(n);
    for (double x : nums)
        buckets[static_cast<size_t>(x * n)].push_back(x);

    size_t index = 0;
    for (auto &bucket : buckets)
    {
        insertionSort(bucket);
        for (double x : bucket)
            nums[index++] = x;
    }
}

void print(const vector<double> &nums)
{
    for (auto n : nums)
        cout << n << " ";
    cout << endl;
}

int main()
{
    vector<double> nums{0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};

    cout << "BEFORE: ";
    print(nums);

    bucketSort(nums);

    cout << "AFTER: ";
    print(nums);

    return 0;
}
