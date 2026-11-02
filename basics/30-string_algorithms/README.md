# String Algorithms - 文字列探索アルゴリズム (KMP / Rabin-Karp)

## 概要
テキストの中からパターンが出現する位置をすべて求める「文字列探索」のアルゴリズムです。素朴な方法は O(n · m) かかりますが、KMP は失敗時の情報を再利用して O(n + m)、Rabin-Karp はハッシュで比較を高速化して平均 O(n + m) で探索します。

## 目的
- `std::string::find` の中で何が起きているか、より速い方法があることを理解する
- KMP の prefix function（接頭辞と接尾辞の一致長）は、周期・繰り返し判定など探索以外にも使える
- Rabin-Karp のローリングハッシュは、部分文字列の比較を O(1) にする汎用テクニック

## 達成条件
- [ ] 何も見ずに main.cpp を15分以内に手書きできる
- [ ] `"ababaca"` の prefix function を手で計算できる（0 0 1 2 3 0 1）
- [ ] KMP で不一致時に `k = pi[k - 1]` へ戻る理由を説明できる
- [ ] KMP が O(n + m) になる理由（`k` の増減の総量）を説明できる
- [ ] Rabin-Karp でハッシュ一致後に実際の文字列比較が必要な理由を説明できる
- [ ] ローリングハッシュの「先頭を引いて、BASE 倍して、末尾を足す」を式で書ける
- [ ] LeetCode 28. Find the Index of the First Occurrence in a String を解ける
- [ ] LeetCode 459. Repeated Substring Pattern を解ける
- [ ] LeetCode 214. Shortest Palindrome を解ける
- [ ] LeetCode 1392. Longest Happy Prefix を解ける

## 文字列探索の動き
prefix function `pi[i]` = `p[0..i]` の「真の接頭辞」と「接尾辞」が一致する最大長：

```
i      :  0  1  2  3  4  5  6
p[i]   :  a  b  a  b  a  c  a
pi[i]  :  0  0  1  2  3  0  1

例: i=4 "ababa" → 接頭辞 "aba" == 接尾辞 "aba" → 3
```

KMP で不一致が起きたときの動き（パターン `abab`）：

```
text   : a b a b a b c ...
pattern: a b a b            ← 0 で一致。k=4 → k = pi[3] = 2 に戻す
pattern:     a b a b        ← "ab" は一致済みとして続きから比較
```

Rabin-Karp のローリングハッシュ（窓を1文字ずつずらす）：

```
text: [a b a b] a b c ...   hash = a·B^3 + b·B^2 + a·B + b
text:  a [b a b a] b c ...  hash = (前の hash - a·B^3) · B + a
```

## コードの解説

### prefix function（main.cpp:5-18）
```cpp
std::vector<int> prefix_function(const std::string &p)
{
    std::vector<int> pi(p.size(), 0);
    for (std::size_t i = 1; i < p.size(); ++i)
    {
        int k = pi[i - 1];             // 直前の一致長から始める
        while (k > 0 && p[i] != p[k])
            k = pi[k - 1];             // 一致しなければ短い候補へ戻る
        if (p[i] == p[k])
            ++k;                       // 一致したら1伸ばす
        pi[i] = k;
    }
    return pi;
}
```
- `pi[0]` は常に 0（自分自身は「真の」接頭辞ではない）

### KMP 探索（main.cpp:20-40）
```cpp
std::vector<int> kmp_search(const std::string &text, const std::string &p)
{
    std::vector<int> pi = prefix_function(p);
    int k = 0;                              // 今パターンの何文字目まで一致しているか
    for (std::size_t i = 0; i < text.size(); ++i)
    {
        while (k > 0 && text[i] != p[k])
            k = pi[k - 1];                  // テキスト側は戻らない
        if (text[i] == p[k])
            ++k;
        if (k == static_cast<int>(p.size()))
        {
            result.push_back(static_cast<int>(i) - k + 1);  // 開始位置
            k = pi[k - 1];                  // 重なった出現も探す
        }
    }
    return result;
}
```
- prefix function とほぼ同じ形。「パターン同士」か「テキストとパターン」かの違いだけ

### Rabin-Karp（main.cpp:42-75）
```cpp
const long long BASE = 256;
const long long MOD = 1000000007;
long long high = 1;                         // BASE^(m-1) % MOD
for (std::size_t i = 1; i < m; ++i)
    high = high * BASE % MOD;

// パターンと最初の窓のハッシュを計算
for (std::size_t i = 0; i < m; ++i)
{
    hp = (hp * BASE + p[i]) % MOD;
    ht = (ht * BASE + text[i]) % MOD;
}

for (std::size_t i = 0; i + m <= n; ++i)
{
    if (hp == ht && text.compare(i, m, p) == 0)  // ハッシュ一致 → 実際に比較
        result.push_back(static_cast<int>(i));
    if (i + m < n)
    {
        ht = (ht - text[i] * high % MOD + MOD) % MOD;  // 先頭を除く
        ht = (ht * BASE + text[i + m]) % MOD;          // 末尾を追加
    }
}
```
- ハッシュが一致しても別の文字列の可能性（衝突）があるので `compare` で確認
- 引き算で負になるのを防ぐため `+ MOD` してから `% MOD`
- `char` は負になり得るので `unsigned char` にキャストしている

## 計算量
- **KMP**:
  - 時間: O(n + m)（前処理 O(m) + 探索 O(n)）
  - 空間: O(m)（`pi` 配列）
- **Rabin-Karp**:
  - 時間: 平均 O(n + m)、最悪 O(n · m)（ハッシュ衝突が多発した場合）
  - 空間: O(1)（結果を除く）

## 特徴
- **KMP**: 最悪でも線形。テキストのポインタが後戻りしない
- **Rabin-Karp**: 実装がシンプルで、複数パターン検索や2次元への拡張がしやすい

## 使いどころ
- 長いテキストからのパターン検索
- 文字列の周期・繰り返し構造の判定（prefix function）
- 重複する部分文字列の検出（ローリングハッシュ + 二分探索、LC 1044）

## 注意点
- KMP の `pi` は「長さ」なので、`p[k]` は「次に比較する文字」を指す
- Rabin-Karp の MOD 演算でオーバーフローしないよう `long long` を使う
- ハッシュ一致だけで答えにすると、衝突時に誤答になる
