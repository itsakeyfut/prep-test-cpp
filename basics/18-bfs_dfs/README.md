# BFS / DFS - 幅優先探索 / 深さ優先探索

## 概要
BFS（Breadth-First Search）はキューを使い、始点から近い順に頂点を訪問します。DFS（Depth-First Search）は再帰またはスタックを使い、行けるところまで深く進んでから戻ります。どちらもグラフ上のすべての頂点を O(V + E) で訪問する基本の探索です。

## 目的
- グラフ問題の大半は BFS か DFS の応用（連結成分、最短経路、サイクル検出、トポロジカルソート）
- **重みなしグラフの最短距離は BFS** で求まる
- グリッド（2次元配列）の島・塗りつぶし問題は、グリッドをグラフとみなした BFS/DFS
- 再帰 DFS が深すぎてスタックオーバーフローする場合に、スタック版へ書き換えられるようにする

## 達成条件
- [ ] 何も見ずに main.cpp を20分以内に手書きできる
- [ ] BFS で距離配列 `dist` を作り、重みなし最短距離を求められる
- [ ] 再帰 DFS とスタック DFS の両方を書け、訪問順が一致する理由を説明できる
- [ ] グリッドの4方向移動（`dr`, `dc`）と範囲チェックを迷わず書ける
- [ ] BFS で「キューに入れる時に訪問済みにする」理由を説明できる
- [ ] 計算量 O(V + E)、グリッドなら O(R × C) を説明できる
- [ ] LeetCode 200. Number of Islands を解ける
- [ ] LeetCode 733. Flood Fill を解ける
- [ ] LeetCode 695. Max Area of Island を解ける
- [ ] LeetCode 547. Number of Provinces を解ける
- [ ] LeetCode 994. Rotting Oranges を解ける（多始点 BFS）
- [ ] LeetCode 1091. Shortest Path in Binary Matrix を解ける
- [ ] LeetCode 797. All Paths From Source to Target を解ける
- [ ] LeetCode 127. Word Ladder を解ける

## BFS / DFS の動き
サンプルグラフ（無向）：
```
  0 --- 1
  |     |
  2 --- 3 --- 4 --- 5
```

### BFS（始点 0）
```
queue: [0]          dist: 0=0
pop 0 → 1,2 を追加  queue: [1, 2]   dist: 1=1, 2=1
pop 1 → 3 を追加    queue: [2, 3]   dist: 3=2
pop 2 → 3 は訪問済  queue: [3]
pop 3 → 4 を追加    queue: [4]      dist: 4=3
pop 4 → 5 を追加    queue: [5]      dist: 5=4
pop 5               queue: []

結果: 0 1 1 2 3 4
```
同じ距離の頂点が「層」ごとに処理されるので、最初に到達した時の距離が最短になります。

### DFS（始点 0）
```
0 → 1 → 3 → 2（0,3 訪問済で戻る）
        3 → 4 → 5

訪問順: 0 1 3 2 4 5
```

### Number of Islands
```
1 1 0 0 0      A A . . .
1 1 0 0 0  →   A A . . .
0 0 1 0 0      . . B . .
0 0 0 1 1      . . . C C     → 3
```
`'1'` を見つけたら島の数を +1 し、BFS でつながった `'1'` をすべて `'0'` に塗りつぶします。

## コードの解説

### BFS（main.cpp:7-27）
```cpp
std::vector<int> dist(adj.size(), -1);  // -1 = 未訪問
std::queue<int> q;
dist[start] = 0;
q.push(start);
while (!q.empty())
{
    int u = q.front();
    q.pop();
    for (int v : adj[u])
    {
        if (dist[v] == -1)           // 未訪問なら
        {
            dist[v] = dist[u] + 1;   // 距離を確定してから
            q.push(v);               // キューに入れる
        }
    }
}
```
- `dist` が訪問済みフラグを兼ねる
- キューに入れる時点で訪問済みにしないと、同じ頂点が何度もキューに入る

### DFS 再帰（main.cpp:29-40）
```cpp
void dfs_recursive(adj, int u, visited, order)
{
    visited[u] = true;
    order.push_back(u);
    for (int v : adj[u])
    {
        if (!visited[v])
            dfs_recursive(adj, v, visited, order);  // 深く潜る
    }
}
```
- 最も短く書ける。木の走査・サイクル検出・トポロジカルソートの基本形

### DFS スタック（main.cpp:42-63）
```cpp
st.push(start);
while (!st.empty())
{
    int u = st.top();
    st.pop();
    if (visited[u])
        continue;               // 取り出した時点で訪問済みチェック
    visited[u] = true;
    order.push_back(u);
    for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it)
    {
        if (!visited[*it])
            st.push(*it);       // 逆順に積むと再帰版と同じ順になる
    }
}
```
- スタックは後入れ先出しなので、隣接リストを逆順に積むと小さい番号から訪問される
- BFS と違い「取り出した時に」訪問済みにする

### Number of Islands（main.cpp:65-100）
```cpp
int dr[] = {1, -1, 0, 0};   // 下 上 右 左
int dc[] = {0, 0, 1, -1};
...
if (grid[r][c] != '1')
    continue;
++count;                     // 新しい島
grid[r][c] = '0';            // 訪問済みにする（元のグリッドを書き換え）
...
if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == '1')
{
    grid[nr][nc] = '0';
    q.push({nr, nc});
}
```
- グリッドを値渡ししているので呼び出し元は変わらない
- `visited` 配列を別に持つ代わりに `'0'` で塗りつぶすのが定番テク

### main（main.cpp:111-141）
- `edges` から無向の隣接リストを作り（main.cpp:113-119）、BFS・DFS 2種・島の数を出力

## 計算量
- **BFS / DFS**: 時間 O(V + E)、空間 O(V)
- **グリッド BFS**: 時間 O(R × C)、空間 O(min(R, C))〜O(R × C)

## 特徴
| | BFS | DFS |
|---|-----|-----|
| データ構造 | キュー | 再帰 / スタック |
| 訪問順 | 近い順（層ごと） | 深い順 |
| 重みなし最短距離 | ◯ | ✕ |
| 経路の全列挙・バックトラック | △ | ◯ |
| サイクル検出・トポロジカルソート | ◯（Kahn） | ◯ |

## 使いどころ
- **BFS**: 最短手数、最小ステップ数、多始点からの拡散（腐ったオレンジ）、レベル順走査
- **DFS**: 連結成分の数、経路の列挙、サイクル検出、木の問題全般

## 注意点
- 再帰 DFS は深さ 10⁵ 程度でスタックオーバーフローの危険がある → スタック版か BFS に
- グリッドの範囲チェックは `grid[nr][nc]` を参照する**前**に行う（`&&` の短絡評価）
- 多始点 BFS は、最初にすべての始点をキューに入れてから開始する
