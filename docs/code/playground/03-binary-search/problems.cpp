/**
 * Binary Search（二分探索）- アクティブリコール問題
 *
 * 各パターンを見ずに書いてみましょう。
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ========================================
// 問題1: 値の検索（基本パターン）
// ========================================

// Q1: target を探してインデックスを返す（見つからなければ -1）
// ヒント: l <= r を使用
int binarySearch(vector<int> &arr, int target)
{
    // TODO:
    return -1;
}

// ========================================
// 問題2: 境界探索（lower_bound 的）
// ========================================

// Q2-1: target 以上の最小インデックスを返す
// ヒント: l < r を使用、arr[mid] < target なら l = mid + 1
int lowerBound(vector<int> &arr, int target)
{
    // TODO:
    return -1;
}

// Q2-2: target より大きい最小インデックスを返す
// ヒント: arr[mid] <= target なら l = mid + 1
int upperBound(vector<int> &arr, int target)
{
    // TODO:
    return -1;
}

// ========================================
// 問題3: 答えの二分探索（最小値を探す）
// ========================================

// 例: 条件を満たす最小の値を探す
// Q3-1: check(x) が true を返す最小の x を探す
// ヒント: check(mid) が true なら r = mid
bool check(int x)
{
    // 条件判定（仮）
    return x >= 5;
}

int binarySearchOnAnswerMin()
{
    // 探索範囲: 0 ～ 1e9
    // TODO:
    return -1;
}

// ========================================
// 問題4: 答えの二分探索（最大値を探す）
// ========================================

// Q4: check(x) が true を返す最大の x を探す
// ヒント: mid の計算で +1 して切り上げ、check(mid) が true なら l = mid
int binarySearchOnAnswerMax()
{
    // 探索範囲: 0 ～ 1e9
    // TODO:
    return -1;
}

// ========================================
// 問題5: Search Insert Position (LC 35)
// ========================================

// Q5: ソート済み配列で target を挿入すべき位置を返す
// 例: [1,3,5,6], target=5 → 2
// 例: [1,3,5,6], target=2 → 1
int searchInsert(vector<int> &nums, int target)
{
    // TODO:
    return -1;
}

// ========================================
// 問題6: Koko Eating Bananas (LC 875)
// ========================================

// Q6: バナナの山 piles、h 時間以内に全部食べたい
// 1時間に k 本食べられる時、最小の k を求める
// ヒント: canFinish(k) を定義し、二分探索
int minEatingSpeed(vector<int> &piles, int h)
{
    // TODO:
    return -1;
}

// ========================================
// 問題7: Search in Rotated Sorted Array (LC 33)
// ========================================

// Q7: 回転したソート済み配列で target を探す
// 例: [4,5,6,7,0,1,2], target=0 → 4
// ヒント: 左半分 or 右半分がソート済みか判定
int searchRotated(vector<int> &nums, int target)
{
    // TODO:
    return -1;
}

// ========================================
// 問題8: Find Minimum in Rotated Sorted Array (LC 153)
// ========================================

// Q8: 回転したソート済み配列の最小値を探す
// 例: [4,5,6,7,0,1,2] → 0
// ヒント: nums[mid] > nums[r] なら最小値は右側
int findMin(vector<int> &nums)
{
    // TODO:
    return -1;
}

// ========================================
// 問題9: 浮動小数点数での二分探索
// ========================================

// Q9: 平方根を二分探索で求める
// ヒント: 精度 eps = 1e-9、r - l > eps でループ
double mySqrt(double x)
{
    // TODO:
    return -1;
}

int main()
{
    // テスト
    vector<int> arr = {1, 3, 5, 7, 9, 11};

    cout << "=== Test Cases ===\n";
    cout << "Binary Search for 7: " << binarySearch(arr, 7) << "\n";
    cout << "Lower Bound of 6: " << lowerBound(arr, 6) << "\n";
    cout << "Upper Bound of 7: " << upperBound(arr, 7) << "\n";

    vector<int> nums = {1, 3, 5, 6};
    cout << "Search Insert 2: " << searchInsert(nums, 2) << "\n";

    vector<int> piles = {3, 6, 7, 11};
    cout << "Min Eating Speed (h=8): " << minEatingSpeed(piles, 8) << "\n";

    vector<int> rotated = {4, 5, 6, 7, 0, 1, 2};
    cout << "Search 0 in rotated: " << searchRotated(rotated, 0) << "\n";
    cout << "Find min in rotated: " << findMin(rotated) << "\n";

    cout << "Sqrt(2): " << mySqrt(2) << "\n";

    return 0;
}

/**
 * チェックリスト（答えを見ずに書けたか？）:
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
