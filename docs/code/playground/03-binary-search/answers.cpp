/**
 * Binary Search（二分探索）- 解答
 *
 * problems.cpp の解答です。
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ========================================
// 解答1: 値の検索（基本パターン）
// ========================================

int binarySearch(vector<int> &arr, int target)
{
    int l = 0, r = arr.size() - 1;

    while (l <= r)
    {
        int mid = l + (r - l) / 2; // オーバーフロー防止

        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] < target)
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }

    return -1;
}

// ========================================
// 解答2: 境界探索
// ========================================

// target 以上の最小インデックス
int lowerBound(vector<int> &arr, int target)
{
    int l = 0, r = arr.size();

    while (l < r)
    {
        int mid = l + (r - l) / 2;

        if (arr[mid] < target)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }

    return l;
}

// target より大きい最小インデックス
int upperBound(vector<int> &arr, int target)
{
    int l = 0, r = arr.size();

    while (l < r)
    {
        int mid = l + (r - l) / 2;

        if (arr[mid] <= target)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }

    return l;
}

// ========================================
// 解答3: 答えの二分探索（最小値）
// ========================================

bool check(int x)
{
    return x >= 5;
}

int binarySearchOnAnswerMin()
{
    int l = 0, r = 1e9;

    while (l < r)
    {
        int mid = l + (r - l) / 2;

        if (check(mid))
        {
            r = mid; // 答えを小さくできる
        }
        else
        {
            l = mid + 1;
        }
    }

    return l;
}

// ========================================
// 解答4: 答えの二分探索（最大値）
// ========================================

int binarySearchOnAnswerMax()
{
    int l = 0, r = 1e9;

    while (l < r)
    {
        int mid = l + (r - l + 1) / 2; // +1 で切り上げ（重要！）

        if (check(mid))
        {
            l = mid; // 答えを大きくできる
        }
        else
        {
            r = mid - 1;
        }
    }

    return l;
}

// ========================================
// 解答5: Search Insert Position
// ========================================

int searchInsert(vector<int> &nums, int target)
{
    int l = 0, r = nums.size();

    while (l < r)
    {
        int mid = l + (r - l) / 2;

        if (nums[mid] < target)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }

    return l;
}

// ========================================
// 解答6: Koko Eating Bananas
// ========================================

int minEatingSpeed(vector<int> &piles, int h)
{
    auto canFinish = [&](int k)
    {
        long long hours = 0;
        for (int pile : piles)
        {
            hours += (pile + k - 1) / k; // 切り上げ除算
        }
        return hours <= h;
    };

    int l = 1, r = *max_element(piles.begin(), piles.end());

    while (l < r)
    {
        int mid = l + (r - l) / 2;

        if (canFinish(mid))
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }

    return l;
}

// ========================================
// 解答7: Search in Rotated Sorted Array
// ========================================

int searchRotated(vector<int> &nums, int target)
{
    int l = 0, r = nums.size() - 1;

    while (l <= r)
    {
        int mid = l + (r - l) / 2;

        if (nums[mid] == target)
            return mid;

        // 左半分がソート済みか判定
        if (nums[l] <= nums[mid])
        {
            // 左半分にtargetがあるか
            if (nums[l] <= target && target < nums[mid])
            {
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        else
        {
            // 右半分にtargetがあるか
            if (nums[mid] < target && target <= nums[r])
            {
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
    }

    return -1;
}

// ========================================
// 解答8: Find Minimum in Rotated Sorted Array
// ========================================

int findMin(vector<int> &nums)
{
    int l = 0, r = nums.size() - 1;

    while (l < r)
    {
        int mid = l + (r - l) / 2;

        if (nums[mid] > nums[r])
        {
            // 最小値は右側
            l = mid + 1;
        }
        else
        {
            // 最小値は左側（midを含む）
            r = mid;
        }
    }

    return nums[l];
}

// ========================================
// 解答9: 浮動小数点数での二分探索
// ========================================

double mySqrt(double x)
{
    double l = 0, r = x;
    double eps = 1e-9;

    // x < 1 の場合、r を調整
    if (x < 1)
        r = 1;

    while (r - l > eps)
    {
        double mid = (l + r) / 2;

        if (mid * mid < x)
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }

    return l;
}

int main()
{
    vector<int> arr = {1, 3, 5, 7, 9, 11};

    cout << "=== Test Cases ===\n";
    cout << "Binary Search for 7: " << binarySearch(arr, 7) << "\n";       // 3
    cout << "Lower Bound of 6: " << lowerBound(arr, 6) << "\n";            // 3
    cout << "Upper Bound of 7: " << upperBound(arr, 7) << "\n";            // 4

    vector<int> nums = {1, 3, 5, 6};
    cout << "Search Insert 2: " << searchInsert(nums, 2) << "\n";          // 1

    vector<int> piles = {3, 6, 7, 11};
    cout << "Min Eating Speed (h=8): " << minEatingSpeed(piles, 8) << "\n"; // 4

    vector<int> rotated = {4, 5, 6, 7, 0, 1, 2};
    cout << "Search 0 in rotated: " << searchRotated(rotated, 0) << "\n";  // 4
    cout << "Find min in rotated: " << findMin(rotated) << "\n";           // 0

    cout << "Sqrt(2): " << mySqrt(2) << "\n"; // 1.41421...

    return 0;
}
