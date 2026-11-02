# Union-Find - 素集合データ構造 (Disjoint Set Union)

## 概要
Union-Find は、要素をいくつかのグループ（素集合）に分けて管理するデータ構造です。「2つのグループを合併する（unite）」と「2つの要素が同じグループか判定する（same）」をほぼ O(1) で行えます。各グループを木で表し、根（代表元）が同じなら同じグループです。

## 目的
- 「つながっているか」「グループはいくつか」を高速に答える方法を身につける
- グラフの連結成分・閉路検出・最小全域木（クラスカル法）の基礎にする
- 経路圧縮とランクによる合併という2つの最適化の効果を理解する

## 達成条件
- [ ] 何も見ずに main.cpp を10分以内に手書きできる
- [ ] 経路圧縮とランクによる合併が、それぞれ何を防いでいるか説明できる
- [ ] 計算量がほぼ O(1)（O(α(n))、α はアッカーマン関数の逆関数）であることを説明できる
- [ ] `unite` が false を返す（既に同じグループ）ことを閉路検出に使えると説明できる
- [ ] LeetCode 547. Number of Provinces を解ける
- [ ] LeetCode 684. Redundant Connection を解ける
- [ ] LeetCode 323. Number of Connected Components in an Undirected Graph を解ける
- [ ] LeetCode 721. Accounts Merge を解ける
- [ ] LeetCode 1584. Min Cost to Connect All Points（クラスカル法）を解ける

## Union-Findの動き
6 要素で `unite(0,1)`, `unite(1,2)`, `unite(3,4)` を行った場合：

```
初期状態: 全員が自分自身の親
  0   1   2   3   4   5

unite(0, 1):            unite(1, 2):            unite(3, 4):
  0   2   3   4   5       0     3   4   5         0     3     5
  |                      / \                     / \    |
  1                     1   2                   1   2   4

→ グループ {0,1,2}, {3,4}, {5}  components = 3
```

経路圧縮（`find` の途中のノードを根に直接つなぎ直す）：

```
  find(3) の前        find(3) の後
      0                   0
      |                 / | \
      1                1  2  3
      |
      2
      |
      3
```

## コードの解説

### メンバ変数と初期化（main.cpp:8-17）
```cpp
std::vector<int> parent;   // parent[x] = x の親（根なら自分自身）
std::vector<int> rank;     // 木の高さの上界
int components;            // グループ数

explicit UnionFind(int n) : parent(n), rank(n, 0), components(n)
{
    std::iota(parent.begin(), parent.end(), 0);  // parent = {0, 1, 2, ...}
}
```
- 最初は全員が別グループなので `components = n`

### find（main.cpp:19-24）
```cpp
int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);  // 根を見つけて直接つなぎ直す（経路圧縮）
    return parent[x];
}
```
- 一度たどった経路は次回から1ステップで根に届く

### unite（main.cpp:26-39）
```cpp
bool unite(int a, int b)
{
    int ra = find(a);
    int rb = find(b);
    if (ra == rb)
        return false;               // 既に同じグループ
    if (rank[ra] < rank[rb])
        std::swap(ra, rb);          // ra を高い方にする
    parent[rb] = ra;                // 低い木を高い木の下につなぐ
    if (rank[ra] == rank[rb])
        ++rank[ra];                 // 同じ高さなら1つ高くなる
    --components;
    return true;
}
```
- 低い木を高い木の下につなぐことで、木が一直線に伸びるのを防ぐ（ランクによる合併）

### same / count（main.cpp:41-49）
```cpp
bool same(int a, int b)
{
    return find(a) == find(b);      // 根が同じなら同じグループ
}

int count() const
{
    return components;
}
```

### LC 547. Number of Provinces（main.cpp:52-65）
```cpp
int find_circle_num(const std::vector<std::vector<int>> &is_connected)
{
    int n = static_cast<int>(is_connected.size());
    UnionFind uf(n);
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)     // 対称行列なので上三角だけ
            if (is_connected[i][j])
                uf.unite(i, j);
    return uf.count();                      // 残ったグループ数が答え
}
```

## 計算量
- **時間計算量**:
  - find / unite / same: 償却 O(α(n))（実用上 O(1)）
  - 最適化なしだと最悪 O(n)
- **空間計算量**: O(n)

## 特徴
- **合併は得意、分割は苦手**: 一度つないだグループを切り離すことはできない
- **2つの最適化**: 経路圧縮とランクによる合併を両方使うと非常に速い
- **実装が短い**: 20 行程度で書ける

## 使いどころ
- 連結成分の数を数える
- 無向グラフの閉路検出
- クラスカル法（最小全域木）
- 同値関係のグループ化（アカウント統合、同義語）

## 注意点
- `find` は経路圧縮で `parent` を書き換えるので `const` にできない
- `parent[a] = b` のように根ではなく要素同士をつながないこと（必ず `find` した根同士）
- 再帰の `find` は n が非常に大きく最適化が効かない場合にスタックが深くなる。気になるならループ版で書く
