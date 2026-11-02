# Sliding Window - スライディングウィンドウ（尺取り法）

## 概要
スライディングウィンドウは、配列や文字列の「連続する区間（部分配列・部分文字列）」を窓として扱い、右端を広げたり左端を縮めたりしながら区間の情報を差分更新していくテクニックです。全区間 O(n²) を調べる代わりに O(n) で済みます。窓の大きさが固定のものと可変のものがあります。

## 目的
- 連続区間に関する最大・最小・個数の問題を O(n) で解けるようになる
- 「右を1つ足す・左を1つ引く」差分更新の考え方を身につける
- **使うサインとなるキーワード**:
  - 「連続する部分配列」「部分文字列（substring）」
  - 「長さ k の」（→ 固定長）
  - 「最長の」「最短の」「条件を満たす」（→ 可変長）
  - 「重複なし」「〜以上になる最小の長さ」「高々 k 種類」

## 達成条件
- [ ] 何も見ずに main.cpp を15分以内に手書きできる
- [ ] 固定長と可変長のテンプレートを書き分けられる
- [ ] 「最長」は while で条件を回復してから更新、「最短」は while の中で更新する違いを説明できる
- [ ] 各要素が窓に入る・出るのは1回ずつなので O(n) になると説明できる
- [ ] LeetCode 643. Maximum Average Subarray I を解ける
- [ ] LeetCode 3. Longest Substring Without Repeating Characters を解ける
- [ ] LeetCode 209. Minimum Size Subarray Sum を解ける
- [ ] LeetCode 424. Longest Repeating Character Replacement を解ける
- [ ] LeetCode 76. Minimum Window Substring を解ける

## スライディングウィンドウの動き
固定長 k=3：`{2, 1, 5, 1, 3, 2}`

```
[2  1  5] 1  3  2   sum=8
 2 [1  5  1] 3  2   sum=8 - 2 + 1 = 7
 2  1 [5  1  3] 2   sum=7 - 1 + 3 = 9  ← 最大
 2  1  5 [1  3  2]  sum=9 - 5 + 2 = 6
```

可変長：`"abcabcbb"` の重複なし最長部分文字列

```
R=0 [a]bcabcbb        長さ1
R=1 [ab]cabcbb        長さ2
R=2 [abc]abcbb        長さ3
R=3 [abca]bcbb        'a' が重複 → L を進める
     a[bca]bcbb       長さ3
R=4  a[bcab]cbb       'b' が重複 → L を進める
     ab[cab]cbb       長さ3
...                   最大は 3
```

## コードの解説

### 固定長の最大和（main.cpp:6-18）
```cpp
int sum = 0;
for (int i = 0; i < k; ++i)
    sum += a[i];               // 最初の窓
int best = sum;
for (int i = k; i < static_cast<int>(a.size()); ++i)
{
    sum += a[i] - a[i - k];    // 右に1つ入れて、左から1つ出す
    best = std::max(best, sum);
}
return best;
```
- 毎回 k 個足し直さず、差分だけ更新する

### 重複なし最長部分文字列（main.cpp:20-37）
```cpp
std::vector<int> count(256, 0);   // 窓内の各文字の出現数
int left = 0;
int best = 0;
for (int right = 0; right < static_cast<int>(s.size()); ++right)
{
    unsigned char c = s[right];
    ++count[c];                   // 右端を広げる
    while (count[c] > 1)          // 条件違反の間、左端を縮める
    {
        --count[static_cast<unsigned char>(s[left])];
        ++left;
    }
    best = std::max(best, right - left + 1);  // 条件を満たした状態で更新
}
```
- 「最長」系：違反したら縮めて、正常に戻ってから答えを更新
- `char` は負になり得るので `unsigned char` で添字にする

### 和が target 以上の最短区間（main.cpp:39-56）
```cpp
int best = n + 1;                 // 「見つからない」を表す番兵
for (int right = 0; right < n; ++right)
{
    sum += a[right];
    while (sum >= target)         // 条件を満たしている間
    {
        best = std::min(best, right - left + 1);  // 縮める前に更新
        sum -= a[left];
        ++left;
    }
}
return best == n + 1 ? 0 : best;
```
- 「最短」系：条件を満たしている間に答えを更新しつつ縮める
- 要素がすべて正なので「縮めると和が減る」単調性が成り立つ

## 計算量
- **時間計算量**: O(n)（left と right はそれぞれ最大 n 回しか進まない）
- **空間計算量**: O(1)、または窓内の情報を持つ分 O(文字種)

## 特徴
- **差分更新**: 窓の出入りだけを処理する
- **単調性が前提**: 「広げると悪化／縮めると改善」の方向が一定であること

## 使いどころ
- 連続部分配列の最大和・最小長・個数
- 部分文字列の条件（重複なし、k 種類以下、アナグラム検出）
- 固定長の移動平均・最大値（最大値は単調 deque と組み合わせる）

## 注意点
- **負の数があると可変長は使えない**: 和の単調性が崩れる。LeetCode 560 などは累積和 + hash map を使う
- **長さの計算**: 閉区間 `[left, right]` なら `right - left + 1`
- **見つからない場合**: 最短系は初期値を `n + 1` などにし、最後に 0 へ変換
- **固定長で k > n**: 最初の窓が作れないので事前にチェック
