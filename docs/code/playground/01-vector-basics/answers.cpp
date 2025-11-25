/**
 * Vector 基本操作 - 解答
 *
 * problems.cpp の解答です。
 * 自分で書いた後に確認してください。
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    // ========================================
    // 解答1: 初期化
    // ========================================

    // A1-1: 空のint型vectorを作成
    vector<int> v1;

    // A1-2: サイズ10、デフォルト値0のvectorを作成
    vector<int> v2(10);

    // A1-3: サイズ10、初期値-1のvectorを作成
    vector<int> v3(10, -1);

    // A1-4: {1, 2, 3, 4, 5} で初期化
    vector<int> v4 = {1, 2, 3, 4, 5};

    // A1-5: 3×4 の2D配列（初期値0）を作成
    int n = 3, m = 4;
    vector<vector<int>> grid(n, vector<int>(m));

    // A1-6: 3×4 の2D配列（初期値-1）を作成
    vector<vector<int>> grid2(n, vector<int>(m, -1));

    // ========================================
    // 解答2: 基本操作
    // ========================================

    vector<int> nums = {1, 2, 3};

    // A2-1: 末尾に4を追加
    nums.push_back(4); // [1, 2, 3, 4]

    // A2-2: 末尾の要素を削除
    nums.pop_back(); // [1, 2, 3]

    // A2-3: サイズを取得
    int size = nums.size();

    // A2-4: 空かどうか判定
    bool isEmpty = nums.empty();

    // A2-5: 先頭要素を取得
    int first = nums.front(); // 1

    // A2-6: 末尾要素を取得
    int last = nums.back(); // 3

    // A2-7: インデックス0の要素を取得（2通り）
    int x = nums[0];    // 通常のアクセス
    int y = nums.at(1); // 範囲チェックありのアクセス

    // A2-8: 全要素を削除
    nums.clear();

    // A2-9: サイズを10にリサイズ
    nums.resize(10);

    // ========================================
    // 解答3: イテレーション
    // ========================================

    vector<int> arr = {10, 20, 30, 40, 50};

    // A3-1: 範囲for（値）で全要素を出力
    for (int x : arr)
    {
        cout << x << " ";
    }
    cout << "\n";

    // A3-2: 範囲for（参照）で全要素を2倍に
    for (int &x : arr)
    {
        x *= 2;
    }

    // A3-3: インデックスforで全要素を出力
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";

    // A3-4: 逆順で全要素を出力
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";

    // ========================================
    // 解答4: ソート
    // ========================================

    vector<int> data = {5, 2, 8, 1, 9};

    // A4-1: 昇順ソート
    sort(data.begin(), data.end());

    // A4-2: 降順ソート（greater使用）
    sort(data.begin(), data.end(), greater<int>());

    // A4-3: 降順ソート（ラムダ使用）
    sort(data.begin(), data.end(), [](int a, int b)
         { return a > b; });

    // A4-4: pair<int,int>のvectorをソート
    vector<pair<int, int>> pairs = {{2, 1}, {1, 3}, {2, 0}};
    sort(pairs.begin(), pairs.end());
    // first優先、次にsecond

    // ========================================
    // 解答5: 検索
    // ========================================

    vector<int> sorted_arr = {1, 3, 5, 7, 9};

    // A5-1: 線形探索で5を探し、インデックスを出力
    auto it = find(sorted_arr.begin(), sorted_arr.end(), 5);
    if (it != sorted_arr.end())
    {
        int index = it - sorted_arr.begin();
        cout << "Found at index: " << index << "\n";
    }

    // A5-2: 二分探索で5が存在するか判定
    bool found = binary_search(sorted_arr.begin(), sorted_arr.end(), 5);

    // A5-3: lower_bound で5以上の最初の位置を取得
    auto lb = lower_bound(sorted_arr.begin(), sorted_arr.end(), 5);
    int lb_index = lb - sorted_arr.begin();

    // A5-4: upper_bound で5より大きい最初の位置を取得
    auto ub = upper_bound(sorted_arr.begin(), sorted_arr.end(), 5);
    int ub_index = ub - sorted_arr.begin();

    // ========================================
    // 解答6: その他の便利な操作
    // ========================================

    vector<int> v = {1, 2, 3, 4, 5};

    // A6-1: 配列を反転
    reverse(v.begin(), v.end());

    // A6-2: 最大値を取得
    int max_val = *max_element(v.begin(), v.end());

    // A6-3: 最小値を取得
    int min_val = *min_element(v.begin(), v.end());

    // A6-4: 重複削除（ソート後）
    vector<int> dup = {1, 2, 2, 3, 3, 3, 4};
    sort(dup.begin(), dup.end());
    dup.erase(unique(dup.begin(), dup.end()), dup.end());
    // [1, 2, 3, 4]

    // ========================================
    // 解答7: Prefix Sum（超頻出！）
    // ========================================

    vector<int> nums_ps = {1, 2, 3, 4, 5};
    int n_ps = nums_ps.size();

    // A7-1: Prefix Sum配列を作成
    vector<int> prefix(n_ps + 1, 0);
    for (int i = 0; i < n_ps; i++)
    {
        prefix[i + 1] = prefix[i] + nums_ps[i];
    }
    // prefix = [0, 1, 3, 6, 10, 15]

    // A7-2: 区間[l, r]の和を O(1) で計算
    int l = 1, r = 3;
    int range_sum = prefix[r + 1] - prefix[l];
    cout << "Sum[" << l << ", " << r << "] = " << range_sum << "\n";
    // Sum[1, 3] = 9 (2+3+4)

    // ========================================
    // 解答8: 2D Prefix Sum
    // ========================================

    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    int rows = matrix.size();
    int cols = matrix[0].size();

    // A8-1: 2D Prefix Sum配列を作成
    vector<vector<int>> prefix2d(rows + 1, vector<int>(cols + 1, 0));

    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= cols; j++)
        {
            prefix2d[i][j] = matrix[i - 1][j - 1] + prefix2d[i - 1][j] + prefix2d[i][j - 1] - prefix2d[i - 1][j - 1];
        }
    }

    // A8-2: 矩形領域 (r1,c1) から (r2,c2) の和を計算するラムダ
    auto getSum = [&](int r1, int c1, int r2, int c2)
    {
        return prefix2d[r2 + 1][c2 + 1] - prefix2d[r1][c2 + 1] - prefix2d[r2 + 1][c1] + prefix2d[r1][c1];
    };

    cout << "Sum of submatrix: " << getSum(0, 0, 1, 1) << "\n";
    // (0,0) から (1,1) の和 = 1+2+4+5 = 12

    // ========================================
    // 解答9: 例外処理パターン
    // ========================================

    vector<int> test_arr = {1, 2, 3};

    // A9-1: 空配列チェック
    if (test_arr.empty())
    {
        cout << "Array is empty\n";
        return 0;
    }

    // A9-2: サイズ1のチェック
    if (test_arr.size() == 1)
    {
        cout << "Single element: " << test_arr[0] << "\n";
    }

    // A9-3: インデックス範囲チェック
    int index = 5;
    if (index >= 0 && index < test_arr.size())
    {
        cout << test_arr[index] << "\n";
    }

    return 0;
}
