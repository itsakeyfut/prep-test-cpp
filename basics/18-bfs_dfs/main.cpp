#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

std::vector<int> bfs(const std::vector<std::vector<int>> &adj, int start)
{
    std::vector<int> dist(adj.size(), -1);
    std::queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
        {
            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

void dfs_recursive(const std::vector<std::vector<int>> &adj, int u, std::vector<bool> &visited, std::vector<int> &order)
{
    visited[u] = true;
    order.push_back(u);
    for (int v : adj[u])
    {
        if (!visited[v])
        {
            dfs_recursive(adj, v, visited, order);
        }
    }
}

std::vector<int> dfs_iterative(const std::vector<std::vector<int>> &adj, int start)
{
    std::vector<bool> visited(adj.size(), false);
    std::vector<int> order;
    std::stack<int> st;
    st.push(start);
    while (!st.empty())
    {
        int u = st.top();
        st.pop();
        if (visited[u])
            continue;
        visited[u] = true;
        order.push_back(u);
        for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it)
        {
            if (!visited[*it])
                st.push(*it);
        }
    }
    return order;
}

int num_islands(std::vector<std::vector<char>> grid)
{
    int rows = grid.size();
    int cols = grid[0].size();
    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};
    int count = 0;
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            if (grid[r][c] != '1')
                continue;
            ++count;
            grid[r][c] = '0';
            std::queue<std::pair<int, int>> q;
            q.push({r, c});
            while (!q.empty())
            {
                auto [cr, cc] = q.front();
                q.pop();
                for (int d = 0; d < 4; ++d)
                {
                    int nr = cr + dr[d];
                    int nc = cc + dc[d];
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == '1')
                    {
                        grid[nr][nc] = '0';
                        q.push({nr, nc});
                    }
                }
            }
        }
    }
    return count;
}

void print(const std::vector<int> &v)
{
    for (int x : v)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

int main()
{
    std::vector<std::vector<int>> adj(6);
    std::vector<std::pair<int, int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {4, 5}};
    for (const auto &[u, v] : edges)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::cout << "BFS distance from 0: ";
    print(bfs(adj, 0));

    std::vector<bool> visited(adj.size(), false);
    std::vector<int> order;
    dfs_recursive(adj, 0, visited, order);
    std::cout << "DFS recursive: ";
    print(order);

    std::cout << "DFS iterative: ";
    print(dfs_iterative(adj, 0));

    std::vector<std::vector<char>> grid = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}};
    std::cout << "Number of islands: " << num_islands(grid) << "\n";

    return 0;
}
