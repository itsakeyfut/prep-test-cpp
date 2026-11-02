# Dynamic Array - 動的配列

## 概要
動的配列は、要素数に応じて自動的に大きくなる配列です（`std::vector` の中身）。内部では固定長の配列を確保しておき、満杯になったら「2倍の大きさの配列を確保して全部コピーする」ことでサイズを伸ばします。コピーはたまにしか起きないので、push_back は平均すると O(1) になります。

## 目的
- LeetCode で最も多用する `std::vector` がどう動いているかを理解する
- 「償却計算量（amortized）」という考え方を身につける（面接で頻出）
- `reserve` で再確保を避ける、イテレータ無効化に気をつける、といった実践的な判断ができるようになる
- スタック・ヒープ・ハッシュマップのバケットなど、配列ベースのデータ構造の土台

## 達成条件
- [ ] 何も見ずに main.cpp を10分以内に手書きできる
- [ ] 容量を2倍にすると push_back が償却 O(1) になる理由を説明できる（1 + 2 + 4 + ... + n < 2n）
- [ ] 容量を「+1」や「+10」で増やすと O(n^2) になってしまう理由を説明できる
- [ ] size と capacity の違いを説明できる
- [ ] 再確保時にポインタ・参照・イテレータが無効化される理由を説明できる
- [ ] 各操作の計算量を説明できる
- [ ] LeetCode 1. Two Sum を vector で解ける
- [ ] LeetCode 26. Remove Duplicates from Sorted Array を解ける
- [ ] LeetCode 283. Move Zeroes を解ける
- [ ] LeetCode 1480. Running Sum of 1d Array を解ける

## 動的配列の動き
```
push_back(10): size=1 cap=1  [10]
push_back(20): size=2 cap=2  [10][20]                 ← 満杯なので 1→2 に拡張
push_back(30): size=3 cap=4  [10][20][30][  ]         ← 2→4 に拡張
push_back(40): size=4 cap=4  [10][20][30][40]
push_back(50): size=5 cap=8  [10][20][30][40][50][  ][  ][  ]  ← 4→8 に拡張

拡張の手順:
  1. 2倍の新しい配列を確保
  2. 古い配列から要素を移す
  3. 古い配列を解放して差し替え

pop_back(): size を1減らすだけ（capacity はそのまま）
```

## コードの解説

### メンバ変数（main.cpp:9-12）
```cpp
std::unique_ptr<T[]> data;  // 実データ
std::size_t length;         // 使っている要素数（size）
std::size_t cap;            // 確保済みの要素数（capacity）
```
- `length <= cap` が常に成り立つ

### reserve（再確保）（main.cpp:14-21）
```cpp
void reserve(std::size_t new_cap)
{
    auto new_data = std::make_unique<T[]>(new_cap);  // 新しい配列
    for (std::size_t i = 0; i < length; ++i)
        new_data[i] = std::move(data[i]);            // 要素を移動
    data = std::move(new_data);                      // 古い配列は自動解放
    cap = new_cap;
}
```
- `std::move` でコピーではなくムーブ（string などで効率的）

### push_back（main.cpp:26-31）
```cpp
void push_back(const T &value)
{
    if (length == cap)
        reserve(cap == 0 ? 1 : cap * 2);  // 満杯なら2倍に
    data[length++] = value;
}
```
- 容量0のときは 0 * 2 = 0 になってしまうので1にする

### pop_back（main.cpp:33-38）
```cpp
if (empty())
    throw std::underflow_error("Array is empty");
--length;  // size を減らすだけ
```
- 容量は縮めない（std::vector も同じ。縮めたいときは shrink_to_fit）

### operator[] と at（main.cpp:40-55）
```cpp
T &operator[](std::size_t index)
{
    return data[index];  // 範囲チェックなし（高速）
}

T &at(std::size_t index)
{
    if (index >= length)
        throw std::out_of_range("Index out of range");  // 範囲チェックあり
    return data[index];
}
```
- const 版の `operator[]` も用意して、const オブジェクトからも読めるようにする
- std::vector と同じく `[]` はチェックなし、`at` はチェックあり

### size / capacity / empty（main.cpp:57-70）
- それぞれ `length`、`cap`、`length == 0` を返すだけ

## 計算量
- **時間計算量**:
  - push_back: 償却 O(1)（再確保が起きる瞬間だけ O(n)）
  - pop_back: O(1)
  - operator[] / at: O(1)
  - 途中への挿入・削除（この実装にはない）: O(n)
- **空間計算量**: O(n)（最大で要素数の約2倍）

## 特徴
- **ランダムアクセス O(1)**: メモリが連続しているのでアドレス計算だけで済む
- **キャッシュ効率が良い**: 連続メモリなので実測でも速い
- **末尾操作が速い**: 先頭・途中の操作は要素のずらしが必要で遅い

## 使いどころ
- ほぼすべての場面のデフォルトのコンテナ
- スタック（末尾を top とみなす）
- ヒープやハッシュマップのバケットなど、配列ベースのデータ構造の内部

## 注意点
- 再確保が起きると、それまでの要素への参照・ポインタ・イテレータはすべて無効になる
- 要素数が事前にわかっているなら `reserve` しておくと再確保が起きない
- 成長率は実装によって 1.5 倍（MSVC）や 2 倍（GCC/Clang）

## 標準ライブラリ
C++では`std::vector`が標準で提供されています。
