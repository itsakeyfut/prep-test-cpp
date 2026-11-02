# Binary Search - 二分探索

## 概要
二分探索は、ソート済みの配列（または「ある境界を境に条件が false → true に切り替わる」単調な性質）に対して、探索範囲を毎回半分に絞り込むことで O(log n) で目的の位置を見つけるアルゴリズムです。

## 目的
- ソート済み配列から値や「境界の位置」を高速に求められるようになる
- `lower_bound` / `upper_bound` を自作できれば、個数カウント・挿入位置・範囲検索がすべて書ける
- 「答えで二分探索」を身につけると、最適化問題（最小の最大値・最大の最小値）を判定問題に変換して解ける
- **使うサインとなるキーワード**:
  - 「ソート済み配列」「O(log n) で」
  - 「〜以上の最小値」「〜以下の最大値」「挿入位置」
  - 「最小の容量／速度／日数」「最大値を最小化」（→ 答えで二分探索）
  - 制約が大きい（値が 10^9 など）のに判定は簡単にできる

## 達成条件
- [ ] 何も見ずに main.cpp を15分以内に手書きできる
- [ ] 閉区間 `[lo, hi]` と半開区間 `[lo, hi)` のループ条件・更新式の違いを説明できる
- [ ] `lo + (hi - lo) / 2` を使う理由（オーバーフロー対策）を説明できる
- [ ] `lower_bound` と `upper_bound` の違いと、その差で個数が求まる理由を説明できる
- [ ] 時間計算量 O(log n)、答えで二分探索なら O(n log(範囲)) と説明できる
- [ ] LeetCode 704. Binary Search を解ける
- [ ] LeetCode 35. Search Insert Position を解ける
- [ ] LeetCode 34. Find First and Last Position of Element in Sorted Array を解ける
- [ ] LeetCode 1011. Capacity To Ship Packages Within D Days を解ける
- [ ] LeetCode 875. Koko Eating Bananas を解ける
- [ ] LeetCode 69. Sqrt(x) を解ける

## 二分探索の動き
`a = {1, 3, 3, 3, 5, 7, 9}` で `lower_bound(3)`（3 以上の最初の位置）を求める：

```
index:  0  1  2  3  4  5  6  (7)
value:  1  3  3  3  5  7  9

[lo, hi) = [0, 7)  mid=3  a[3]=3 >= 3 → hi=3
[lo, hi) = [0, 3)  mid=1  a[1]=3 >= 3 → hi=1
[lo, hi) = [0, 1)  mid=0  a[0]=1 <  3 → lo=1
[lo, hi) = [1, 1)  lo == hi で終了 → 答え 1

upper_bound(3)（3 より大きい最初の位置）は同様に 4
個数 = 4 - 1 = 3
```

答えで二分探索（容量 `cap` で D 日以内に運べるか）：

```
容量:   10 11 12 13 14 15 16 17 ...
判定:    F  F  F  F  F  T  T  T ...
                         ↑ ここ（最初の T）を lower_bound と同じ形で探す
```

## コードの解説

### 古典的な二分探索（main.cpp:5-20）
```cpp
int binary_search(const std::vector<int> &a, int target)
{
    int lo = 0;
    int hi = static_cast<int>(a.size()) - 1;  // 閉区間 [lo, hi]
    while (lo <= hi)                          // 要素が1つでも残っていれば続ける
    {
        int mid = lo + (hi - lo) / 2;         // (lo + hi) / 2 はオーバーフローの恐れ
        if (a[mid] == target)
            return mid;
        if (a[mid] < target)
            lo = mid + 1;                     // mid は違うので除外
        else
            hi = mid - 1;
    }
    return -1;                                // 見つからない
}
```
- 閉区間なので `lo <= hi`、更新は `mid ± 1`

### lower_bound（main.cpp:22-35）
```cpp
int lower_bound(const std::vector<int> &a, int target)
{
    int lo = 0;
    int hi = static_cast<int>(a.size());  // 半開区間 [lo, hi)、答えが size() の可能性もある
    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] < target)
            lo = mid + 1;                 // mid は答えではない
        else
            hi = mid;                     // mid は答えの候補なので残す
    }
    return lo;                            // target 以上の最初の位置
}
```
- 半開区間なので `lo < hi`、`hi = mid`（`- 1` しない）
- 全要素が target 未満なら `a.size()` を返す

### upper_bound（main.cpp:37-50）
```cpp
if (a[mid] <= target)   // lower_bound との違いは < が <= になるだけ
    lo = mid + 1;
else
    hi = mid;
```
- target より大きい最初の位置を返す
- `upper_bound - lower_bound` = target の個数

### 答えで二分探索：判定関数（main.cpp:52-66）
```cpp
bool can_ship(const std::vector<int> &weights, int days, int capacity)
{
    int used = 1;              // 使った日数
    int load = 0;              // 今日の積載量
    for (int w : weights)
    {
        if (load + w > capacity)  // 今日に載らなければ翌日へ
        {
            ++used;
            load = 0;
        }
        load += w;
    }
    return used <= days;
}
```
- 容量が大きいほど true になりやすい（単調性）のが二分探索できる条件

### 答えで二分探索：本体（main.cpp:68-86）
```cpp
int lo = 0;
int hi = 0;
for (int w : weights)
{
    lo = std::max(lo, w);  // 最低でも最大の荷物は載る必要がある
    hi += w;               // 全部を1日で運べる容量なら必ず OK
}
while (lo < hi)
{
    int mid = lo + (hi - lo) / 2;
    if (can_ship(weights, days, mid))
        hi = mid;          // OK なら、もっと小さくできるか試す
    else
        lo = mid + 1;      // NG なら増やす
}
return lo;
```
- 構造は `lower_bound` とまったく同じ。「条件を満たす最小値」を探している

## 計算量
- **時間計算量**:
  - binary_search / lower_bound / upper_bound: O(log n)
  - 答えで二分探索: O(n log S)（S は探索範囲の幅、判定が O(n)）
- **空間計算量**: O(1)

## 特徴
- **高速**: 10^9 の範囲でも約30回で収束
- **前提が必要**: ソート済み、または判定結果が単調であること

## 使いどころ
- ソート済み配列での検索・挿入位置・個数カウント
- 「最小の最大値」「最大の最小値」を求める最適化問題
- 単調な関数の境界（整数平方根など）

## 注意点
- **区間の流儀を混ぜない**: 閉区間なら `lo <= hi` / `hi = mid - 1`、半開区間なら `lo < hi` / `hi = mid`
- **無限ループ**: 半開区間で `lo = mid` と書くと `lo + 1 == hi` のとき進まなくなる
- **オーバーフロー**: `(lo + hi) / 2` ではなく `lo + (hi - lo) / 2`
- **答えの範囲**: 答えで二分探索では `lo` と `hi` が必ず答えを含むように初期化する（例: `lo` = 最大の荷物）
- **見つからない場合**: `lower_bound` は `size()` を返し得るので、アクセス前に範囲チェック
