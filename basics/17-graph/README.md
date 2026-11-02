# Graph - グラフ (Graph Representation)

## 概要
グラフは、頂点（ノード）と辺（エッジ）の集合で「つながり」を表すデータ構造です。辺に向きがあるものを有向グラフ、向きがないものを無向グラフと呼びます。コード上では主に **隣接リスト** と **隣接行列** の2通りで表現します。

## 目的
- BFS / DFS / トポロジカルソート / ダイクストラなど、すべてのグラフアルゴリズムの土台になる
- LeetCode のグラフ問題は「辺のリスト `edges` から隣接リストを組み立てる」ところから始まることがほとんど
- 隣接リストと隣接行列の使い分け（メモリ・辺の有無判定の速さ）を説明できるようにする

## 達成条件
- [ ] 何も見ずに main.cpp を10分以内に手書きできる
- [ ] `edges` から有向・無向の隣接リストを即座に組み立てられる
- [ ] 隣接リストと隣接行列の空間計算量・辺の判定コストの違いを説明できる
- [ ] 疎グラフ / 密グラフでどちらを選ぶべきか説明できる
- [ ] LeetCode 1971. Find if Path Exists in Graph を解ける
- [ ] LeetCode 997. Find the Town Judge を解ける（入次数・出次数）
- [ ] LeetCode 1791. Find Center of Star Graph を解ける
- [ ] LeetCode 133. Clone Graph を解ける

## グラフの動き
辺 `(0,1) (0,2) (1,3) (2,3) (3,4)` を追加した場合：

```
無向グラフ                 有向グラフ

  0 --- 1                  0 ---> 1
  |     |                  |      |
  2 --- 3 --- 4            v      v
                           2 ---> 3 ---> 4
```

隣接リスト（各頂点から行ける頂点の一覧）：
```
無向            有向
0: 1 2          0: 1 2
1: 0 3          1: 3
2: 0 3          2: 3
3: 1 2 4        3: 4
4: 3            4:
```

隣接行列（`matrix[u][v] == 1` なら u→v の辺あり）：
```
無向              有向
  0 1 2 3 4         0 1 2 3 4
0 0 1 1 0 0       0 0 1 1 0 0
1 1 0 0 1 0       1 0 0 0 1 0
2 1 0 0 1 0       2 0 0 0 1 0
3 0 1 1 0 1       3 0 0 0 0 1
4 0 0 0 1 0       4 0 0 0 0 0
```
無向グラフの行列は対角線に対して対称になります。

## コードの解説

### メンバ変数（main.cpp:8-11）
```cpp
int n;                                     // 頂点数
bool directed;                             // 有向かどうか
std::vector<std::vector<int>> adj_list;    // 隣接リスト
std::vector<std::vector<int>> adj_matrix;  // 隣接行列
```
- 学習用に同じグラフを2つの表現で同時に持つ

### コンストラクタ（main.cpp:14-15）
```cpp
Graph(int size, bool is_directed)
    : n(size), directed(is_directed),
      adj_list(size),                                  // 空のリストを n 個
      adj_matrix(size, std::vector<int>(size, 0)) {}   // n×n の 0 行列
```

### 辺の追加（main.cpp:17-26）
```cpp
void add_edge(int u, int v)
{
    adj_list[u].push_back(v);   // u → v
    adj_matrix[u][v] = 1;
    if (!directed)
    {
        adj_list[v].push_back(u);  // 無向なら逆向きも追加
        adj_matrix[v][u] = 1;
    }
}
```
- 無向グラフは「両方向の有向辺」として扱うのがポイント

### 辺の判定と隣接頂点（main.cpp:28-36）
```cpp
bool has_edge(int u, int v) const
{
    return adj_matrix[u][v] == 1;  // 行列なら O(1)
}

const std::vector<int> &neighbors(int u) const
{
    return adj_list[u];            // リストなら隣接頂点を直接列挙できる
}
```

### 出力（main.cpp:38-61）
- `print_list` は各頂点の隣接リストを、`print_matrix` は n×n の行列をそのまま出力

### main（main.cpp:64-97）
```cpp
std::vector<std::pair<int, int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}};
for (const auto &[u, v] : edges)   // 構造化束縛で (u, v) を取り出す
{
    undirected.add_edge(u, v);
    directed.add_edge(u, v);
}
```
- LeetCode の `edges` 入力と同じ形。この「edges → 隣接リスト」は毎回書くので指に覚えさせる
- 3→1 は無向では Yes、有向では No になる

## 計算量
| 操作 | 隣接リスト | 隣接行列 |
|------|-----------|---------|
| 空間 | O(V + E) | O(V²) |
| 辺の追加 | O(1) | O(1) |
| 辺 (u,v) の有無判定 | O(deg(u)) | O(1) |
| u の隣接頂点を列挙 | O(deg(u)) | O(V) |
| 全辺を走査 | O(V + E) | O(V²) |

## 特徴
- **隣接リスト**: 疎グラフ（E が V² よりずっと小さい）に強い。LeetCode ではほぼこちら
- **隣接行列**: 密グラフや、辺の有無を頻繁に判定する場合、Floyd-Warshall で便利
- **無向 = 双方向の有向**: 実装上は両方向に辺を張るだけ

## 使いどころ
- すべてのグラフ問題の入力変換
- 依存関係（コース・タスク）、ネットワーク、地図、SNS の友達関係のモデル化
- グリッド問題も「各マスが頂点、上下左右が辺」のグラフとみなせる

## 注意点
- 頂点番号が 1 始まりの問題では `adj(n + 1)` にするか `u - 1` に変換する
- 重み付きグラフは `std::vector<std::vector<std::pair<int, int>>>`（行き先, 重み）にする
- V が 10⁵ 規模だと隣接行列はメモリ不足になる
