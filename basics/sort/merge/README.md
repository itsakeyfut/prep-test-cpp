# Merge Sort - マージソート

## 概要
マージソートは**分割統治法**を用いた効率的なソートアルゴリズムです。配列を半分ずつ分割し、それぞれをソートしてから結合（マージ）します。

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
[3] [22] [19] [5]  ← 1要素まで分割

【結合フェーズ】
[3] [22] → [3, 22]    ← ソート済みの2つを結合
[19] [5] → [5, 19]    ← ソート済みの2つを結合
   ↓
[3, 22] [5, 19] → [3, 5, 19, 22]  ← 最終結合
```

## コードの解説

### 分割部分（main.cpp:27-36）
```cpp
void mergeSort(vector<int> &nums, int left, int right)
{
    if (right - left <= 1)    // 1要素以下なら終了
        return;

    int mid = left + (right - left) / 2;  // 中央位置
    mergeSort(nums, left, mid);           // 左半分を再帰的にソート
    mergeSort(nums, mid, right);          // 右半分を再帰的にソート
    merge(nums, left, mid, right);        // 2つをマージ
}
```

### 結合部分（main.cpp:6-25）
```cpp
void merge(vector<int> &nums, int left, int mid, int right)
{
    // 左半分と右半分を一時配列にコピー
    vector<int> leftPart(nums.begin() + left, nums.begin() + mid);
    vector<int> rightPart(nums.begin() + mid, nums.begin() + right);

    int i = 0, j = 0, k = left;

    // 2つのソート済み配列を結合
    while (i < leftPart.size() && j < rightPart.size())
    {
        if (leftPart[i] <= rightPart[j])
            nums[k++] = leftPart[i++];  // 小さい方を選択
        else
            nums[k++] = rightPart[j++];
    }

    // 残りをコピー
    while (i < leftPart.size()) nums[k++] = leftPart[i++];
    while (j < rightPart.size()) nums[k++] = rightPart[j++];
}
```

## 計算量
- **時間計算量**:
  - 最良: O(n log n)
  - 平均: O(n log n)
  - 最悪: O(n log n)
- **空間計算量**: O(n)（一時配列が必要）

## 特徴
- **安定ソート**: 同じ値の順序が保たれる
- **保証された性能**: どんなデータでもO(n log n)
- **分割統治**: 再帰的に問題を小さく分割
- **追加メモリ**: 一時配列が必要（クイックソートより多い）

## 使いどころ
- 大量のデータ
- 安定ソートが必要な場合
- リンクリストのソート（追加メモリ不要で実装可能）
- 外部ソート（ファイルなど、メモリに乗らないデータ）
- 予測可能な性能が必要な場合

## 他のソートとの比較
- **クイックソート vs マージソート**:
  - クイックソート: 平均的に速いが、最悪O(n²)、不安定
  - マージソート: 常にO(n log n)、安定、追加メモリが必要
