# Two Pointers - 二つのポインタ（尺取りの基礎）

## 概要
Two Pointers は、配列や文字列の上に2つのインデックスを置き、条件に応じてどちらかを動かしていくテクニックです。二重ループ O(n²) で全ペアを調べる代わりに、O(n) で済ませられます。主に「両端から内側へ」と「同じ方向に速い／遅い」の2パターンがあります。

## 目的
- 全ペア探索 O(n²) を O(n) に落とす発想を身につける
- 配列の in-place 操作（重複削除・要素削除・並べ替え）を追加メモリなしで書けるようになる
- Sliding Window や 3Sum など、より複雑なパターンの土台になる
- **使うサインとなるキーワード**:
  - 「ソート済み配列」で「2つの和が target」
  - 「in-place で」「追加メモリ O(1) で」「重複を削除」
  - 「回文」「反転」
  - 「両端」「最大の面積／水量」

## 達成条件
- [ ] 何も見ずに main.cpp を15分以内に手書きできる
- [ ] 「両端から」と「同方向（fast/slow）」の2パターンを使い分けられる
- [ ] Container With Most Water で「低い方を動かす」理由を説明できる
- [ ] 時間計算量 O(n)、空間計算量 O(1) と説明できる
- [ ] LeetCode 167. Two Sum II - Input Array Is Sorted を解ける
- [ ] LeetCode 26. Remove Duplicates from Sorted Array を解ける
- [ ] LeetCode 125. Valid Palindrome を解ける
- [ ] LeetCode 11. Container With Most Water を解ける
- [ ] LeetCode 15. 3Sum を解ける（ソート + 1つ固定 + Two Pointers）

## Two Pointersの動き
両端から：`{1, 2, 4, 7, 11, 15}` で和が 15 になるペア

```
 L                 R
[1, 2, 4, 7, 11, 15]  1+15=16 > 15 → R を左へ
 L             R
[1, 2, 4, 7, 11, 15]  1+11=12 < 15 → L を右へ
    L          R
[1, 2, 4, 7, 11, 15]  2+11=13 < 15 → L を右へ
       L       R
[1, 2, 4, 7, 11, 15]  4+11=15 → 見つかった [2, 4]
```

同方向（slow / fast）：`{1, 1, 2, 3, 3}` の重複削除

```
 S  F
[1, 1, 2, 3, 3]  a[F]==a[S] → F だけ進む
 S     F
[1, 1, 2, 3, 3]  違う → S を進めて a[S]=a[F]
    S     F
[1, 2, 2, 3, 3]  違う → S を進めて a[S]=a[F]
       S     F
[1, 2, 3, 3, 3]  同じ → F だけ進む → 終了
長さ = S + 1 = 3 → [1, 2, 3]
```

## コードの解説

### ソート済み配列の Two Sum（main.cpp:7-22）
```cpp
int left = 0;
int right = static_cast<int>(a.size()) - 1;
while (left < right)
{
    int sum = a[left] + a[right];
    if (sum == target)
        return {left, right};
    if (sum < target)
        ++left;    // 和を大きくしたい → 小さい側を捨てる
    else
        --right;   // 和を小さくしたい → 大きい側を捨てる
}
return {-1, -1};
```
- ソート済みなので「どちらを動かせば和が増える／減るか」が確定する

### 重複削除（main.cpp:24-38）
```cpp
int slow = 0;                        // 書き込み済みの最後の位置
for (int fast = 1; fast < static_cast<int>(a.size()); ++fast)
{
    if (a[fast] != a[slow])          // 新しい値が来たら
    {
        ++slow;
        a[slow] = a[fast];           // slow の次に詰める
    }
}
return slow + 1;                     // ユニークな要素数
```
- `fast` が読み取り、`slow` が書き込み位置
- 空配列の場合は先に 0 を返す

### 回文判定（main.cpp:40-52）
```cpp
while (left < right)
{
    if (s[left] != s[right])
        return false;
    ++left;    // 両方とも内側へ
    --right;
}
return true;
```
- 文字列の反転（`std::swap(s[left], s[right])`）も同じ形

### Container With Most Water（main.cpp:54-69）
```cpp
while (left < right)
{
    int h = std::min(height[left], height[right]);  // 水位は低い方で決まる
    best = std::max(best, h * (right - left));
    if (height[left] < height[right])
        ++left;    // 低い方を動かす
    else
        --right;
}
```
- 高い方を動かしても、幅が減るうえ水位は低い方以下のままなので改善しない
- だから低い方を動かすしかない、という貪欲的な判断

## 計算量
- **時間計算量**: O(n)（各ポインタは高々 n 回しか動かない）
- **空間計算量**: O(1)

## 特徴
- **追加メモリ不要**: in-place 操作と相性が良い
- **単調性が鍵**: 「片方を動かすと値が一方向に変化する」性質が必要

## 使いどころ
- ソート済み配列でのペア探索（2Sum, 3Sum, 4Sum）
- 配列の in-place 圧縮・削除・並べ替え
- 回文判定・文字列反転
- 連結リストのサイクル検出（fast/slow、Floyd のアルゴリズム）

## 注意点
- **ソートされているか確認**: Two Sum II はソート済みが前提。未ソートなら hash map を使う
- **ループ条件**: `left < right`（同じ要素を2回使わない）
- **空配列**: `a.size() - 1` は `size_t` だとアンダーフローするので `int` にキャストしてから引く
- **3Sum の重複**: 同じ値をスキップしないと同じ組が複数回出る
