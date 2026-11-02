# MST - 最小全域木 (Minimum Spanning Tree)

## 概要
最小全域木は、重み付き無向グラフの **すべての頂点をつなぐ木（V-1 本の辺）のうち、辺の重みの合計が最小のもの** です。代表的なアルゴリズムは、辺を軽い順に採用する **クラスカル法（Union-Find）** と、1つの頂点から木を広げていく **プリム法（優先度付きキュー）** の2つです。

## 目的
- 「すべてを最小コストでつなぐ」問題（配線・道路・ネットワーク）の定番
- クラスカル法を通して **Union-Find** を身につける（連結判定・冗長辺の検出など単独でも頻出）
- プリム法はダイクストラとほぼ同じ形なので、両者の違いを理解できる

## 達成条件
- [ ] 何も見ずに main.cpp を20分以内に手書きできる
- [ ] Union-Find の `find`（経路圧縮）と `unite`（ランク）を3分で書ける
- [ ] クラスカル法で「同じ集合ならサイクルになるので捨てる」理由を説明できる
- [ ] プリム法とダイクストラの違い（pq に入れるのが「辺の重み」か「始点からの距離」か）を説明できる
- [ ] 計算量（クラスカル O(E log E)、プリム O(E log V)）と使い分けを説明できる
- [ ] LeetCode 1584. Min Cost to Connect All Points を解ける
- [ ] LeetCode 1135. Connecting Cities With Minimum Cost を解ける（プレミアム）
- [ ] LeetCode 1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree を解ける
- [ ] LeetCode 684. Redundant Connection を Union-Find で解ける
- [ ] LeetCode 547. Number of Provinces を Union-Find で解ける

## MST の動き
サンプルグラフ（無向）：
```
        2         3
    0 ------ 1 ------ 2
    |      / |        |
   6|    8/  |5       |7
    |    /   |        |
    3 --+    4 -------+
     \       |
      +--9---+
```
辺: 0-1(2), 0-3(6), 1-2(3), 1-3(8), 1-4(5), 2-4(7), 3-4(9)

### クラスカル法（辺を軽い順に）
```
重み順: 0-1(2) 1-2(3) 1-4(5) 0-3(6) 2-4(7) 1-3(8) 3-4(9)

0-1 (2): {0} と {1} は別 → 採用   集合: {0,1} {2} {3} {4}
1-2 (3): 別 → 採用               集合: {0,1,2} {3} {4}
1-4 (5): 別 → 採用               集合: {0,1,2,4} {3}
0-3 (6): 別 → 採用               集合: {0,1,2,3,4}
2-4 (7): 同じ集合 → サイクルになるので捨てる
1-3 (8): 捨てる
3-4 (9): 捨てる

合計: 2 + 3 + 5 + 6 = 16
```

### プリム法（頂点 0 から）
```
取り出し       木に追加   pq に追加
(0, 0, -1)    0         (2,1,0) (6,3,0)
(2, 1, 0)     0-1       (3,2,1) (8,3,1) (5,4,1)
(3, 2, 1)     1-2       (7,4,2)
(5, 4, 1)     1-4       (9,3,4)
(6, 3, 0)     0-3
残り (7,4,2) (8,3,1) (9,3,4) は木に含まれる頂点なのでスキップ

合計: 2 + 3 + 5 + 6 = 16
```

### 結果の MST
```
        2         3
    0 ------ 1 ------ 2
    |        |
   6|        |5
    |        |
    3        4
```

## コードの解説

### 辺の構造体（main.cpp:10-15）
```cpp
struct Edge
{
    int u;
    int v;
    int weight;
};
```

### Union-Find（main.cpp:17-45）
```cpp
explicit UnionFind(int n) : parent(n), rank(n, 0)
{
    std::iota(parent.begin(), parent.end(), 0);   // parent[i] = i（自分が根）
}

int find(int x)
{
    return parent[x] == x ? x : parent[x] = find(parent[x]);  // 経路圧縮
}

bool unite(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a == b)
        return false;              // 既に同じ集合
    if (rank[a] < rank[b])
        std::swap(a, b);           // 高い木の下に低い木をつなぐ
    parent[b] = a;
    if (rank[a] == rank[b])
        ++rank[a];
    return true;
}
```
- `find`（main.cpp:27-30）: 根をたどりながら、途中の頂点を根に直接つなぎ直す
- `unite`（main.cpp:32-44）: 結合できたら `true`、既に同じ集合なら `false` を返すのがクラスカルで便利

### クラスカル法（main.cpp:47-62）
```cpp
std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
          { return a.weight < b.weight; });     // 重みの昇順
UnionFind uf(n);
int total = 0;
for (const auto &e : edges)
{
    if (uf.unite(e.u, e.v))     // 別の集合なら採用（サイクルにならない）
    {
        total += e.weight;
    }
}
```
- `edges` は値渡しなので、呼び出し元の順序は変わらない

### プリム法（main.cpp:64-96）
```cpp
// 無向の隣接リストを作る（main.cpp:66-71）
adj[e.u].push_back({e.v, e.weight});
adj[e.v].push_back({e.u, e.weight});

// (重み, 頂点, どこから) の min-heap
std::priority_queue<std::tuple<int, int, int>,
                    std::vector<std::tuple<int, int, int>>,
                    std::greater<>> pq;
pq.push({0, 0, -1});                 // 頂点 0 から開始
while (!pq.empty())
{
    auto [w, v, from] = pq.top();
    pq.pop();
    if (in_tree[v])
        continue;                    // 既に木に入っている
    in_tree[v] = true;
    if (from != -1)
        total += w;                  // 始点以外は辺の重みを加算
    for (auto [to, weight] : adj[v])
        if (!in_tree[to])
            pq.push({weight, to, v});  // 距離ではなく「辺の重み」を入れる
}
```
- ダイクストラは `dist[u] + w`（始点からの累計）、プリムは `w`（その辺だけ）を pq に入れる

### main（main.cpp:98-112）
- 同じ辺リストでクラスカルとプリムを実行し、採用した辺と合計（どちらも 16）を出力

## 計算量
- **クラスカル法**: 時間 O(E log E)（ソートが支配的）、空間 O(V)
- **プリム法**: 時間 O(E log V)、空間 O(V + E)
- **Union-Find**: 1操作あたりほぼ O(1)（O(α(n))、α はアッカーマン関数の逆関数）

## 特徴
| | クラスカル法 | プリム法 |
|---|------------|---------|
| 考え方 | 軽い辺から採用 | 木を1頂点ずつ広げる |
| データ構造 | ソート + Union-Find | 優先度付きキュー |
| 向いているグラフ | 疎グラフ、辺リストで与えられる | 密グラフ、隣接リスト |
| 書きやすさ | Union-Find があれば短い | ダイクストラと同じ形 |

## 使いどころ
- ネットワーク・配線・道路を最小コストで全部つなぐ
- 点の座標だけ与えられる問題（全点間に辺がある完全グラフ）→ LeetCode 1584
- クラスタリング（MST から重い辺を k-1 本除く）

## 注意点
- MST は **無向グラフ** の概念。有向グラフには使えない
- グラフが非連結だと全域木は存在しない（採用した辺が V-1 本未満になる）
- 完全グラフ（E = V²）ではクラスカルのソートが重いので、プリム（または O(V²) 版プリム）が有利
