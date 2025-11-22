/**
 * Vector 基本操作テンプレート
 * 面接で最も頻繁に使うデータ構造
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    // ========================================
    // 1. 初期化
    // ========================================

    // 空のvector
    vector<int> v1;

    // サイズ指定（デフォルト値0）
    vector<int> v2(10);

    // サイズ + 初期値指定
    vector<int> v3(10, -1);

    // 初期値リスト
    vector<int> v4 = {1, 2, 3, 4, 5};

    // 2D配列（n×m、初期値0）
    int n = 3, m = 4;
    vector<vector<int>> grid(n, vector<int>(m));

    // 2D配列（初期値指定）
    vector<vector<int>> grid2(n, vector<int>(m, -1));

    // ========================================
    // 2. 基本操作
    // ========================================

    vector<int> nums = {1, 2, 3};

    // 末尾に追加
    nums.push_back(4); // [1, 2, 3, 4]

    // 末尾を削除
    nums.pop_back(); // [1, 2, 3]

    // サイズ
    int size = nums.size();

    // 空かどうか
    bool isEmpty = nums.empty();

    // 先頭要素
    int first = nums.front(); // 1

    // 末尾要素
    int last = nums.back(); // 3

    // 要素アクセス
    int x = nums[0];    // 1
    int y = nums.at(1); // 2（範囲チェックあり）

    // クリア
    nums.clear(); // 全削除

    // リサイズ
    nums.resize(10);    // サイズを10に
    nums.resize(5, -1); // サイズを5に、新要素は-1

    // ========================================
    // 3. イテレーション
    // ========================================

    vector<int> arr = {10, 20, 30, 40, 50};

    // 範囲for（値）
    for (int x : arr)
    {
        cout << x << " ";
    }
    cout << "\n";

    // 範囲for（参照、変更可能）
    for (int &x : arr)
    {
        x *= 2; // 各要素を2倍に
    }

    // インデックスfor
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";

    // 逆順イテレート
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";

    // ========================================
    // 4. ソート
    // ========================================

    vector<int> data = {5, 2, 8, 1, 9};

    // 昇順ソート
    sort(data.begin(), data.end());
    // [1, 2, 5, 8, 9]

    // 降順ソート
    sort(data.begin(), data.end(), greater<int>());
    // [9, 8, 5, 2, 1]

    // カスタムソート（ラムダ）
    sort(data.begin(), data.end(), [](int a, int b)
         {
             return a > b; // 降順
         });

    // ペアのソート
    vector<pair<int, int>> pairs = {{2, 1}, {1, 3}, {2, 0}};
    sort(pairs.begin(), pairs.end());
    // first優先、次にsecond

    // ========================================
    // 5. 検索
    // ========================================

    vector<int> sorted_arr = {1, 3, 5, 7, 9};

    // 線形探索
    auto it = find(sorted_arr.begin(), sorted_arr.end(), 5);
    if (it != sorted_arr.end())
    {
        int index = it - sorted_arr.begin();
        cout << "Found at index: " << index << "\n";
    }

    // 二分探索（ソート済み配列のみ）
    bool found = binary_search(sorted_arr.begin(), sorted_arr.end(), 5);

    // lower_bound（x以上の最初の位置）
    auto lb = lower_bound(sorted_arr.begin(), sorted_arr.end(), 5);
    int lb_index = lb - sorted_arr.begin();

    // upper_bound（xより大きい最初の位置）
    auto ub = upper_bound(sorted_arr.begin(), sorted_arr.end(), 5);
    int ub_index = ub - sorted_arr.begin();

    // ========================================
    // 6. その他の便利な操作
    // ========================================

    vector<int> v = {1, 2, 3, 4, 5};

    // 反転
    reverse(v.begin(), v.end());
    // [5, 4, 3, 2, 1]

    // 最大値
    int max_val = *max_element(v.begin(), v.end());

    // 最小値
    int min_val = *min_element(v.begin(), v.end());

    // 合計
    int sum = 0;
    for (int x : v)
        sum += x;

    // 重複削除（ソート後）
    vector<int> dup = {1, 2, 2, 3, 3, 3, 4};
    sort(dup.begin(), dup.end());
    dup.erase(unique(dup.begin(), dup.end()), dup.end());
    // [1, 2, 3, 4]

    // ========================================
    // 7. Prefix Sum（超頻出パターン）
    // ========================================

    vector<int> nums_ps = {1, 2, 3, 4, 5};
    int n_ps = nums_ps.size();

    // Prefix Sum配列を作成
    vector<int> prefix(n_ps + 1, 0);
    for (int i = 0; i < n_ps; i++)
    {
        prefix[i + 1] = prefix[i] + nums_ps[i];
    }
    // prefix = [0, 1, 3, 6, 10, 15]

    // 区間[l, r]の和を O(1) で計算
    int l = 1, r = 3; // インデックス1〜3
    int range_sum = prefix[r + 1] - prefix[l];
    cout << "Sum[" << l << ", " << r << "] = " << range_sum << "\n";
    // Sum[1, 3] = 9 (2+3+4)

    // ========================================
    // 8. 2D Prefix Sum
    // ========================================

    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    int rows = matrix.size();
    int cols = matrix[0].size();

    // 2D Prefix Sum配列
    vector<vector<int>> prefix2d(rows + 1, vector<int>(cols + 1, 0));

    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= cols; j++)
        {
            prefix2d[i][j] = matrix[i - 1][j - 1] + prefix2d[i - 1][j] + prefix2d[i][j - 1] - prefix2d[i - 1][j - 1];
        }
    }

    // 矩形領域 (r1,c1) から (r2,c2) の和
    auto getSum = [&](int r1, int c1, int r2, int c2)
    {
        return prefix2d[r2 + 1][c2 + 1] - prefix2d[r1][c2 + 1] - prefix2d[r2 + 1][c1] + prefix2d[r1][c1];
    };

    cout << "Sum of submatrix: " << getSum(0, 0, 1, 1) << "\n";
    // (0,0) から (1,1) の和 = 1+2+4+5 = 12

    // ========================================
    // 9. よくある例外処理パターン
    // ========================================

    vector<int> test_arr = {1, 2, 3};

    // 空配列チェック
    if (test_arr.empty())
    {
        cout << "Array is empty\n";
        return 0;
    }

    // サイズ1の処理
    if (test_arr.size() == 1)
    {
        cout << "Single element: " << test_arr[0] << "\n";
    }

    // インデックス範囲チェック
    int index = 5;
    if (index >= 0 && index < test_arr.size())
    {
        cout << test_arr[index] << "\n";
    }

    return 0;
}

/**
 * 暗記チェックリスト:
 *
 * [ ] vector の初期化（空、サイズ指定、初期値、2D）
 * [ ] push_back, pop_back, front, back
 * [ ] 範囲for と インデックスfor
 * [ ] sort（昇順、降順、カスタム）
 * [ ] find, binary_search, lower_bound, upper_bound
 * [ ] reverse, max_element, min_element
 * [ ] Prefix Sum の実装
 * [ ] 2D Prefix Sum の実装
 * [ ] 例外処理パターン
 */