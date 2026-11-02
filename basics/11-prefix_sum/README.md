# Prefix Sum - 累積和

## 概要
累積和は、配列の先頭から i 番目までの和を前計算しておくことで、任意の区間の和を O(1) で求められるようにするテクニックです。2次元への拡張、hash map との組み合わせ、逆操作である差分配列（いもす法）まで含めて、区間に関する問題の基本道具になります。

## 目的
- 区間和クエリを O(1) で答えられるようになる
- 「区間和 = prefix[r] - prefix[l]」という変換で、部分配列の問題を「2点の差」の問題に置き換えられるようになる
- いもす法で、区間への一括加算を O(1) で記録できるようになる
- **使うサインとなるキーワード**:
  - 「区間の和を何度も」「クエリが多い」
  - 「和が k になる部分配列の個数」（負の数あり → hash map）
  - 「長方形領域の和」（→ 2次元累積和）
  - 「区間に一括で加算」「重なりの最大数」「時刻ごとの人数」（→ いもす法）

## 達成条件
- [ ] 何も見ずに main.cpp を15分以内に手書きできる
- [ ] `prefix` のサイズを n+1 にして `prefix[0] = 0` とする理由を説明できる
- [ ] 2次元累積和の包除原理（足して、2つ引いて、1つ足す）を図で説明できる
- [ ] Subarray Sum Equals K で `seen[0] = 1` が必要な理由を説明できる
- [ ] 前計算 O(n)、クエリ O(1) と説明できる
- [ ] LeetCode 303. Range Sum Query - Immutable を解ける
- [ ] LeetCode 304. Range Sum Query 2D - Immutable を解ける
- [ ] LeetCode 560. Subarray Sum Equals K を解ける
- [ ] LeetCode 238. Product of Array Except Self を解ける（累積積）
- [ ] LeetCode 1094. Car Pooling を解ける（いもす法）

## 累積和の動き
```
index:     0  1  2  3  4  5
a:         3  1  4  1  5  9
prefix: 0  3  4  8  9 14 23
        ↑ prefix[0]=0

区間 [1, 4) の和 = a[1]+a[2]+a[3] = prefix[4] - prefix[1] = 9 - 3 = 6
```

2次元累積和（`s[i][j]` = 左上 i×j の矩形の和）：

```
     c1      c2
  +---+-------+
  | D |   B   |      求めたい領域 A の和
r1+---+-------+        = s[r2][c2] - s[r1][c2] - s[r2][c1] + s[r1][c1]
  | C |   A   |        = (全体) - (上: D+B) - (左: D+C) + (二重に引いた D)
r2+---+-------+
```

いもす法：長さ6の配列に [0,3)+1, [2,5)+2, [1,2)+3

```
index:          0  1  2  3  4  5  6
[0,3) +1       +1          -1           ← 始点に +v、終点に -v
[2,5) +2             +2          -2
[1,2) +3          +3 -3
-------------------------------------
diff:           1  3 -1 -1  0 -2  0
累積和:         1  4  3  2  2  0        ← これが結果
```

## コードの解説

### 1次元累積和の構築（main.cpp:5-11）
```cpp
std::vector<int> prefix(a.size() + 1, 0);  // 先頭に 0 を置く
for (std::size_t i = 0; i < a.size(); ++i)
    prefix[i + 1] = prefix[i] + a[i];      // prefix[i] = a[0..i) の和
return prefix;
```
- n+1 にすると「空区間の和 = 0」が自然に扱え、境界の if が不要になる

### 区間和（main.cpp:13-16）
```cpp
return prefix[r] - prefix[l];  // 半開区間 [l, r) の和
```

### 2次元累積和の構築（main.cpp:18-27）
```cpp
std::vector<std::vector<int>> s(h + 1, std::vector<int>(w + 1, 0));
for (std::size_t i = 0; i < h; ++i)
    for (std::size_t j = 0; j < w; ++j)
        s[i + 1][j + 1] = s[i][j + 1] + s[i + 1][j] - s[i][j] + g[i][j];
        //                上             左             重複分    自分
```

### 矩形和（main.cpp:29-32）
```cpp
return s[r2][c2] - s[r1][c2] - s[r2][c1] + s[r1][c1];  // 行 [r1,r2) × 列 [c1,c2)
```

### 和が k の部分配列の個数（main.cpp:34-49）
```cpp
std::unordered_map<int, int> seen;  // これまでの累積和 → 出現回数
seen[0] = 1;                        // 「先頭から」の区間のための空の累積和
int sum = 0;
int count = 0;
for (int x : a)
{
    sum += x;
    auto it = seen.find(sum - k);   // prefix[r] - prefix[l] = k ⇔ prefix[l] = sum - k
    if (it != seen.end())
        count += it->second;
    ++seen[sum];                    // 検索の「後」に登録（長さ0の区間を数えない）
}
```
- 負の数があっても使える（スライディングウィンドウは使えない）

### いもす法（main.cpp:51-67）
```cpp
std::vector<int> diff(n + 1, 0);    // 終点 n に書き込めるよう n+1
for (const auto &u : updates)       // u = {l, r, v}: [l, r) に v を足す
{
    diff[u[0]] += u[2];             // 始点で +v
    diff[u[1]] -= u[2];             // 終点で -v
}
int cur = 0;
for (int i = 0; i < n; ++i)
{
    cur += diff[i];                 // 累積和を取ると実際の値になる
    result[i] = cur;
}
```
- 更新は各 O(1)、最後に1回だけ O(n) で復元

## 計算量
- **時間計算量**:
  - 1次元: 前計算 O(n)、クエリ O(1)
  - 2次元: 前計算 O(HW)、クエリ O(1)
  - Subarray Sum Equals K: O(n)（平均）
  - いもす法: 更新 O(1) × q、復元 O(n)
- **空間計算量**: O(n)（2次元は O(HW)）

## 特徴
- **静的な配列向け**: 値の更新があると作り直しが必要（更新ありなら Fenwick Tree / Segment Tree）
- **逆演算が必要**: 和・XOR は OK、max/min は引き算できないので不可

## 使いどころ
- 区間和クエリが大量にある問題
- 部分配列の和・個数・平均に関する問題
- 区間への一括加算、イベントの重なり数（いもす法）

## 注意点
- **添字のずれ**: `prefix[i]` は `a[0..i)` の和。区間 `[l, r]`（閉区間）なら `prefix[r + 1] - prefix[l]`
- **オーバーフロー**: 和が大きくなるなら `long long` を使う
- **`seen[0] = 1` を忘れない**: 先頭から始まる区間を数え漏らす
- **登録の順番**: 検索してから `++seen[sum]`。逆にすると k=0 で誤カウント
