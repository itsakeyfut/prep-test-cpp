/**
 * Graph（グラフ）- 解答
 *
 * problems.cpp の解答です。
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

// 4方向移動
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

// ========================================
// 解答1: グラフの表現
// ========================================

void createAdjacencyList(int n, vector<vector<int>> &edges)
{
    vector<vector<int>> graph(n);

    for (auto &edge : edges)
    {
        int u = edge[0], v = edge[1];
        graph[u].push_back(v);
        graph[v].push_back(u); // 無向グラフ
    }
}

void createWeightedGraph(int n, vector<vector<int>> &edges)
{
    vector<vector<pair<int, int>>> graph(n); // {隣接ノード, 重み}

    for (auto &edge : edges)
    {
        int u = edge[0], v = edge[1], w = edge[2];
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // 無向グラフ
    }
}

// ========================================
// 解答2: DFS - 再帰
// ========================================

void dfsRecursive(vector<vector<int>> &graph, int start)
{
    int n = graph.size();
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

    dfs(dfs, start);
}

// ========================================
// 解答3: DFS - 反復
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
// 解答4: BFS
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
// 解答5: Grid BFS
// ========================================

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

            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                grid[nx][ny] == 0 && dist[nx][ny] == -1)
            {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return -1;
}

// ========================================
// 解答6: Number of Islands
// ========================================

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

// ========================================
// 解答7: Course Schedule - トポロジカルソート
// ========================================

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

// ========================================
// 解答8: Union-Find
// ========================================

class UnionFind
{
private:
    vector<int> parent;
    vector<int> rank_;

public:
    UnionFind(int n) : parent(n), rank_(n, 0)
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
        if (rank_[px] < rank_[py])
        {
            swap(px, py);
        }

        parent[py] = px;
        if (rank_[px] == rank_[py])
        {
            rank_[px]++;
        }

        return true;
    }

    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }
};

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
// 解答9: Dijkstra
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
// 解答10: サイクル検出
// ========================================

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
    vector<vector<int>> graph = {
        {1, 2},
        {0, 3},
        {0, 3},
        {1, 2, 4},
        {3}};

    cout << "=== BFS from node 0 ===\n";
    bfs(graph, 0);
    cout << "\n";

    cout << "=== DFS from node 0 ===\n";
    dfsRecursive(graph, 0);
    cout << "\n";

    UnionFind uf(5);
    uf.unite(0, 1);
    uf.unite(1, 2);
    uf.unite(3, 4);

    cout << "\n=== Union-Find ===\n";
    cout << "0 and 2 connected: " << uf.connected(0, 2) << "\n";
    cout << "0 and 3 connected: " << uf.connected(0, 3) << "\n";

    return 0;
}
