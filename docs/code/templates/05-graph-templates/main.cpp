/**
 * Graph（グラフ）アルゴリズム テンプレート
 * Google/Snap で超頻出
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

// ========================================
// グラフの表現方法
// ========================================

// 隣接リスト（最も一般的）
void createAdjacencyList()
{
    int n = 5; // ノード数
    vector<vector<int>> graph(n);

    // 辺を追加
    graph[0].push_back(1);
    graph[0].push_back(2);
    graph[1].push_back(3);
    graph[2].push_back(3);
    graph[3].push_back(4);
}

// 重み付きグラフ
void createWeightedGraph()
{
    int n = 5;
    vector<vector<pair<int, int>>> graph(n); // {隣接ノード, 重み}

    graph[0].push_back({1, 10});
    graph[0].push_back({2, 5});
    graph[1].push_back({3, 2});
}

// 隣接行列（密なグラフ）
void createAdjacencyMatrix()
{
    int n = 5;
    vector<vector<int>> matrix(n, vector<int>(n, 0));

    matrix[0][1] = 1; // 0 -> 1 の辺
    matrix[0][2] = 1;
}

// ========================================
// パターン1: DFS（深さ優先探索）- 再帰
// ========================================

void dfsRecursive()
{
    int n = 5;
    vector<vector<int>> graph(n);
    // グラフ構築...

    vector<bool> visited(n, false);

    auto dfs = [&](auto &&self, int node) -> void
    {
        visited[node] = true;
        cout << node << " ";

        for (int neighbor : graph[node])
        {
            if (!visited[neighbor])
            {
                self(self, neighbor);
            }
        }
    };

    dfs(dfs, 0); // ノード0から開始
}

// ========================================
// パターン2: DFS - 反復（スタック）
// ========================================

void dfsIterative(vector<vector<int>> &graph, int start)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    stack<int> st;

    st.push(start);

    while (!st.empty())
    {
        int node = st.top();
        st.pop();

        if (visited[node])
            continue;

        visited[node] = true;
        cout << node << " ";

        for (int neighbor : graph[node])
        {
            if (!visited[neighbor])
            {
                st.push(neighbor);
            }
        }
    }
}

// ========================================
// パターン3: BFS（幅優先探索）
// ========================================

void bfs(vector<vector<int>> &graph, int start)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        cout << node << " ";

        for (int neighbor : graph[node])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

// 最短距離を求めるBFS
vector<int> bfsDistance(vector<vector<int>> &graph, int start)
{
    int n = graph.size();
    vector<int> dist(n, -1);
    queue<int> q;

    q.push(start);
    dist[start] = 0;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (int neighbor : graph[node])
        {
            if (dist[neighbor] == -1)
            {
                dist[neighbor] = dist[node] + 1;
                q.push(neighbor);
            }
        }
    }

    return dist;
}

// ========================================
// パターン4: Grid での BFS/DFS
// ========================================

// 4方向移動
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

// Grid BFS（最短経路）
int gridBFS(vector<vector<int>> &grid, pair<int, int> start, pair<int, int> end)
{
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;

    q.push(start);
    dist[start.first][start.second] = 0;

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        if (x == end.first && y == end.second)
        {
            return dist[x][y];
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 0 && dist[nx][ny] == -1)
            {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return -1; // 到達不可
}

// Grid DFS
void gridDFS(vector<vector<int>> &grid, int x, int y, vector<vector<bool>> &visited)
{
    int n = grid.size();
    int m = grid[0].size();

    if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y] || grid[x][y] == 1)
    {
        return;
    }

    visited[x][y] = true;

    for (int i = 0; i < 4; i++)
    {
        gridDFS(grid, x + dx[i], y + dy[i], visited);
    }
}

// ========================================
// 実戦問題パターン
// ========================================

// 問題1: Number of Islands (LC 200)
int numIslands(vector<vector<char>> &grid)
{
    if (grid.empty())
        return 0;

    int n = grid.size();
    int m = grid[0].size();
    int count = 0;

    auto dfs = [&](auto &&self, int x, int y) -> void
    {
        if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == '0')
        {
            return;
        }

        grid[x][y] = '0'; // 訪問済みマーク

        for (int i = 0; i < 4; i++)
        {
            self(self, x + dx[i], y + dy[i]);
        }
    };

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '1')
            {
                count++;
                dfs(dfs, i, j);
            }
        }
    }

    return count;
}

// 問題2: Clone Graph (LC 133)
class Node
{
public:
    int val;
    vector<Node *> neighbors;
    Node(int _val) : val(_val) {}
};

Node *cloneGraph(Node *node)
{
    if (!node)
        return nullptr;

    unordered_map<Node *, Node *> clones;

    auto dfs = [&](auto &&self, Node *n) -> Node *
    {
        if (clones.count(n))
            return clones[n];

        Node *clone = new Node(n->val);
        clones[n] = clone;

        for (Node *neighbor : n->neighbors)
        {
            clone->neighbors.push_back(self(self, neighbor));
        }

        return clone;
    };

    return dfs(dfs, node);
}

// 問題3: Course Schedule (LC 207) - トポロジカルソート
bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
{
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses, 0);

    // グラフ構築
    for (auto &pre : prerequisites)
    {
        graph[pre[1]].push_back(pre[0]);
        indegree[pre[0]]++;
    }

    // 入次数0のノードをキューに
    queue<int> q;
    for (int i = 0; i < numCourses; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    int count = 0;
    while (!q.empty())
    {
        int course = q.front();
        q.pop();
        count++;

        for (int next : graph[course])
        {
            indegree[next]--;
            if (indegree[next] == 0)
            {
                q.push(next);
            }
        }
    }

    return count == numCourses;
}

// 問題4: Pacific Atlantic Water Flow (LC 417)
vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
{
    int n = heights.size();
    int m = heights[0].size();

    vector<vector<bool>> pacific(n, vector<bool>(m, false));
    vector<vector<bool>> atlantic(n, vector<bool>(m, false));

    auto dfs = [&](auto &&self, int x, int y, vector<vector<bool>> &visited) -> void
    {
        visited[x][y] = true;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && heights[nx][ny] >= heights[x][y])
            {
                self(self, nx, ny, visited);
            }
        }
    };

    // 太平洋側から
    for (int i = 0; i < n; i++)
        dfs(dfs, i, 0, pacific);
    for (int j = 0; j < m; j++)
        dfs(dfs, 0, j, pacific);

    // 大西洋側から
    for (int i = 0; i < n; i++)
        dfs(dfs, i, m - 1, atlantic);
    for (int j = 0; j < m; j++)
        dfs(dfs, n - 1, j, atlantic);

    // 両方到達できるセル
    vector<vector<int>> result;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (pacific[i][j] && atlantic[i][j])
            {
                result.push_back({i, j});
            }
        }
    }

    return result;
}

// ========================================
// Union-Find（素集合データ構造）
// ========================================

class UnionFind
{
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]); // 経路圧縮
        }
        return parent[x];
    }

    bool unite(int x, int y)
    {
        int px = find(x);
        int py = find(y);

        if (px == py)
            return false; // すでに同じ集合

        // ランクによる結合
        if (rank[px] < rank[py])
        {
            swap(px, py);
        }

        parent[py] = px;
        if (rank[px] == rank[py])
        {
            rank[px]++;
        }

        return true;
    }

    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }
};

// Union-Find の使用例
int countComponents(int n, vector<vector<int>> &edges)
{
    UnionFind uf(n);

    for (auto &edge : edges)
    {
        uf.unite(edge[0], edge[1]);
    }

    unordered_set<int> roots;
    for (int i = 0; i < n; i++)
    {
        roots.insert(uf.find(i));
    }

    return roots.size();
}

// ========================================
// Dijkstra（最短経路）
// ========================================

vector<int> dijkstra(vector<vector<pair<int, int>>> &graph, int start)
{
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start}); // {距離, ノード}

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto [v, weight] : graph[u])
        {
            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

// ========================================
// サイクル検出
// ========================================

// 無向グラフのサイクル検出（DFS）
bool hasCycleUndirected(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<bool> visited(n, false);

    auto dfs = [&](auto &&self, int node, int parent) -> bool
    {
        visited[node] = true;

        for (int neighbor : graph[node])
        {
            if (!visited[neighbor])
            {
                if (self(self, neighbor, node))
                    return true;
            }
            else if (neighbor != parent)
            {
                return true; // サイクル発見
            }
        }

        return false;
    };

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            if (dfs(dfs, i, -1))
                return true;
        }
    }

    return false;
}

// 有向グラフのサイクル検出（DFS）
bool hasCycleDirected(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<int> state(n, 0); // 0: 未訪問, 1: 処理中, 2: 完了

    auto dfs = [&](auto &&self, int node) -> bool
    {
        state[node] = 1;

        for (int neighbor : graph[node])
        {
            if (state[neighbor] == 1)
                return true; // 後退辺＝サイクル
            if (state[neighbor] == 0 && self(self, neighbor))
                return true;
        }

        state[node] = 2;
        return false;
    };

    for (int i = 0; i < n; i++)
    {
        if (state[i] == 0)
        {
            if (dfs(dfs, i))
                return true;
        }
    }

    return false;
}

int main()
{
    // テスト: BFS
    vector<vector<int>> graph = {
        {1, 2},    // 0
        {0, 3},    // 1
        {0, 3},    // 2
        {1, 2, 4}, // 3
        {3}        // 4
    };

    cout << "BFS from node 0: ";
    bfs(graph, 0);
    cout << "\n";

    cout << "DFS from node 0: ";
    dfsRecursive();
    cout << "\n";

    // Union-Find テスト
    UnionFind uf(5);
    uf.unite(0, 1);
    uf.unite(1, 2);
    uf.unite(3, 4);

    cout << "0 and 2 connected: " << uf.connected(0, 2) << "\n";
    cout << "0 and 3 connected: " << uf.connected(0, 3) << "\n";

    return 0;
}

/**
 * 暗記チェックリスト:
 *
 * [ ] 隣接リストでグラフを表現
 * [ ] DFS（再帰・反復）を書ける
 * [ ] BFS を書ける
 * [ ] Grid での BFS/DFS
 * [ ] 訪問済み管理（visited配列）
 * [ ] トポロジカルソート
 * [ ] Union-Find の実装
 * [ ] Dijkstra の実装
 * [ ] サイクル検出（無向・有向）
 * [ ] 4方向移動の定義
 */