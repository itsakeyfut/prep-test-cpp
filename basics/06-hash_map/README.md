# Hash Map - ハッシュマップ（チェイン法）

## 概要
ハッシュマップは、キーをハッシュ関数で数値に変換し、その値を配列の添字として使うことで、キーから値を平均 O(1) で引けるデータ構造です。異なるキーが同じ添字（バケット）に入る「衝突」は避けられないので、この実装では各バケットをリストにして衝突したものを並べて持つ「チェイン法（separate chaining）」を使います。

## 目的
- LeetCode で最も出番の多いテクニック「ハッシュマップで O(n^2) を O(n) に落とす」の中身を理解する
- 平均 O(1) / 最悪 O(n) の理由、負荷率（load factor）と rehash の関係を説明できるようにする
- 頻度カウント、Two Sum 型の補数検索、グルーピング、重複検出などのパターンの基礎

## 達成条件
- [ ] 何も見ずに main.cpp を15分以内に手書きできる
- [ ] ハッシュ → バケット番号 → リスト内を線形探索、の流れを説明できる
- [ ] 負荷率（要素数 / バケット数）が大きくなると遅くなる理由と、rehash で解決する仕組みを説明できる
- [ ] rehash 時にすべての要素のバケット番号を計算し直す必要がある理由を説明できる
- [ ] 平均 O(1)、最悪 O(n) になる理由を説明できる
- [ ] チェイン法とオープンアドレス法の違いを説明できる
- [ ] LeetCode 1. Two Sum を解ける
- [ ] LeetCode 49. Group Anagrams を解ける
- [ ] LeetCode 242. Valid Anagram を解ける
- [ ] LeetCode 128. Longest Consecutive Sequence を解ける
- [ ] LeetCode 706. Design HashMap を自作の実装で解ける

## ハッシュマップの動き
```
バケット数 4 で開始（hash の値は例）

insert("apple",100)   hash % 4 = 1
insert("banana",200)  hash % 4 = 3
insert("cherry",300)  hash % 4 = 1  ← 衝突！同じバケットのリストに追加

  [0] -> (空)
  [1] -> (apple,100) -> (cherry,300)
  [2] -> (空)
  [3] -> (banana,200)

insert("durian",400)  要素数 4 / バケット 4 = 1.0 > 0.75 → rehash

rehash: バケットを 8 に増やし、全要素を hash % 8 で入れ直す
  [0] -> ...
  [1] -> (apple,100)
  ...
  [5] -> (cherry,300)      ← % 8 になったので場所が変わる
  ...

find("cherry"): hash % 8 のバケットだけをたどる
erase("banana"): バケット内のリストから取り除く
```

## コードの解説

### メンバ変数（main.cpp:11-13）
```cpp
std::vector<std::list<std::pair<K, V>>> buckets;  // バケットの配列。各バケットは (key, value) のリスト
std::size_t count;                                // 要素数
```

### index_of（バケット番号の計算）（main.cpp:15-18）
```cpp
std::size_t index_of(const K &key) const
{
    return std::hash<K>{}(key) % buckets.size();  // ハッシュ値をバケット数で割った余り
}
```
- `std::hash<K>{}` は一時オブジェクトを作ってすぐ呼び出している

### rehash（main.cpp:20-29）
```cpp
std::vector<std::list<std::pair<K, V>>> old = std::move(buckets);  // 古いバケットを退避
buckets = std::vector<std::list<std::pair<K, V>>>(old.size() * 2); // 2倍のバケットを用意
for (auto &bucket : old)
{
    for (auto &kv : bucket)
        buckets[index_of(kv.first)].push_back(std::move(kv));     // 新しいサイズで入れ直す
}
```
- バケット数が変わると `% buckets.size()` の結果が変わるので、全要素の入れ直しが必要

### コンストラクタ（main.cpp:32-33）
- 初期バケット数を受け取る（デフォルト 8）

### insert（main.cpp:35-51）
```cpp
auto &bucket = buckets[index_of(key)];
for (auto &kv : bucket)
{
    if (kv.first == key)
    {
        kv.second = value;  // 既存キーなら上書き
        return;
    }
}

bucket.emplace_back(key, value);  // 新規キーなら末尾に追加
++count;
if (static_cast<double>(count) / buckets.size() > 0.75)
    rehash();                     // 負荷率が 0.75 を超えたら拡張
```
- 同じキーが2つ入らないよう、先にバケット内を探す
- `static_cast<double>` を忘れると整数除算になって負荷率が常に 0 になる

### find（main.cpp:53-61）
```cpp
for (auto &kv : buckets[index_of(key)])
{
    if (kv.first == key)
        return &kv.second;  // 値へのポインタを返す
}
return nullptr;             // 見つからなければ nullptr
```
- 見つからない場合を表現するためにポインタを返す（`std::optional` でもよい）

### erase（main.cpp:63-76）
```cpp
auto &bucket = buckets[index_of(key)];
for (auto it = bucket.begin(); it != bucket.end(); ++it)
{
    if (it->first == key)
    {
        bucket.erase(it);  // リストから削除
        --count;
        return true;
    }
}
return false;
```
- 削除にはイテレータが必要なので range-for ではなくイテレータで回す

## 計算量
- **時間計算量**:
  - insert / find / erase: 平均 O(1)、最悪 O(n)（全キーが同じバケットに衝突した場合）
  - rehash: O(n)（ただし頻度が低いので insert は償却 O(1)）
- **空間計算量**: O(n + バケット数)

## 特徴
- **平均 O(1)**: キーから直接バケットを特定できる
- **順序なし**: キーの大小順には並ばない（順序が必要なら `std::map`）
- **ハッシュ関数の質が性能を決める**: 偏ると衝突が増えて遅くなる

## 使いどころ
- 出現回数のカウント（頻度表）
- 「すでに見たか」の判定（重複検出）
- Two Sum のような「補数を探す」問題
- キャッシュ（LRU Cache の索引部分）
- グルーピング（Group Anagrams）

## 注意点
- 自作の型をキーにするなら `std::hash` の特殊化（またはハッシュ関数オブジェクト）と `operator==` が必要
- `std::pair` は標準ではハッシュできないので、LeetCode では文字列化するか自前でハッシュを書く
- 競技プログラミングではハッシュ衝突を狙ったテストケースで最悪 O(n) になることがある

## 標準ライブラリ
C++では`std::unordered_map`（チェイン法で実装されている）が標準で提供されています。
