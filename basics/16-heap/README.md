# Heap - 二分ヒープ（最小ヒープ）

## 概要
二分ヒープは「親は必ず子以下」という性質（ヒープ条件）を持つ完全二分木です。木の形をしていますが、実際には配列で表現でき、添字の計算だけで親子をたどれます。最小値が常に根（`data[0]`）にあるので、最小値の取得が O(1)、追加・削除が O(log n) でできます。優先度付きキューの正体です。

## 目的
- LeetCode の「Top K」「K番目に大きい/小さい」「K個のソート済みリストをマージ」「ダイクストラ法」など、優先度付きキューを使う問題を解けるようにする
- `std::priority_queue` がデフォルトで **最大** ヒープであること、最小ヒープにするには `std::greater` が必要なことを理由とともに覚える
- heapify が O(n) で済む理由を説明できるようにする（面接で聞かれやすい）
- ヒープソートの理解

## 達成条件
- [ ] 何も見ずに main.cpp を15分以内に手書きできる
- [ ] 添字 i の親 `(i-1)/2`、左の子 `2i+1`、右の子 `2i+2` を即答できる
- [ ] sift_up と sift_down がそれぞれ何をしているか図で説明できる
- [ ] push / pop / top の計算量を説明できる
- [ ] heapify（後ろの親から順に sift_down）が O(n log n) ではなく O(n) になる理由を説明できる
- [ ] `std::priority_queue<int, std::vector<int>, std::greater<int>>` で最小ヒープを書ける
- [ ] LeetCode 215. Kth Largest Element in an Array を解ける
- [ ] LeetCode 347. Top K Frequent Elements を解ける
- [ ] LeetCode 703. Kth Largest Element in a Stream を解ける
- [ ] LeetCode 23. Merge k Sorted Lists を解ける
- [ ] LeetCode 295. Find Median from Data Stream を解ける

## ヒープの動き
```
配列と木の対応:
  index:  0  1  2  3  4  5
  data : [1, 3, 2, 5, 9, 8]

            1          (0)
          /   \
         3     2       (1)(2)
        / \   /
       5   9 8         (3)(4)(5)

push(0): 末尾に追加して sift_up（親より小さい間は親と交換）
  [1,3,2,5,9,8,0]  → 0 の親は index 2 の 2 → 交換
  [1,3,0,5,9,8,2]  → 0 の親は index 0 の 1 → 交換
  [0,3,1,5,9,8,2]  → 根に到達して終了

pop(): 根を末尾の要素で上書きして sift_down（小さいほうの子と交換）
  [0,3,1,5,9,8,2] → 根に 2 を移す → [2,3,1,5,9,8]
  2 の子は 3 と 1 → 小さい 1 と交換 → [1,3,2,5,9,8]
  2 の子は 8 のみ → 2 <= 8 なので終了

heapify([7,4,6,2,10,1,3]):  子を持つ最後のノード (n/2-1) から根に向かって sift_down
  i=2: 6 と子(1,3) → 1 と交換 → [7,4,1,2,10,6,3]
  i=1: 4 と子(2,10) → 2 と交換 → [7,2,1,4,10,6,3]
  i=0: 7 と子(2,1) → 1 と交換 → 7 と子(6,3) → 3 と交換 → [1,2,3,4,10,6,7]
```

## コードの解説

### メンバ変数（main.cpp:10）
```cpp
std::vector<T> data;  // 完全二分木を配列で表現
```
- 完全二分木は隙間なく左から詰まっているので、ポインタなしで配列に収まる

### sift_up（main.cpp:12-22）
```cpp
void sift_up(std::size_t i)
{
    while (i > 0)
    {
        std::size_t parent = (i - 1) / 2;
        if (data[parent] <= data[i])
            break;                       // 親のほうが小さければ OK
        std::swap(data[parent], data[i]); // そうでなければ親と交換
        i = parent;                      // 上へ進む
    }
}
```
- push の直後に使う。新しい要素を正しい高さまで「浮かせる」

### sift_down（main.cpp:24-43）
```cpp
void sift_down(std::size_t i)
{
    std::size_t n = data.size();
    while (true)
    {
        std::size_t smallest = i;
        std::size_t left = 2 * i + 1;
        std::size_t right = 2 * i + 2;

        if (left < n && data[left] < data[smallest])
            smallest = left;             // 左の子のほうが小さい
        if (right < n && data[right] < data[smallest])
            smallest = right;            // 右の子のほうが小さい
        if (smallest == i)
            break;                       // 自分が一番小さければ OK

        std::swap(data[i], data[smallest]); // 小さいほうの子と交換
        i = smallest;                    // 下へ進む
    }
}
```
- pop と heapify で使う。要素を正しい深さまで「沈める」
- 「3者（自分・左・右）の中で最小を探す」形にすると分岐が少なく書ける

### heapify コンストラクタ（main.cpp:48-52）
```cpp
explicit MinHeap(std::vector<T> values) : data(std::move(values))
{
    for (std::size_t i = data.size() / 2; i-- > 0;)
        sift_down(i);  // 子を持つノードを後ろから順に沈める
}
```
- 葉（後ろ半分）は最初からヒープ条件を満たすので、前半分だけ処理すればよい
- `i-- > 0` は size_t（符号なし）で 0 まで逆順ループするための定番の書き方
- 1つずつ push すると O(n log n) だが、この方法なら O(n)

### push（main.cpp:54-58）
```cpp
data.push_back(value);    // 末尾に追加
sift_up(data.size() - 1); // 正しい位置まで浮かせる
```

### pop（main.cpp:60-68）
```cpp
if (empty())
    throw std::underflow_error("Heap is empty");
data[0] = std::move(data.back()); // 末尾の要素を根に移動
data.pop_back();
if (!empty())
    sift_down(0);                 // 根から沈める
```
- 根を直接消すと木に穴が開くので、末尾の要素で埋めてから直す

### top（main.cpp:70-75）
- `data[0]` が常に最小値

## 計算量
- **時間計算量**:
  - top: O(1)
  - push: O(log n)
  - pop: O(log n)
  - heapify（構築）: O(n)
- **空間計算量**: O(n)

## 特徴
- **最小値（最大値）だけを高速に取り出せる**: 全体はソートされていない
- **配列で実装できる**: ポインタ不要でキャッシュ効率が良い
- **木の高さが常に log n**: 完全二分木なので BST のように偏らない

## 使いどころ
- 優先度付きキュー（タスクスケジューリング）
- ダイクストラ法・プリム法
- Top K 問題（サイズ K の最小ヒープで大きい K 個を保持）
- ストリームの中央値（最大ヒープ + 最小ヒープの2本立て）
- ヒープソート

## 注意点
- `std::priority_queue` はデフォルトで **最大** ヒープ。最小ヒープは `std::priority_queue<int, std::vector<int>, std::greater<int>>`
- 任意の要素の検索・削除は O(n)（ヒープが得意なのは根だけ）
- Top K（大きい順）は「サイズ K の **最小** ヒープ」を使うと O(n log K) になる

## 標準ライブラリ
C++では`std::priority_queue`、および`std::make_heap` / `std::push_heap` / `std::pop_heap`が提供されています。
