# Merge Sort - マージソート

## 概要
マージソートは**分割統治法**を用いた効率的なソートアルゴリズムです。配列を半分ずつ分割し、それぞれをソートしてから結合（マージ）します。どんな入力でも O(n log n) が保証され、**安定**なので、`std::stable_sort` の中身にも使われています。

## 目的
- 分割統治法（分割 → 再帰で解く → 結合）の基本形を身につける（面接で最頻出）
- 「2つのソート済み配列をマージする」処理を正確に書けるようにする（単体でも頻出）
- 半開区間 `[left, right)` で再帰を書く方法を身につける
- 漸化式 T(n) = 2T(n/2) + O(n) から O(n log n) を導けるようにする
- 解ける問題の例: 88 Merge Sorted Array、21 Merge Two Sorted Lists、148 Sort List、912 Sort an Array、315 Count of Smaller Numbers After Self / 493 Reverse Pairs（マージ中に数える）

## 達成条件
- [ ] 何も見ずに main.cpp を10分以内に手書きできる
- [ ] 分割の深さが log n、各段のマージの合計が O(n) なので O(n log n) になる理由を説明できる
- [ ] `leftPart[i] <= rightPart[j]` の `<=` を `<` にすると**不安定**になる理由を説明できる
- [ ] 半開区間 `[left, right)` で `right - left <= 1` が終了条件になる理由を説明できる
- [ ] `mid = left + (right - left) / 2` と書く理由（オーバーフロー対策）を説明できる
- [ ] LeetCode 88. Merge Sorted Array を解ける
- [ ] LeetCode 21. Merge Two Sorted Lists を解ける
- [ ] LeetCode 148. Sort List を連結リストのマージソートで解ける
- [ ] LeetCode 912. Sort an Array をマージソートで解ける

## アルゴリズムの動き
1. **分割**: 配列を半分に分割し続ける（1要素になるまで）
2. **統治**: 分割した配列をソートしながら結合

```
[3, 22, 19, 5] の場合

【分割フェーズ】
[3, 22, 19, 5]
   ↓ 半分に分割
[3, 22]  [19, 5]
   ↓        ↓
[3] [22] [19] [5]  ← 1要素まで分割（1要素は必ずソート済み）

【結合フェーズ】
[3] [22] → [3, 22]    ← ソート済みの2つを結合
[19] [5] → [5, 19]    ← ソート済みの2つを結合
   ↓
[3, 22] [5, 19] → [3, 5, 19, 22]  ← 最終結合
```

### マージの中身
```
left:  [3, 22]    right: [5, 19]

3 <= 5   → 3 を出力   [3]
22 > 5   → 5 を出力   [3, 5]
22 > 19  → 19 を出力  [3, 5, 19]
right が尽きたので残りの left をコピー → [3, 5, 19, 22]
```

## コードの解説

### 結合部分（main.cpp:6-25）
```cpp
void merge(vector<int> &nums, int left, int mid, int right)
{
    // 左半分 [left, mid) と右半分 [mid, right) を一時配列にコピー
    vector<int> leftPart(nums.begin() + left, nums.begin() + mid);
    vector<int> rightPart(nums.begin() + mid, nums.begin() + right);

    int i = 0, j = 0, k = left;

    // 2つのソート済み配列を結合
    while (i < leftPart.size() && j < rightPart.size())
    {
        if (leftPart[i] <= rightPart[j])
            nums[k++] = leftPart[i++];  // 小さい方を選択（同じなら左を優先 → 安定）
        else
            nums[k++] = rightPart[j++];
    }

    // 残りをコピー（どちらか片方しか残らない）
    while (i < leftPart.size()) nums[k++] = leftPart[i++];
    while (j < rightPart.size()) nums[k++] = rightPart[j++];
}
```

### 分割部分（main.cpp:27-36）
```cpp
void mergeSort(vector<int> &nums, int left, int right)
{
    if (right - left <= 1)    // 1要素以下なら終了
        return;

    int mid = left + (right - left) / 2;  // 中央位置
    mergeSort(nums, left, mid);           // 左半分 [left, mid) を再帰的にソート
    mergeSort(nums, mid, right);          // 右半分 [mid, right) を再帰的にソート
    merge(nums, left, mid, right);        // 2つをマージ
}
```

### 呼び出し用のラッパー（main.cpp:38-41）
```cpp
void mergeSort(vector<int> &nums)
{
    mergeSort(nums, 0, nums.size());  // 全体 [0, n) をソート
}
```

## 計算量
- **時間計算量**:
  - 最良: O(n log n)
  - 平均: O(n log n)
  - 最悪: O(n log n)
  - T(n) = 2T(n/2) + O(n) → 深さ log n × 各段 O(n)
- **空間計算量**: O(n)（一時配列）+ O(log n)（再帰スタック）

## 特徴
- **安定ソート**: 同じ値の順序が保たれる
- **保証された性能**: どんなデータでもO(n log n)
- **分割統治**: 再帰的に問題を小さく分割
- **追加メモリ**: 一時配列が必要（クイックソートより多い）
- **シーケンシャルアクセス**: 前から順に読むだけなので、連結リストや外部ファイルと相性が良い

## 使いどころ
- 大量のデータ
- 安定ソートが必要な場合
- 連結リストのソート（つなぎ替えだけで済み、追加の配列が不要）
- 外部ソート（ファイルなど、メモリに乗らないデータ）
- 予測可能な性能が必要な場合
- 転倒数を数える問題（マージ中に「右から取った回数」を数える）

## 他のソートとの比較
- **クイックソート vs マージソート**:
  - クイックソート: 平均的に速いが、最悪O(n²)、不安定、省メモリ
  - マージソート: 常にO(n log n)、安定、追加メモリが必要

## 注意点
- `i < leftPart.size()` は `int` と `size_t` の比較なので警告が出る。`size_t` に揃えるとよい
- merge のたびに vector を確保するのは遅い。一時バッファを1回だけ確保して使い回すと速くなる
- 閉区間 `[left, right]` で書く流派もある。どちらかに統一し、終了条件と mid の扱いを混ぜない
- 小さい区間（16要素程度以下）は挿入ソートに切り替えると実用上速くなる

## 標準ライブラリ
C++では`std::stable_sort`（マージソートベース）、2つのソート済み範囲の結合は`std::merge`、同じ配列内の結合は`std::inplace_merge`が提供されています。
