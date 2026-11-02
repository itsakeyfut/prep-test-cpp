# Recursion & Backtracking - 再帰とバックトラッキング

## 概要
バックトラッキングは、「選ぶ → 再帰で先へ進む → 選択を取り消す」を繰り返して、すべての候補を系統的に探索する手法です。順列・組み合わせ・部分集合・N-Queens など「全パターンを列挙する」問題の基本形になります。

## 目的
- 「全列挙」系の問題を、同じテンプレート（choose → recurse → un-choose）で解けるようにする
- 再帰の終了条件と、状態の巻き戻し（`pop_back` / `used[i] = false`）を体で覚える
- 枝刈り（`is_safe` のような条件で探索を打ち切る）の考え方を身につける
- DFS・グラフ探索・DP（メモ化再帰）の土台になる

## 達成条件
- [ ] 何も見ずに main.cpp を15分以内に手書きできる
- [ ] choose → recurse → un-choose の3ステップを、各関数のどの行が担当しているか説明できる
- [ ] 順列は `used` 配列、組み合わせ・部分集合は `start` インデックスで重複を防ぐ理由を説明できる
- [ ] 順列 O(n · n!)、部分集合 O(n · 2^n) になる理由を説明できる
- [ ] LeetCode 46. Permutations を解ける
- [ ] LeetCode 77. Combinations を解ける
- [ ] LeetCode 78. Subsets を解ける
- [ ] LeetCode 39. Combination Sum を解ける
- [ ] LeetCode 51. N-Queens / 52. N-Queens II を解ける
- [ ] LeetCode 79. Word Search を解ける

## バックトラッキングの動き
`{1, 2, 3}` の順列を作る再帰木：

```
                     []
          /          |          \
        [1]         [2]         [3]
       /   \       /   \       /   \
    [1,2] [1,3] [2,1] [2,3] [3,1] [3,2]
      |     |     |     |     |     |
  [1,2,3][1,3,2][2,1,3][2,3,1][3,1,2][3,2,1]   ← 葉で result に追加
```

部分集合は「すべてのノード」で結果に追加します（葉だけでなく途中も答え）：

```
              []
         /    |    \
       [1]   [2]   [3]
      /   \    |
   [1,2] [1,3] [2,3]
     |
  [1,2,3]
```

N-Queens（n=4）は1行ずつクイーンを置き、置けなければ戻ります：

```
.Q..    ← row 0: col 1 に置く
...Q    ← row 1: col 3 に置く
Q...    ← row 2: col 0 に置く
..Q.    ← row 3: col 2 に置く → row == n で解を記録
```

## コードの解説

### 順列（main.cpp:15-32）
```cpp
void permute(const std::vector<int> &nums, std::vector<bool> &used,
             std::vector<int> &path, std::vector<std::vector<int>> &result)
{
    if (path.size() == nums.size())
    {
        result.push_back(path);   // 全部使ったら1つ完成
        return;
    }
    for (std::size_t i = 0; i < nums.size(); ++i)
    {
        if (used[i])
            continue;              // 使用済みはスキップ
        used[i] = true;            // choose
        path.push_back(nums[i]);
        permute(nums, used, path, result);  // recurse
        path.pop_back();           // un-choose
        used[i] = false;
    }
}
```
- 毎回 0 から全要素を見るので、順番違いが別の答えになる
- `used` で同じ要素の二重使用を防ぐ

### 組み合わせ（main.cpp:34-47）
```cpp
void combine(int start, int n, int k, std::vector<int> &path,
             std::vector<std::vector<int>> &result)
{
    if (static_cast<int>(path.size()) == k)
    {
        result.push_back(path);   // k 個選んだら完成
        return;
    }
    for (int i = start; i <= n; ++i)
    {
        path.push_back(i);
        combine(i + 1, n, k, path, result);  // 次は i+1 から
        path.pop_back();
    }
}
```
- `start` より前は見ないので `[1,2]` と `[2,1]` が重複しない

### 部分集合（main.cpp:49-58）
```cpp
void subsets(const std::vector<int> &nums, std::size_t start,
             std::vector<int> &path, std::vector<std::vector<int>> &result)
{
    result.push_back(path);       // 途中経過がそのまま答え
    for (std::size_t i = start; i < nums.size(); ++i)
    {
        path.push_back(nums[i]);
        subsets(nums, i + 1, path, result);
        path.pop_back();
    }
}
```
- 組み合わせとほぼ同じ形。終了条件がなく、毎回 `result` に追加する点だけが違う

### 配置チェック（main.cpp:60-74）
```cpp
bool is_safe(const std::vector<std::string> &board, int row, int col)
{
    int n = static_cast<int>(board.size());
    for (int r = 0; r < row; ++r)
    {
        if (board[r][col] == 'Q')
            return false;                          // 同じ列
        int d = row - r;
        if (col - d >= 0 && board[r][col - d] == 'Q')
            return false;                          // 左上の斜め
        if (col + d < n && board[r][col + d] == 'Q')
            return false;                          // 右上の斜め
    }
    return true;
}
```
- 1行に1つしか置かないので、行の衝突はチェック不要
- 上の行だけ見れば十分（下はまだ置いていない）

### N-Queens（main.cpp:76-92）
```cpp
void solve_queens(int row, std::vector<std::string> &board,
                  std::vector<std::vector<std::string>> &solutions)
{
    int n = static_cast<int>(board.size());
    if (row == n)
    {
        solutions.push_back(board);  // 全行置けたら解
        return;
    }
    for (int col = 0; col < n; ++col)
    {
        if (!is_safe(board, row, col))
            continue;                // 枝刈り
        board[row][col] = 'Q';       // choose
        solve_queens(row + 1, board, solutions);
        board[row][col] = '.';       // un-choose
    }
}
```
- 置けない場所は再帰しない（枝刈り）ので全探索より大幅に速い

## 計算量
- **順列**: 時間 O(n · n!)、空間 O(n)（再帰の深さ、結果を除く）
- **組み合わせ**: 時間 O(k · C(n, k))、空間 O(k)
- **部分集合**: 時間 O(n · 2^n)、空間 O(n)
- **N-Queens**: 時間 O(n!) 程度（`is_safe` が O(n) なので厳密には O(n · n!)）、空間 O(n^2)（盤面）

## 特徴
- **テンプレート化できる**: ほぼすべてが choose → recurse → un-choose の形
- **状態を共有して巻き戻す**: `path` をコピーせず使い回すのでメモリ効率が良い
- **指数時間**: n が大きいと現実的に終わらない（n ≤ 10〜20 程度が目安）

## 使いどころ
- 全パターンの列挙（順列・組み合わせ・部分集合）
- 制約充足問題（N-Queens、数独）
- グリッド上の経路探索（Word Search）

## 注意点
- un-choose を忘れると状態が壊れる（`pop_back` と `used[i] = false` はセット）
- `result.push_back(path)` はコピーなので OK。参照を保存しないこと
- 重複要素を含む入力（LC 47, 90）はソートして `nums[i] == nums[i-1]` をスキップする工夫が必要
