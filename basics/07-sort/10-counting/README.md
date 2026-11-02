# Counting Sort - 計数ソート

## 概要
計数ソートは、要素同士を比較せずに「各値が何回出てきたか」を数えてソートする**非比較ソート**です。値の範囲 k が小さければ O(n + k) で動き、比較ソートの下限 O(n log n) を超えられます。このコードは**累積カウント**を使った**安定版**で、0 以上の整数を対象にしています。

## 目的
- 「値の範囲が小さい」という条件を見たら O(n) で解ける、という発想を身につける
- 累積カウントで「各値の出力位置」を求めるテクニックを理解する（Radix Sort の部品になる）
- 解ける問題の例: 912 Sort an Array（値域 -5×10⁴〜5×10⁴ をオフセットして使う）、75 Sort Colors、1051 Height Checker、1122 Relative Sort Array、274 H-Index

## 達成条件
- [ ] 何も見ずに main.cpp を5分以内に手書きできる
- [ ] 累積カウントの後、`count[v]` が「v 以下の要素数」＝「v を置く末尾+1の位置」になる理由を説明できる
- [ ] 後ろから走査すると**安定**になる理由を説明できる
- [ ] O(n + k) の時間・空間計算量を説明でき、k が大きいと使えない理由を言える
- [ ] 負の数を扱う場合のオフセット（`v - minVal`）を書ける
- [ ] LeetCode 912 Sort an Array を計数ソートで解ける
- [ ] LeetCode 1051 Height Checker を解ける

## 計数ソートの動き
```
入力: [2, 5, 3, 0, 2, 3, 0, 3]

【1. 数える】
値:     0  1  2  3  4  5
count: [2, 0, 2, 3, 0, 1]

【2. 累積する】 count[v] = v 以下の要素数
count: [2, 2, 4, 7, 7, 8]

【3. 後ろから配置】 output[--count[v]] = v
i=7: 3 → count[3]=7→6, output[6]=3
i=6: 0 → count[0]=2→1, output[1]=0
i=5: 3 → count[3]=6→5, output[5]=3
i=4: 2 → count[2]=4→3, output[3]=2
i=3: 0 → count[0]=1→0, output[0]=0
i=2: 3 → count[3]=5→4, output[4]=3
i=1: 5 → count[5]=8→7, output[7]=5
i=0: 2 → count[2]=3→2, output[2]=2

結果: [0, 0, 2, 2, 3, 3, 3, 5]
```
同じ値は「後ろにあったものほど後ろに置かれる」ので、元の順序が保たれます（安定）。

## コードの解説

### 計数ソート（main.cpp:7-28）
```cpp
void countingSort(vector<int> &nums)
{
    if (nums.empty())
        return;

    int maxVal = *max_element(nums.begin(), nums.end());
    vector<int> count(maxVal + 1, 0);       // 値 0〜maxVal の出現回数

    for (int n : nums)
        ++count[n];                         // 1. 数える

    for (int i = 1; i <= maxVal; ++i)
        count[i] += count[i - 1];           // 2. 累積（v 以下の個数）

    vector<int> output(nums.size());
    for (int i = static_cast<int>(nums.size()) - 1; i >= 0; --i)
    {
        output[--count[nums[i]]] = nums[i]; // 3. 後ろから配置（安定）
    }

    nums = output;
}
```
- `--count[v]` で先に減らしてから使うので、0-indexed の位置になる
- ループ変数を `int` にしているのは、`size_t` だと `i >= 0` が常に真になるため

## 計算量
- **時間計算量**: O(n + k)（k = 値の範囲 = maxVal + 1）
- **空間計算量**: O(n + k)（count 配列と output 配列）

## 特徴
- **非比較ソート**: O(n log n) の壁を超えられる
- **安定ソート**: 累積カウント＋後ろからの配置で順序を保つ
- **値域依存**: k が n より極端に大きいとメモリ・時間ともに無駄が大きい

## 使いどころ
- 値の範囲が小さい整数（年齢、点数、文字 'a'〜'z' など）
- Radix Sort の各桁のソート
- 「出現回数を数える」系の問題全般

## 注意点
- 負の数は `minVal` を引いてオフセットする
- 値の範囲が 10⁹ のように大きい場合は使えない（座標圧縮か比較ソートを使う）
- 安定性が不要なら、count を前から展開するだけの簡易版でもよい
