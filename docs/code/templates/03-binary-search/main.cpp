/**
 * Binary Search（二分探索）テンプレート
 * Big Tech 面接で超頻出
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ========================================
// パターン1: 値の検索（基本）
// ========================================

int binarySearch(vector<int> &arr, int target)
{
    int l = 0, r = arr.size() - 1;

    while (l <= r)
    {
        int mid = l + (r - l) / 2; // オーバーフロー防止

        if (arr[mid] == target)
        {
            return mid; // 見つかった
        }
        else if (arr[mid] < target)
        {
            l = mid + 1; // 右半分を探索
        }
        else
        {
            r = mid - 1; // 左半分を探索
        }
    }

    return -1; // 見つからない
}

// ========================================
// パターン2: 境界探索（lower_bound 的）
// ========================================

// target 以上の最小のインデックスを返す
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

// target より大きい最小のインデックスを返す
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
// パターン3: 答えの二分探索（超重要）
// ========================================

// 例：最小値を探す
// check(x) = "x が条件を満たすか"
bool check(int x)
{
    // 条件判定ロジック
    return true;
}

int binarySearchOnAnswer()
{
    int l = 0, r = 1e9; // 探索範囲

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

// 例：最大値を探す
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
// 実戦問題パターン
// ========================================

// 問題1: Search Insert Position (LC 35)
// ソート済み配列で target を挿入すべき位置を返す
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

// 問題2: First Bad Version (LC 278)
// バージョン1〜n があり、あるバージョン以降が全てバグっている
// 最初のバグバージョンを見つける
bool isBadVersion(int version); // API（与えられる）

int firstBadVersion(int n)
{
    int l = 1, r = n;

    while (l < r)
    {
        int mid = l + (r - l) / 2;

        if (isBadVersion(mid))
        {
            r = mid; // もっと前にあるかも
        }
        else
        {
            l = mid + 1;
        }
    }

    return l;
}

// 問題3: Koko Eating Bananas (LC 875)
// バナナの山が piles = [3,6,7,11]、h=8 時間以内に食べたい
// 1時間に k 本食べられるとき、最小の k を求める
int minEatingSpeed(vector<int> &piles, int h)
{
    // k 本/時 で全部食べられるか判定
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
            r = mid; // もっと遅くできる
        }
        else
        {
            l = mid + 1;
        }
    }

    return l;
}

// 問題4: Search in Rotated Sorted Array (LC 33)
// 回転したソート済み配列から target を探す
// 例: [4,5,6,7,0,1,2]
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

// 問題5: Find Minimum in Rotated Sorted Array (LC 153)
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
// 浮動小数点数での二分探索
// ========================================

// 平方根を二分探索で求める
double sqrt(double x)
{
    double l = 0, r = x;
    double eps = 1e-9; // 精度

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

// ========================================
// デバッグのコツ
// ========================================

void debugBinarySearch()
{
    vector<int> arr = {1, 3, 5, 7, 9};
    int target = 5;

    int l = 0, r = arr.size() - 1;

    while (l <= r)
    {
        int mid = l + (r - l) / 2;

        // デバッグ出力
        cout << "l=" << l << ", r=" << r << ", mid=" << mid
             << ", arr[mid]=" << arr[mid] << "\n";

        if (arr[mid] == target)
        {
            cout << "Found at index: " << mid << "\n";
            break;
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
}

// ========================================
// よくあるミス
// ========================================

void commonMistakes()
{
    vector<int> arr = {1, 2, 3, 4, 5};

    // ❌ ミス1: オーバーフロー
    int l = 0, r = arr.size() - 1;
    int mid = (l + r) / 2; // l + r がオーバーフローする可能性

    // ✅ 正しい
    mid = l + (r - l) / 2;

    // ❌ ミス2: 無限ループ（最大値を探す時）
    l = 0;
    r = 5;
    while (l < r)
    {
        mid = (l + r) / 2; // 切り捨て
        if (check(mid))
        {
            l = mid; // mid が l と同じだと進まない
        }
        else
        {
            r = mid - 1;
        }
    }

    // ✅ 正しい（切り上げ）
    while (l < r)
    {
        mid = (l + r + 1) / 2; // +1 で切り上げ
        if (check(mid))
        {
            l = mid;
        }
        else
        {
            r = mid - 1;
        }
    }

    // ❌ ミス3: l <= r vs l < r の使い分けミス
    // 値を探す場合: l <= r
    // 境界を探す場合: l < r
}

int main()
{
    // テストケース
    vector<int> arr = {1, 3, 5, 7, 9, 11};

    cout << "Binary Search for 7: " << binarySearch(arr, 7) << "\n";
    cout << "Lower Bound of 6: " << lowerBound(arr, 6) << "\n";
    cout << "Upper Bound of 7: " << upperBound(arr, 7) << "\n";

    // Koko Eating Bananas
    vector<int> piles = {3, 6, 7, 11};
    cout << "Min eating speed: " << minEatingSpeed(piles, 8) << "\n";

    // Rotated Array
    vector<int> rotated = {4, 5, 6, 7, 0, 1, 2};
    cout << "Search 0 in rotated: " << searchRotated(rotated, 0) << "\n";
    cout << "Find min in rotated: " << findMin(rotated) << "\n";

    return 0;
}

/**
 * 暗記チェックリスト:
 *
 * [ ] パターン1: 値の検索（l <= r）
 * [ ] パターン2: 境界探索（l < r）
 * [ ] パターン3: 答えの二分探索（最小値）
 * [ ] パターン3: 答えの二分探索（最大値、+1 切り上げ）
 * [ ] mid = l + (r - l) / 2 でオーバーフロー防止
 * [ ] 回転配列での探索
 * [ ] check() 関数の設計
 * [ ] 浮動小数点数での二分探索
 * [ ] l <= r と l < r の使い分け
 */