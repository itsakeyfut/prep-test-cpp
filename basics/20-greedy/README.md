# Greedy - 貪欲法

## 概要
貪欲法は、各ステップで「その時点で最も良さそうな選択」を行い、後戻りせずに答えを組み立てるアルゴリズムの設計方針です。正しく適用できればシンプルかつ高速ですが、常に最適解が得られるとは限らないため、「なぜ貪欲で良いのか」を説明できることが重要です。

## 目的
- ソート + 1パスで解ける最適化問題を見抜けるようになる
- 「貪欲で良い問題」と「DP が必要な問題」を区別できるようになる
- 交換論法（最適解の一部を貪欲の選択に入れ替えても悪くならない）で正しさを考える習慣をつける
- **使うサインとなるキーワード**:
  - 「区間」「重ならないように最大個」「会議室」「矢で風船を割る」
  - 「到達できるか」「最小のジャンプ回数」
  - 「最小枚数」「最小コスト」で、ソートすると選び方が自明になりそう
  - 逆に「すべての組み合わせ」「最適な部分構造が複雑」なら DP を疑う

## 達成条件
- [ ] 何も見ずに main.cpp を15分以内に手書きできる
- [ ] 区間スケジューリングで「終了時刻」でソートする理由を説明できる（開始時刻や長さではダメな理由も）
- [ ] 硬貨 {1, 3, 4} で 6 を作るとき貪欲法が失敗する反例を説明できる
- [ ] 時間計算量（ソート込みで O(n log n)）を説明できる
- [ ] LeetCode 435. Non-overlapping Intervals を解ける
- [ ] LeetCode 452. Minimum Number of Arrows to Burst Balloons を解ける
- [ ] LeetCode 55. Jump Game を解ける
- [ ] LeetCode 45. Jump Game II を解ける
- [ ] LeetCode 322. Coin Change を DP で解ける（貪欲ではダメな例として）
- [ ] LeetCode 122. Best Time to Buy and Sell Stock II を解ける

## 貪欲法の動き
区間スケジューリング（終了時刻でソート済み）：

```
時刻:      0 1 2 3 4 5 6 7 8 9 10 11
(1,4)        [-----)                  ← 選ぶ  last_end=4
(3,5)            [---)                  3 < 4 で重なる
(0,6)      [-----------)                0 < 4 で重なる
(5,7)                [---)            ← 選ぶ  last_end=7
(3,9)            [-----------)          重なる
(5,9)                [-------)          重なる
(6,10)                 [-------)        重なる
(8,11)                     [-----)    ← 選ぶ  last_end=11

答え: 3
```

Jump Game `{2, 3, 1, 1, 4}`：

```
i=0 reach=max(0, 0+2)=2
i=1 reach=max(2, 1+3)=4   ← 最後の index 4 に届く
i=2 reach=4
i=3 reach=4
i=4 reach=8   i が reach を超えることはなかった → true

{3, 2, 1, 0, 4}: reach は 3 で止まり、i=4 > reach → false
```

硬貨の反例 `{1, 3, 4}` で 6 を作る：

```
貪欲: 4 を使う → 残り 2 → 1, 1  = 3枚 (4 + 1 + 1)
最適: 3, 3                       = 2枚
```

## コードの解説

### 区間スケジューリング（main.cpp:6-21）
```cpp
std::sort(intervals.begin(), intervals.end(), [](const auto &a, const auto &b)
          { return a.second < b.second; });  // 終了時刻の早い順
int count = 0;
int last_end = -1000000000;                  // 直前に選んだ区間の終了時刻
for (const auto &[start, end] : intervals)
{
    if (start >= last_end)                   // 重ならなければ選ぶ
    {
        ++count;
        last_end = end;
    }
}
```
- 早く終わる区間を選ぶほど、残りの時間が最も多く残る
- LeetCode 435（削除する最小数）は `n - count` で求まる

### Jump Game（main.cpp:23-33）
```cpp
int reach = 0;                          // 現時点で到達できる最も遠い index
for (int i = 0; i < static_cast<int>(nums.size()); ++i)
{
    if (i > reach)
        return false;                   // i にたどり着けない
    reach = std::max(reach, i + nums[i]);
}
return true;
```
- どこから跳ぶかを全部試さず、「最遠到達点」だけを持てば十分

### 貪欲な硬貨の両替（main.cpp:35-45）
```cpp
std::sort(coins.rbegin(), coins.rend());  // 大きい順
for (int c : coins)
{
    count += amount / c;                  // 使えるだけ使う
    amount %= c;
}
return amount == 0 ? count : -1;
```
- 日本の硬貨 {1, 5, 10, 50, 100, 500} のような「標準的な」硬貨系では最適

### DP による硬貨の両替（main.cpp:47-57）
```cpp
std::vector<int> dp(amount + 1, INF);  // dp[x] = x を作る最小枚数
dp[0] = 0;
for (int x = 1; x <= amount; ++x)
    for (int c : coins)
        if (c <= x && dp[x - c] != INF)
            dp[x] = std::min(dp[x], dp[x - c] + 1);
```
- 反例を確かめるための比較用。{1, 3, 4} で 6 → 貪欲 3枚、DP 2枚

## 計算量
- **時間計算量**:
  - 区間スケジューリング: O(n log n)（ソートが支配的）
  - Jump Game: O(n)
  - 貪欲な硬貨: O(m log m)（m は硬貨の種類）
  - DP 硬貨: O(amount × m)
- **空間計算量**: O(1)（ソートを除く）、DP は O(amount)

## 特徴
- **シンプル・高速**: 多くはソート + 1パス
- **正しさの証明が必要**: 直感で書くと反例に引っかかる

## 使いどころ
- 区間の選択・統合・分割
- 到達可能性、最小回数の問題
- ソートすると選ぶ順番が自明になる最適化問題

## 注意点
- **反例を探す**: 書く前に小さなケースで「貪欲が失敗しないか」を考える。不安なら DP
- **ソートの基準**: 区間スケジューリングは「終了時刻」。開始時刻や長さでソートすると誤答
- **境界の等号**: `start >= last_end` か `>` かは「端点が接しているのを重なりとみなすか」で変わる（問題文を確認）
- **初期値**: `last_end` は最小の開始時刻より小さい値にする
