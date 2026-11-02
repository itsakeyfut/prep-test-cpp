# Topological Sort - トポロジカルソート

## 概要
トポロジカルソートは、有向グラフの頂点を「すべての辺 u→v について u が v より前に来る」ように並べることです。サイクルのない有向グラフ（DAG: Directed Acyclic Graph）でのみ可能で、サイクルがあれば並べられないので **サイクル検出** にも使えます。代表的な実装は **Kahn のアルゴリズム（BFS）** と **DFS の帰りがけ順** の2つです。

## 目的
- 「A をやる前に B が必要」という依存関係の順序付け（履修順、ビルド順、タスク実行順）
- 有向グラフのサイクル検出（LeetCode 207 は実質これだけ）
- DAG 上の DP（最長経路など）の処理順を決める

## 達成条件
- [ ] 何も見ずに main.cpp を20分以内に手書きできる
- [ ] Kahn のアルゴリズムで入次数を数え、0 の頂点からキューで処理できる
- [ ] 「結果の長さ < n ならサイクルあり」を説明できる
- [ ] DFS の3状態（0: 未訪問, 1: 訪問中, 2: 完了）でサイクルを検出できる
- [ ] DFS では帰りがけ順を**逆順**にする理由を説明できる
- [ ] 計算量 O(V + E) を説明できる
- [ ] LeetCode 207. Course Schedule を解ける
- [ ] LeetCode 210. Course Schedule II を解ける
- [ ] LeetCode 802. Find Eventual Safe States を解ける
- [ ] LeetCode 2115. Find All Possible Recipes from Given Supplies を解ける
- [ ] LeetCode 269. Alien Dictionary の方針を説明できる（プレミアム）

## トポロジカルソートの動き
サンプル DAG（辺: 5→2, 5→0, 4→0, 4→1, 2→3, 3→1）：
```
  5       4
 / \     / \
v   v   v   v
2    0       1
|            ^
v            |
3 -----------+
```

### Kahn のアルゴリズム
```
入次数: 0=2  1=2  2=1  3=1  4=0  5=0
queue: [4, 5]                       （入次数 0 を全部入れる）

pop 4 → 0:2→1, 1:2→1                queue: [5]          order: 4
pop 5 → 2:1→0 push, 0:1→0 push      queue: [2, 0]       order: 4 5
pop 2 → 3:1→0 push                  queue: [0, 3]       order: 4 5 2
pop 0                               queue: [3]          order: 4 5 2 0
pop 3 → 1:1→0 push                  queue: [1]          order: 4 5 2 0 3
pop 1                               queue: []           order: 4 5 2 0 3 1
```

### DFS（帰りがけ順の逆）
```
dfs(0) → 完了: 0
dfs(1) → 完了: 1
dfs(2) → dfs(3) → 1 は完了済 → 完了: 3 → 完了: 2
dfs(4) → 0,1 完了済 → 完了: 4
dfs(5) → 2,0 完了済 → 完了: 5

帰りがけ順: 0 1 3 2 4 5
逆順:       5 4 2 3 1 0
```
答えは1通りとは限りません。Kahn と DFS で結果が違っても、どちらも正しい順序です。

### サイクルがある場合（0→1→2→0）
- Kahn: 入次数 0 の頂点がなく、order が空のまま → 長さ 0 < 3 でサイクル
- DFS: 0(訪問中) → 1(訪問中) → 2(訪問中) → 0 が「訪問中」→ 後退辺でサイクル

## コードの解説

### 隣接リストの構築（main.cpp:8-16）
```cpp
for (const auto &[u, v] : edges)
    adj[u].push_back(v);   // 有向なので片方向のみ
```
- LeetCode 207/210 の `prerequisites[i] = [a, b]` は「b → a」の辺なので向きに注意

### Kahn のアルゴリズム（main.cpp:18-51）
```cpp
// 入次数を数える（main.cpp:21-26）
for (int u = 0; u < n; ++u)
    for (int v : adj[u])
        ++indegree[v];

// 入次数 0 をすべてキューへ（main.cpp:28-33）
for (int u = 0; u < n; ++u)
    if (indegree[u] == 0)
        q.push(u);

// 取り出して、行き先の入次数を減らす（main.cpp:35-46）
while (!q.empty())
{
    int u = q.front();
    q.pop();
    order.push_back(u);
    for (int v : adj[u])
        if (--indegree[v] == 0)   // 前提がすべて済んだら
            q.push(v);
}

// サイクル判定（main.cpp:48-50）
if (static_cast<int>(order.size()) != n)
    return {};                    // 全部並べられなかった = サイクル
```

### DFS 本体（main.cpp:53-66）
```cpp
state[u] = 1;                     // 訪問中
for (int v : adj[u])
{
    if (state[v] == 1)
        return false;             // 訪問中に戻ってきた = サイクル
    if (state[v] == 0 && !dfs(adj, v, state, order))
        return false;
}
state[u] = 2;                     // 完了
order.push_back(u);               // 帰りがけに追加
return true;
```
- `visited` の bool だけでは「別経路で既に完了した頂点」と「今の経路上の頂点」を区別できない → 3状態が必要

### DFS ラッパー（main.cpp:68-80）
```cpp
for (int u = 0; u < n; ++u)
    if (state[u] == 0 && !dfs(adj, u, state, order))
        return {};
std::reverse(order.begin(), order.end());   // 帰りがけ順を逆にする
```
- 帰りがけ順では「依存先が先に」並ぶので、逆にすると u→v で u が前になる

### main（main.cpp:97-108）
- DAG と サイクルありグラフの両方で Kahn と DFS を実行し、サイクル時は `cycle detected` を出力

## 計算量
- **時間計算量**: O(V + E)（Kahn、DFS とも）
- **空間計算量**: O(V)（入次数配列 / 状態配列、キュー / 再帰スタック）

## 特徴
| | Kahn（BFS） | DFS |
|---|------------|-----|
| サイクル検出 | 結果の長さ < n | 訪問中の頂点に再訪 |
| 再帰 | 不要 | 必要（深いと危険） |
| 辞書順最小 | キューを `priority_queue` に変えれば可 | 難しい |
| 書きやすさ | 直感的 | 短い |

## 使いどころ
- 履修順・ビルド順・タスクスケジューリング
- 有向グラフのサイクル検出
- DAG 上の最長経路 / DP（トポロジカル順に緩和する）

## 注意点
- 無向グラフのサイクル検出には使えない（無向は Union-Find か DFS で親を除外）
- 「並べられるか」だけ聞かれたら、Kahn で処理した頂点数を数えるだけでよい
