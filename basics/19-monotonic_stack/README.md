# Monotonic Stack - 単調スタック

## 概要
単調スタックは、スタック内の要素が常に単調（増加または減少）になるように保つテクニックです。新しい要素を積む前に、単調性を壊す要素をすべて pop します。pop される瞬間に「その要素の次に来る、より大きい（小さい）要素」が確定するため、「次の大きい要素」系の問題を O(n) で解けます。両端から出し入れする単調 deque にすると、スライディングウィンドウの最大値も求められます。

## 目的
- 「各要素について、右（左）で最初に大きい／小さい要素」を O(n) で求められるようになる
- ヒストグラムの最大長方形のような、一見 O(n²) の問題を O(n) で解けるようになる
- **使うサインとなるキーワード**:
  - 「次に大きい（Next Greater）」「次に暖かくなる日」
  - 「左右で自分より小さい最初の位置」「各要素が最小値となる範囲」
  - 「ヒストグラム」「最大長方形」「雨水」
  - 「長さ k の窓の最大値／最小値」（→ 単調 deque）

## 達成条件
- [ ] 何も見ずに main.cpp を15分以内に手書きできる
- [ ] スタックに「値」ではなく「インデックス」を積む理由を説明できる
- [ ] 各要素は push/pop が1回ずつなので O(n) になると説明できる
- [ ] Largest Rectangle で末尾に高さ 0 の番兵を置く理由を説明できる
- [ ] LeetCode 496. Next Greater Element I を解ける
- [ ] LeetCode 739. Daily Temperatures を解ける
- [ ] LeetCode 84. Largest Rectangle in Histogram を解ける
- [ ] LeetCode 239. Sliding Window Maximum を解ける
- [ ] LeetCode 42. Trapping Rain Water を解ける

## 単調スタックの動き
`next_greater({2, 1, 2, 4, 3})`（スタックは下から上へ減少）：

```
i=0 a=2  stack: []          → push 0         stack: [2]
i=1 a=1  stack: [2]         1 < 2 なので push stack: [2, 1]
i=2 a=2  stack: [2, 1]      1 < 2 → pop、result[1]=2
                stack: [2]  2 < 2 ではない → push stack: [2, 2]
i=3 a=4  stack: [2, 2]      2 < 4 → pop、result[2]=4
                            2 < 4 → pop、result[0]=4
                                    push     stack: [4]
i=4 a=3  stack: [4]         4 < 3 ではない → push stack: [4, 3]
終了: 残った要素は -1

result = [4, 2, 4, -1, -1]
（stack の表示は見やすさのため値で書いているが、実際はインデックスを積む）
```

単調 deque（k=3、`{1, 3, -1, -3, 5, ...}`）：

```
i=0 1   dq: [1]
i=1 3   1 <= 3 なので後ろから捨てる → dq: [3]
i=2 -1  dq: [3, -1]         → 最大 3
i=3 -3  dq: [3, -1, -3]     → 最大 3
i=4 5   先頭の 3 は窓外 → 捨てる。後ろの -3, -1 も 5 以下 → 捨てる
        dq: [5]             → 最大 5
```

## コードの解説

### Next Greater Element（main.cpp:8-23）
```cpp
std::vector<int> result(n, -1);    // 見つからなければ -1
std::stack<int> st;                // インデックスを積む
for (int i = 0; i < n; ++i)
{
    while (!st.empty() && a[st.top()] < a[i])  // 自分より小さいものは
    {
        result[st.top()] = a[i];   // 「次の大きい要素」が自分に確定
        st.pop();
    }
    st.push(i);
}
```
- スタックは常に（下から上へ）非増加になっている

### Daily Temperatures（main.cpp:25-40）
```cpp
while (!st.empty() && t[st.top()] < t[i])
{
    result[st.top()] = i - st.top();  // 値ではなく「何日後か」を記録
    st.pop();
}
st.push(i);
```
- Next Greater と同じ形。インデックスを積んでいるから距離が計算できる

### Largest Rectangle in Histogram（main.cpp:42-60）
```cpp
for (int i = 0; i <= n; ++i)                   // n まで回す
{
    int h = (i == n) ? 0 : heights[i];         // 末尾に高さ 0 の番兵
    while (!st.empty() && heights[st.top()] >= h)
    {
        int height = heights[st.top()];        // この棒を高さとする長方形
        st.pop();
        int left = st.empty() ? -1 : st.top(); // 左で自分より低い最初の位置
        best = std::max(best, height * (i - left - 1));  // 右の壁は i
    }
    st.push(i);
}
```
- スタックは増加順。pop される棒にとって、`i` が右側で最初に低い棒、新しい top が左側で最初に低い棒
- 番兵 0 によって、最後に残った棒もすべて pop されて計算される

### Sliding Window Maximum（main.cpp:62-77）
```cpp
std::deque<int> dq;                            // インデックス、値は前から減少
for (int i = 0; i < static_cast<int>(a.size()); ++i)
{
    if (!dq.empty() && dq.front() <= i - k)    // 窓から外れた先頭を捨てる
        dq.pop_front();
    while (!dq.empty() && a[dq.back()] <= a[i])  // 自分以下は今後最大になれない
        dq.pop_back();
    dq.push_back(i);
    if (i >= k - 1)                            // 窓が完成してから記録
        result.push_back(a[dq.front()]);       // 先頭が窓内の最大
}
```

### 表示用ヘルパー（main.cpp:79-85）
- ベクタをラベル付きで出力するだけ

## 計算量
- **時間計算量**: O(n)（各要素は push と pop が高々1回ずつ）
- **空間計算量**: O(n)（スタック／deque）

## 特徴
- **pop の瞬間に答えが確定**する、という発想が核心
- 増加スタックか減少スタックかは「何を探すか」で決まる
  - 次に**大きい**要素 → 減少スタック（`<` で pop）
  - 次に**小さい**要素 → 増加スタック（`>` で pop）

## 使いどころ
- Next Greater / Smaller Element 系
- 各要素が最小（最大）である区間の幅を求める問題（ヒストグラム、部分配列の最小値の和）
- 固定長窓の最大・最小（単調 deque）

## 注意点
- **インデックスを積む**: 値だと距離や位置が分からない
- **等号の扱い**: `<` か `<=` かで重複値の扱いが変わる。Largest Rectangle は `>=` でも `>` でも正しいが、混乱しやすい
- **残った要素の処理**: ループ後スタックに残った要素は「見つからない」。初期値（-1 や 0）で埋めておく
- **deque の窓外判定**: `dq.front() <= i - k` で外れたものを捨てる（off-by-one 注意）
