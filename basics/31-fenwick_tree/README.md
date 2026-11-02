# Fenwick Tree - フェニック木 (Binary Indexed Tree)

## 概要
Fenwick Tree（BIT: Binary Indexed Tree）は、**1点加算**と**接頭辞和（prefix sum）**を O(log n) で処理するデータ構造です。`i & -i`（最下位ビット）を使って、どの区間を担当するかを決めるのが特徴で、コードが非常に短いです。このコードは **1-indexed** で実装しています。

## 目的
- 「値の更新」＋「区間和」の問題を、セグメント木より短いコードで解けるようになる
- 「自分より小さい要素がいくつあるか」を数える問題（転倒数）の定番ツールを身につける
- `i & -i` のビット操作に慣れる
- 解ける問題の例: 307 Range Sum Query - Mutable、315 Count of Smaller Numbers After Self、493 Reverse Pairs、1649 Create Sorted Array through Instructions

## 達成条件
- [ ] 何も見ずに main.cpp を5分以内に手書きできる
- [ ] `i & -i` が「最下位の1ビット」を取り出す理由（2の補数）を説明できる
- [ ] add は `i += i & -i`、prefix_sum は `i -= i & -i` で、向きが逆になる理由を説明できる
- [ ] なぜ 1-indexed なのか（i = 0 だと `0 & -0 = 0` で無限ループ）を説明できる
- [ ] 更新 O(log n)、クエリ O(log n) を説明できる
- [ ] LeetCode 307 Range Sum Query - Mutable を BIT で解ける
- [ ] LeetCode 315 Count of Smaller Numbers After Self を「座標圧縮 + BIT」で解ける
- [ ] Segment Tree との使い分けを説明できる

## Fenwick Treeの動き
`tree[i]` は「i で終わる、長さ `i & -i` の区間の和」を持ちます（n = 8 の例）：

```
i (2進数)    i & -i   担当区間
1  (0001)      1      [1, 1]
2  (0010)      2      [1, 2]
3  (0011)      1      [3, 3]
4  (0100)      4      [1, 4]
5  (0101)      1      [5, 5]
6  (0110)      2      [5, 6]
7  (0111)      1      [7, 7]
8  (1000)      8      [1, 8]

担当区間のイメージ:
tree[8] |===============================|
tree[4] |===============|
tree[2] |=======|               tree[6] |=======|
tree[1] |===|   tree[3] |===|   tree[5] |===|   tree[7] |===|
          1   2   3   4   5   6   7   8
```

`prefix_sum(7)` は下位ビットを消しながら下る：

```
i = 7 (0111) → tree[7]  を足す   [7, 7]
i = 6 (0110) → tree[6]  を足す   [5, 6]
i = 4 (0100) → tree[4]  を足す   [1, 4]
i = 0        → 終了              合計 = [1, 7]
```

`add(3, x)` は下位ビットを足しながら上る：

```
i = 3 (0011) → tree[3] += x
i = 4 (0100) → tree[4] += x
i = 8 (1000) → tree[8] += x
i = 16       → n を超えたので終了   （3 を含む区間すべてを更新）
```

## コードの解説

### メンバ変数とコンストラクタ（main.cpp:7, 10）
```cpp
std::vector<int> tree;                             // tree[0] は使わない
explicit FenwickTree(int n) : tree(n + 1, 0) {}   // 1-indexed なので n + 1
```

### 1点加算 add（main.cpp:12-16）
```cpp
void add(int i, int delta)
{
    for (; i < static_cast<int>(tree.size()); i += i & -i)  // 最下位ビットを足して上へ
        tree[i] += delta;
}
```
- i を含む区間を担当するノードを順に更新する
- 初期化は全要素について `add(i + 1, nums[i])` を呼ぶ（O(n log n)）

### 接頭辞和 prefix_sum（main.cpp:18-24）
```cpp
int prefix_sum(int i) const
{
    int sum = 0;
    for (; i > 0; i -= i & -i)   // 最下位ビットを消して下へ
        sum += tree[i];
    return sum;                  // [1, i] の和
}
```

### 区間和 range_sum（main.cpp:26-29）
```cpp
int range_sum(int left, int right) const
{
    return prefix_sum(right) - prefix_sum(left - 1);  // [left, right] の和
}
```
- 累積和と同じ考え方で、2つの prefix_sum の差を取る

## 計算量
- **時間計算量**:
  - add: O(log n)
  - prefix_sum / range_sum: O(log n)
  - 構築（n 回 add）: O(n log n)
- **空間計算量**: O(n)（配列サイズ n + 1）

## 特徴
- **コードが短い**: 中身はループ2本だけ
- **省メモリ**: n + 1 要素で済む
- **1-indexed**: 0 を使うと `i & -i = 0` で止まらなくなる

## Fenwick Tree vs Segment Tree
| 項目 | Fenwick Tree (BIT) | Segment Tree |
| ---- | ------------------ | ------------ |
| 区間和 + 1点更新 | ○ O(log n) | ○ O(log n) |
| 区間 min / max | △（基本は不可） | ○ |
| コード量 | とても短い | やや多い |
| メモリ | n + 1 | 2n（再帰版は 4n） |

- **和（や個数）だけなら BIT**、それ以外の演算が必要なら Segment Tree

## 使いどころ
- 値の更新がある区間和
- 転倒数・「自分より小さい要素の個数」（値を添字にして個数を add する）
- 座標圧縮と組み合わせたオンラインのカウント

## 注意点
- 外から 0-indexed で使う場合は `i + 1` を渡す
- 値を添字にする使い方では、値の範囲が大きければ座標圧縮が必要
