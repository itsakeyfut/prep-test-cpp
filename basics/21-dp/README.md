# Dynamic Programming - 動的計画法

## 概要
動的計画法（DP）は、大きな問題を小さな部分問題に分け、部分問題の答えを表（配列）に保存して再利用する手法です。同じ計算を何度も繰り返す再帰を、表を埋める作業に置き換えることで指数時間を多項式時間に落とします。

## 目的
- 「最大・最小・何通り」を問う問題で、DP を第一候補として思いつけるようにする
- メモ化（トップダウン）とテーブル（ボトムアップ）の2つの書き方を使い分けられるようにする
- ナップサック・LCS・LIS・コイン問題という頻出の型を覚え、応用問題を「どの型か」で分類できるようにする

## 達成条件
- [ ] 何も見ずに main.cpp を15分以内に手書きできる
- [ ] 各問題について、状態・遷移・初期値を自分の言葉で説明できる
- [ ] メモ化再帰とボトムアップの違い（計算順序・スタック使用量）を説明できる
- [ ] 0/1 ナップサックで 1次元 dp の内側ループを逆順に回す理由を説明できる
- [ ] LIS の O(n log n) 解で `tails` が何を表すか説明できる
- [ ] LeetCode 70. Climbing Stairs / 509. Fibonacci Number を解ける
- [ ] LeetCode 322. Coin Change を解ける
- [ ] LeetCode 1143. Longest Common Subsequence を解ける
- [ ] LeetCode 300. Longest Increasing Subsequence を解ける
- [ ] LeetCode 416. Partition Equal Subset Sum（ナップサックの応用）を解ける
- [ ] LeetCode 198. House Robber を解ける

## DPの動き
LCS（`"abcde"` と `"ace"`）の表。`dp[i][j]` = `a` の先頭 i 文字と `b` の先頭 j 文字の LCS 長：

```
        ""  a   c   e
    ""   0  0   0   0
    a    0  1↖  1   1
    b    0  1   1   1
    c    0  1   2↖  2
    d    0  1   2   2
    e    0  1   2   3↖     ← 答え dp[5][3] = 3

↖ : 文字が一致 → 左上 + 1
それ以外 : max(上, 左)
```

コイン問題（coins = {1, 2, 5}, amount = 11）。`dp[a]` = 金額 a を作る最小枚数：

```
a    : 0  1  2  3  4  5  6  7  8  9  10  11
dp[a]: 0  1  1  2  2  1  2  2  3  3   2   3   ← 5 + 5 + 1
```

## コードの解説

### フィボナッチ：メモ化（main.cpp:6-13）
```cpp
long long fib_memo(int n, std::vector<long long> &memo)
{
    if (n <= 1)
        return n;                   // 初期値: fib(0)=0, fib(1)=1
    if (memo[n] != -1)
        return memo[n];             // 計算済みなら再利用
    return memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);
}
```
- 状態: `fib(n)`、遷移: `fib(n) = fib(n-1) + fib(n-2)`
- 素朴な再帰は O(2^n)、メモ化で O(n)

### フィボナッチ：テーブル（main.cpp:15-26）
```cpp
long long fib_table(int n)
{
    if (n <= 1)
        return n;
    std::vector<long long> dp(n + 1, 0);
    dp[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        dp[i] = dp[i - 1] + dp[i - 2];  // 小さい方から順に埋める
    }
    return dp[n];
}
```
- 再帰を使わないのでスタックオーバーフローの心配がない

### 0/1 ナップサック（main.cpp:28-39）
```cpp
int knapsack(const std::vector<int> &weights, const std::vector<int> &values, int capacity)
{
    std::vector<int> dp(capacity + 1, 0);       // dp[w] = 容量 w での最大価値
    for (std::size_t i = 0; i < weights.size(); ++i)
    {
        for (int w = capacity; w >= weights[i]; --w)   // 逆順！
        {
            dp[w] = std::max(dp[w],                       // 入れない
                             dp[w - weights[i]] + values[i]); // 入れる
        }
    }
    return dp[capacity];
}
```
- 逆順に回すことで、同じ品物を2回使わない（`dp[w - weights[i]]` がまだ更新前の値）
- 正順にすると「個数無制限ナップサック」になる

### LCS（main.cpp:41-57）
```cpp
int lcs(const std::string &a, const std::string &b)
{
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    for (std::size_t i = 1; i <= n; ++i)
        for (std::size_t j = 1; j <= m; ++j)
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;           // 一致: 左上 + 1
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]); // 不一致: 上と左の大きい方
    return dp[n][m];
}
```
- 0 行目・0 列目は空文字列との LCS なので 0（初期値）
- 添字が 1 ずれる（`dp[i]` は `a[i-1]` まで）点に注意

### LIS O(n^2)（main.cpp:59-73）
```cpp
std::vector<int> dp(nums.size(), 1);     // dp[i] = nums[i] で終わる LIS の長さ
for (std::size_t i = 1; i < nums.size(); ++i)
    for (std::size_t j = 0; j < i; ++j)
        if (nums[j] < nums[i])
            dp[i] = std::max(dp[i], dp[j] + 1);  // j の後ろに i をつなげる
return *std::max_element(dp.begin(), dp.end());
```
- 答えは `dp[n-1]` ではなく全体の最大値

### LIS O(n log n)（main.cpp:75-87）
```cpp
std::vector<int> tails;   // tails[k] = 長さ k+1 の増加列の末尾の最小値
for (int x : nums)
{
    auto it = std::lower_bound(tails.begin(), tails.end(), x);
    if (it == tails.end())
        tails.push_back(x);   // 最長を更新
    else
        *it = x;              // より小さい末尾に置き換え
}
return static_cast<int>(tails.size());
```
- `tails` は常にソート済みなので二分探索できる
- `tails` の中身そのものは LIS ではない（長さだけが正しい）

### コイン問題（main.cpp:89-103）
```cpp
int coin_change(const std::vector<int> &coins, int amount)
{
    const int INF = amount + 1;            // 「作れない」を表す大きな値
    std::vector<int> dp(amount + 1, INF);
    dp[0] = 0;                             // 0 円は 0 枚
    for (int a = 1; a <= amount; ++a)
        for (int c : coins)
            if (c <= a)
                dp[a] = std::min(dp[a], dp[a - c] + 1);  // 最後に c を使う
    return dp[amount] == INF ? -1 : dp[amount];
}
```
- `INT_MAX` を使うと `+1` でオーバーフローするので `amount + 1` を INF にする

## 計算量
| 関数 | 時間 | 空間 |
|------|------|------|
| fib_memo / fib_table | O(n) | O(n) |
| knapsack | O(N · W) | O(W) |
| lcs | O(n · m) | O(n · m) |
| lis_n2 | O(n^2) | O(n) |
| lis_nlogn | O(n log n) | O(n) |
| coin_change | O(amount · coins) | O(amount) |

## 特徴
- **部分問題の重複**: 同じ部分問題が何度も出るときに効く
- **最適部分構造**: 部分問題の最適解から全体の最適解が作れる
- **空間削減**: 直前の行しか使わない場合は1次元に圧縮できる（ナップサック）

## 使いどころ
- 最大値・最小値・場合の数を求める問題
- 文字列の比較（LCS、編集距離）
- 部分和・分割問題

## 注意点
- まず「状態（dp[i] は何か）」を日本語で書いてから遷移を考える
- 初期値（`dp[0]`）と答えの位置（`dp[n]` か最大値か）を間違えやすい
- 値が大きくなる場合は `long long` を使う（fib(50) は int に収まらない）
