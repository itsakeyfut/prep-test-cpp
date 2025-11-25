# Vector 基本操作 解説

## 1. 初期化

```cpp
vector<int> v1;              // 空のvector
vector<int> v2(10);          // サイズ10、デフォルト値0
vector<int> v3(10, -1);      // サイズ10、初期値-1
vector<int> v4 = {1,2,3,4,5}; // 初期化リスト

// 2D配列
vector<vector<int>> grid(n, vector<int>(m));      // n×m、初期値0
vector<vector<int>> grid2(n, vector<int>(m, -1)); // n×m、初期値-1
```

| 初期化方法 | 計算量 | 用途 |
|-----------|--------|------|
| `vector<int> v` | O(1) | 動的に追加していく場合 |
| `vector<int> v(n)` | O(n) | サイズが決まっている場合 |
| `vector<int> v(n, x)` | O(n) | 特定の初期値が必要な場合（visited配列など） |

**注意点:**
- `vector<int> v(10)` は10個の0で初期化される（intのデフォルト値）
- 2D配列の初期化は `vector<vector<int>>(n, vector<int>(m))` の形を暗記

---

## 2. 基本操作

```cpp
nums.push_back(4);   // 末尾に追加
nums.pop_back();     // 末尾を削除
nums.size();         // サイズ取得
nums.empty();        // 空判定
nums.front();        // 先頭要素
nums.back();         // 末尾要素
nums[i];             // インデックスアクセス（範囲チェックなし）
nums.at(i);          // インデックスアクセス（範囲外で例外）
nums.clear();        // 全削除
nums.resize(n);      // サイズ変更
```

| 操作 | 計算量 | 備考 |
|------|--------|------|
| `push_back` | 償却 O(1) | 内部で再確保が発生することがある |
| `pop_back` | O(1) | 戻り値なし、要素を返さない |
| `size` | O(1) | |
| `empty` | O(1) | `size() == 0` より意図が明確 |
| `front/back` | O(1) | 空の時は未定義動作 |
| `[]` | O(1) | 範囲外アクセスは未定義動作 |
| `at` | O(1) | 範囲外で `out_of_range` 例外 |
| `clear` | O(n) | サイズは0になるがcapacityは変わらない |

**注意点:**
- `pop_back()` は値を返さない → 先に `back()` で取得してから削除
- 面接では通常 `[]` を使用（`at` は遅い）

---

## 3. イテレーション

```cpp
// 範囲for（値のコピー）
for (int x : arr) { cout << x; }

// 範囲for（参照、変更可能）
for (int& x : arr) { x *= 2; }

// インデックスfor
for (int i = 0; i < arr.size(); i++) { cout << arr[i]; }

// 逆順
for (int i = arr.size() - 1; i >= 0; i--) { cout << arr[i]; }
```

**使い分け:**
| パターン | 使用場面 |
|----------|----------|
| `for (int x : arr)` | 値を読むだけ、インデックス不要 |
| `for (int& x : arr)` | 要素を変更する |
| `for (int i = 0; ...)` | インデックスが必要（隣接要素比較など） |
| `for (int i = n-1; ...)` | 逆順処理が必要 |

**注意点:**
- 逆順ループで `i >= 0` の `i` は `int` 型にする（`size_t` だと無限ループ）
- `arr.size()` は `size_t`（unsigned）なので、空配列で `arr.size() - 1` はオーバーフロー

---

## 4. ソート

```cpp
// 昇順
sort(data.begin(), data.end());

// 降順
sort(data.begin(), data.end(), greater<int>());

// カスタム（ラムダ）
sort(data.begin(), data.end(), [](int a, int b) {
    return a > b;  // 降順
});

// pairのソート（first優先、次にsecond）
sort(pairs.begin(), pairs.end());
```

| ソート | 計算量 | 備考 |
|--------|--------|------|
| `sort` | O(n log n) | イントロソート（クイック+ヒープ+挿入） |
| `stable_sort` | O(n log n) | 同値の相対順序を保持 |

**ラムダの比較関数:**
- `return a < b;` → 昇順（aがbより前に来る）
- `return a > b;` → 降順（aがbより前に来る）
- 「trueを返すと左の引数が前に来る」と覚える

**カスタムソートの例:**
```cpp
// 絶対値でソート
sort(v.begin(), v.end(), [](int a, int b) {
    return abs(a) < abs(b);
});

// secondでソート
sort(pairs.begin(), pairs.end(), [](auto& a, auto& b) {
    return a.second < b.second;
});
```

---

## 5. 検索

```cpp
// 線形探索
auto it = find(arr.begin(), arr.end(), target);
if (it != arr.end()) {
    int index = it - arr.begin();
}

// 二分探索（ソート済み配列のみ）
bool found = binary_search(arr.begin(), arr.end(), target);

// lower_bound: target以上の最初の位置
auto lb = lower_bound(arr.begin(), arr.end(), target);

// upper_bound: targetより大きい最初の位置
auto ub = upper_bound(arr.begin(), arr.end(), target);
```

| 関数 | 計算量 | 戻り値 |
|------|--------|--------|
| `find` | O(n) | イテレータ（見つからない場合 `end()`） |
| `binary_search` | O(log n) | bool |
| `lower_bound` | O(log n) | イテレータ（target以上の最初） |
| `upper_bound` | O(log n) | イテレータ（targetより大きい最初） |

**lower_bound と upper_bound の違い:**
```
配列: [1, 2, 2, 2, 3, 4]
              ↑     ↑
              lb    ub  (target = 2)

lower_bound(2) → index 1（最初の2）
upper_bound(2) → index 4（3の位置）
```

**targetの個数を数える:**
```cpp
int count = upper_bound(..., target) - lower_bound(..., target);
```

---

## 6. その他の便利な操作

```cpp
reverse(v.begin(), v.end());           // 反転 O(n)
int max_val = *max_element(v.begin(), v.end());  // 最大値 O(n)
int min_val = *min_element(v.begin(), v.end());  // 最小値 O(n)

// 重複削除（ソート必須）
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
```

**重複削除の仕組み:**
1. `unique` は連続する重複を除去し、新しい終端イテレータを返す
2. `erase` で不要な末尾を削除

```
元:     [1, 2, 2, 3, 3, 3, 4]
unique: [1, 2, 3, 4, ?, ?, ?] → 新しい終端を返す
erase:  [1, 2, 3, 4]
```

---

## 7. Prefix Sum（累積和）

区間の和を O(1) で求めるテクニック。

```cpp
vector<int> nums = {1, 2, 3, 4, 5};
int n = nums.size();

// Prefix Sum配列を作成
vector<int> prefix(n + 1, 0);
for (int i = 0; i < n; i++) {
    prefix[i + 1] = prefix[i] + nums[i];
}
// prefix = [0, 1, 3, 6, 10, 15]

// 区間[l, r]の和
int sum = prefix[r + 1] - prefix[l];
```

**なぜ動くか:**
```
nums:   [1, 2, 3, 4, 5]
         0  1  2  3  4  (インデックス)

prefix: [0, 1, 3, 6, 10, 15]
         0  1  2  3  4   5

prefix[i] = nums[0] + nums[1] + ... + nums[i-1]

区間[1, 3]の和 = nums[1] + nums[2] + nums[3]
              = (nums[0]+nums[1]+nums[2]+nums[3]) - nums[0]
              = prefix[4] - prefix[1]
              = prefix[r+1] - prefix[l]
```

**計算量:**
- 前処理: O(n)
- クエリ: O(1)

---

## 8. 2D Prefix Sum

矩形領域の和を O(1) で求める。

```cpp
vector<vector<int>> prefix2d(rows + 1, vector<int>(cols + 1, 0));

// 構築
for (int i = 1; i <= rows; i++) {
    for (int j = 1; j <= cols; j++) {
        prefix2d[i][j] = matrix[i-1][j-1]
                       + prefix2d[i-1][j]
                       + prefix2d[i][j-1]
                       - prefix2d[i-1][j-1];
    }
}

// クエリ: (r1,c1) から (r2,c2) の和
int sum = prefix2d[r2+1][c2+1]
        - prefix2d[r1][c2+1]
        - prefix2d[r2+1][c1]
        + prefix2d[r1][c1];
```

**包除原理の図解:**
```
求めたい領域: X
+-------+-------+
|   A   |   B   |
+-------+-------+
|   C   |   X   |
+-------+-------+

X = 全体 - A - B - C + (AとBとCの重複補正)
  = prefix2d[r2+1][c2+1]
  - prefix2d[r1][c2+1]    (上側を除去)
  - prefix2d[r2+1][c1]    (左側を除去)
  + prefix2d[r1][c1]      (左上を2回引いたので足す)
```

---

## 9. 例外処理パターン

面接で忘れがちなエッジケース:

```cpp
// 空配列チェック
if (arr.empty()) return ...;

// サイズ1のチェック
if (arr.size() == 1) return arr[0];

// インデックス範囲チェック
if (index >= 0 && index < arr.size()) {
    // 安全にアクセス
}
```

**よくあるエッジケース:**
| ケース | 対処 |
|--------|------|
| 空配列 | 早期リターン |
| 要素1つ | 特別処理（ループが回らない等） |
| 全要素同じ | ソート結果が元と同じ |
| 負の数を含む | 最大値の初期値を `INT_MIN` に |
| オーバーフロー | `long long` を使用 |

---

## まとめ: 計算量一覧

| 操作 | 計算量 |
|------|--------|
| アクセス `v[i]` | O(1) |
| 末尾追加 `push_back` | 償却 O(1) |
| 末尾削除 `pop_back` | O(1) |
| 先頭/中間への挿入・削除 | O(n) |
| ソート | O(n log n) |
| 線形探索 | O(n) |
| 二分探索 | O(log n) |
| Prefix Sum構築 | O(n) |
| Prefix Sumクエリ | O(1) |
