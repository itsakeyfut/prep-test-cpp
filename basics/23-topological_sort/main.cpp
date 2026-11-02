#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

std::vector<std::vector<int>> build(int n, const std::vector<std::pair<int, int>> &edges)
{
    std::vector<std::vector<int>> adj(n);
    for (const auto &[u, v] : edges)
    {
        adj[u].push_back(v);
    }
    return adj;
}

std::vector<int> kahn(const std::vector<std::vector<int>> &adj)
{
    int n = adj.size();
    std::vector<int> indegree(n, 0);
    for (int u = 0; u < n; ++u)
    {
        for (int v : adj[u])
            ++indegree[v];
    }

    std::queue<int> q;
    for (int u = 0; u < n; ++u)
    {
        if (indegree[u] == 0)
            q.push(u);
    }

    std::vector<int> order;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : adj[u])
        {
            if (--indegree[v] == 0)
                q.push(v);
        }
    }

    if (static_cast<int>(order.size()) != n)
        return {};
    return order;
}

bool dfs(const std::vector<std::vector<int>> &adj, int u, std::vector<int> &state, std::vector<int> &order)
{
    state[u] = 1;
    for (int v : adj[u])
    {
        if (state[v] == 1)
            return false;
        if (state[v] == 0 && !dfs(adj, v, state, order))
            return false;
    }
    state[u] = 2;
    order.push_back(u);
    return true;
}

std::vector<int> topo_dfs(const std::vector<std::vector<int>> &adj)
{
    int n = adj.size();
    std::vector<int> state(n, 0);
    std::vector<int> order;
    for (int u = 0; u < n; ++u)
    {
        if (state[u] == 0 && !dfs(adj, u, state, order))
            return {};
    }
    std::reverse(order.begin(), order.end());
    return order;
}

void print(const std::string &label, const std::vector<int> &order)
{
    std::cout << label << ": ";
    if (order.empty())
    {
        std::cout << "cycle detected\n";
        return;
    }
    for (int u : order)
    {
        std::cout << u << " ";
    }
    std::cout << "\n";
}

int main()
{
    auto dag = build(6, {{5, 2}, {5, 0}, {4, 0}, {4, 1}, {2, 3}, {3, 1}});
    print("Kahn (DAG)", kahn(dag));
    print("DFS  (DAG)", topo_dfs(dag));

    auto cyclic = build(3, {{0, 1}, {1, 2}, {2, 0}});
    print("Kahn (cycle)", kahn(cyclic));
    print("DFS  (cycle)", topo_dfs(cyclic));

    return 0;
}
