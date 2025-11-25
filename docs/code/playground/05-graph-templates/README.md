# Graph（グラフ）解説

## 1. グラフの表現方法

### 隣接リスト（最も一般的）

```cpp
int n = 5;  // ノード数
vector<vector<int>> graph(n);

// 辺を追加（無向グラフ）
graph[u].push_back(v);
graph[v].push_back(u);
```

### 重み付きグラフ

```cpp
vector<vector<pair<int, int>>> graph(n);  // {隣接ノード, 重み}

graph[u].push_back({v, weight});
graph[v].push_back({u, weight});
```

### 隣接行列（密なグラフ）

```cpp
vector<vector<int>> matrix(n, vector<int>(n, 0));

matrix[u][v] = 1;  // 辺がある
matrix[v][u] = 1;  // 無向グラフ
```

| 表現 | 空間 | 辺の追加 | 辺の存在確認 | 用途 |
|------|------|----------|--------------|------|
| 隣接リスト | O(V+E) | O(1) | O(degree) | 疎なグラフ |
| 隣接行列 | O(V²) | O(1) | O(1) | 密なグラフ |

---

## 2. DFS（深さ優先探索）

### 再帰版（ラムダ）

```cpp
vector<bool> visited(n, false);

auto dfs = [&](auto&& self, int node) -> void {
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            self(self, neighbor);
        }
    }
};

dfs(dfs, 0);  // ノード0から開始
```

### 反復版（スタック）

```cpp
vector<bool> visited(n, false);
stack<int> st;

st.push(start);

while (!st.empty()) {
    int node = st.top();
    st.pop();

    if (visited[node]) continue;

    visited[node] = true;
    cout << node << " ";

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            st.push(neighbor);
        }
    }
}
```

---

## 3. BFS（幅優先探索）

### 基本パターン

```cpp
vector<bool> visited(n, false);
queue<int> q;

q.push(start);
visited[start] = true;

while (!q.empty()) {
    int node = q.front();
    q.pop();

    cout << node << " ";

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            q.push(neighbor);
        }
    }
}
```

### 最短距離を求める

```cpp
vector<int> dist(n, -1);
queue<int> q;

q.push(start);
dist[start] = 0;

while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (int neighbor : graph[node]) {
        if (dist[neighbor] == -1) {
            dist[neighbor] = dist[node] + 1;
            q.push(neighbor);
        }
    }
}
```

**ポイント:** BFS は重みなしグラフで最短距離を求めるのに最適

---

## 4. Grid での BFS/DFS

### 4方向移動の定義

```cpp
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

// または
vector<pair<int,int>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
```

### Grid BFS

```cpp
int gridBFS(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> end) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int,int>> q;

    q.push(start);
    dist[start.first][start.second] = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == end.first && y == end.second) {
            return dist[x][y];
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 範囲チェック + 壁チェック + 未訪問チェック
            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                grid[nx][ny] == 0 && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return -1;  // 到達不可
}
```

---

## 5. Number of Islands (LC 200)

```cpp
int numIslands(vector<vector<char>>& grid) {
    int n = grid.size(), m = grid[0].size();
    int count = 0;

    auto dfs = [&](auto&& self, int x, int y) -> void {
        if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == '0') {
            return;
        }

        grid[x][y] = '0';  // 訪問済みマーク（grid を直接変更）

        for (int i = 0; i < 4; i++) {
            self(self, x + dx[i], y + dy[i]);
        }
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '1') {
                count++;
                dfs(dfs, i, j);
            }
        }
    }

    return count;
}
```

**ポイント:** grid を直接 `'0'` に書き換えて訪問済みをマーク

---

## 6. トポロジカルソート（Kahn's Algorithm）

DAG（有向非巡回グラフ）の順序付け。

```cpp
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses, 0);  // 入次数

    // グラフ構築
    for (auto& pre : prerequisites) {
        graph[pre[1]].push_back(pre[0]);
        indegree[pre[0]]++;
    }

    // 入次数0のノードをキューに
    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    int count = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        count++;

        for (int next : graph[node]) {
            indegree[next]--;
            if (indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    return count == numCourses;  // 全ノードを処理できたか
}
```

**考え方:**
1. 入次数（そのノードに入る辺の数）を計算
2. 入次数0のノードをキューに入れる
3. キューから取り出し、隣接ノードの入次数を減らす
4. 入次数が0になったらキューに追加

---

## 7. Union-Find（素集合データ構造）

```cpp
class UnionFind {
private:
    vector<int> parent;
    vector<int> rank_;

public:
    UnionFind(int n) : parent(n), rank_(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;  // 初期状態: 各要素は自分自身が親
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // 経路圧縮
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);

        if (px == py) return false;  // 既に同じ集合

        // ランクによる結合（小さい木を大きい木に結合）
        if (rank_[px] < rank_[py]) swap(px, py);

        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;

        return true;
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
```

**計算量:** 経路圧縮 + ランク結合で、ほぼ O(1)

**用途:**
- 連結成分のカウント
- サイクル検出（無向グラフ）
- Kruskal の最小全域木

---

## 8. Dijkstra（最短経路）

重み付きグラフで、単一始点から全ノードへの最短距離を求める。

```cpp
vector<int> dijkstra(vector<vector<pair<int,int>>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});  // {距離, ノード}

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;  // 古い情報はスキップ

        for (auto [v, weight] : graph[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}
```

**計算量:** O((V + E) log V)

**注意:** 負の重みがあると使えない（Bellman-Ford を使う）

---

## 9. サイクル検出

### 無向グラフ

```cpp
bool hasCycleUndirected(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);

    auto dfs = [&](auto&& self, int node, int parent) -> bool {
        visited[node] = true;

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                if (self(self, neighbor, node)) return true;
            } else if (neighbor != parent) {
                return true;  // 親以外の訪問済み = サイクル
            }
        }

        return false;
    };

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dfs(dfs, i, -1)) return true;
    }

    return false;
}
```

### 有向グラフ

```cpp
bool hasCycleDirected(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> state(n, 0);  // 0: 未訪問, 1: 処理中, 2: 完了

    auto dfs = [&](auto&& self, int node) -> bool {
        state[node] = 1;  // 処理中

        for (int neighbor : graph[node]) {
            if (state[neighbor] == 1) return true;  // 後退辺 = サイクル
            if (state[neighbor] == 0 && self(self, neighbor)) return true;
        }

        state[node] = 2;  // 完了
        return false;
    };

    for (int i = 0; i < n; i++) {
        if (state[i] == 0 && dfs(dfs, i)) return true;
    }

    return false;
}
```

---

## 10. DFS vs BFS の使い分け

| 問題タイプ | 推奨 | 理由 |
|-----------|------|------|
| 最短経路（重みなし） | BFS | レベル順 = 最短距離 |
| 連結成分 | DFS/BFS | どちらでも可 |
| サイクル検出 | DFS | 後退辺の検出が容易 |
| トポロジカルソート | BFS (Kahn) / DFS | BFSの方が直感的 |
| パス探索 | DFS | バックトラックが自然 |

---

## 11. 計算量まとめ

| アルゴリズム | 時間 | 空間 |
|-------------|------|------|
| DFS | O(V + E) | O(V) |
| BFS | O(V + E) | O(V) |
| トポロジカルソート | O(V + E) | O(V) |
| Union-Find | O(α(n)) ≈ O(1) | O(V) |
| Dijkstra | O((V+E) log V) | O(V) |

---

## 12. よくある間違い

### BFS で visited を push 前に設定しない

```cpp
// NG: 同じノードが複数回キューに入る
if (!visited[neighbor]) {
    q.push(neighbor);
}
visited[node] = true;

// OK: push と同時に visited を設定
if (!visited[neighbor]) {
    visited[neighbor] = true;
    q.push(neighbor);
}
```

### 無向グラフで辺を片方しか追加しない

```cpp
// NG: 有向グラフになってしまう
graph[u].push_back(v);

// OK: 両方向に追加
graph[u].push_back(v);
graph[v].push_back(u);
```
