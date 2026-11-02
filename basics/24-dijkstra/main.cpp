#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

constexpr int INF = 1'000'000'000;

using Graph = std::vector<std::vector<std::pair<int, int>>>;

std::vector<int> dijkstra(const Graph &adj, int src, std::vector<int> &prev)
{
    int n = adj.size();
    std::vector<int> dist(n, INF);
    prev.assign(n, -1);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u])
            continue;
        for (auto [v, w] : adj[u])
        {
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

std::vector<int> build_path(const std::vector<int> &prev, int target)
{
    std::vector<int> path;
    for (int v = target; v != -1; v = prev[v])
    {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

int main()
{
    Graph adj(7);
    adj[0] = {{1, 7}, {2, 9}, {5, 14}};
    adj[1] = {{2, 10}, {3, 15}};
    adj[2] = {{3, 11}, {5, 2}};
    adj[3] = {{4, 6}};
    adj[5] = {{4, 9}};

    std::vector<int> prev;
    std::vector<int> dist = dijkstra(adj, 0, prev);

    for (int v = 0; v < static_cast<int>(adj.size()); ++v)
    {
        std::cout << "0 -> " << v << ": ";
        if (dist[v] == INF)
        {
            std::cout << "unreachable\n";
            continue;
        }
        std::cout << "dist=" << dist[v] << " path=";
        for (int p : build_path(prev, v))
        {
            std::cout << p << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
