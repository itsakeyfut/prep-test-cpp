#include <iostream>
#include <string>
#include <vector>

constexpr int INF = 1'000'000'000;

struct Edge
{
    int from;
    int to;
    int weight;
};

bool bellman_ford(int n, const std::vector<Edge> &edges, int src, std::vector<int> &dist)
{
    dist.assign(n, INF);
    dist[src] = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        bool updated = false;
        for (const auto &e : edges)
        {
            if (dist[e.from] != INF && dist[e.from] + e.weight < dist[e.to])
            {
                dist[e.to] = dist[e.from] + e.weight;
                updated = true;
            }
        }
        if (!updated)
            break;
    }

    for (const auto &e : edges)
    {
        if (dist[e.from] != INF && dist[e.from] + e.weight < dist[e.to])
            return false;
    }
    return true;
}

void run(const std::string &label, int n, const std::vector<Edge> &edges)
{
    std::vector<int> dist;
    std::cout << label << ": ";
    if (!bellman_ford(n, edges, 0, dist))
    {
        std::cout << "negative cycle detected\n";
        return;
    }
    for (int v = 0; v < n; ++v)
    {
        std::cout << v << "=" << dist[v] << " ";
    }
    std::cout << "\n";
}

int main()
{
    std::vector<Edge> edges = {
        {0, 1, 6}, {0, 2, 7}, {1, 2, 8}, {1, 3, 5}, {1, 4, -4},
        {2, 3, -3}, {2, 4, 9}, {3, 1, -2}, {4, 0, 2}, {4, 3, 7}};
    run("Negative edges", 5, edges);

    std::vector<Edge> cyclic = {{0, 1, 1}, {1, 2, -1}, {2, 1, -1}};
    run("Negative cycle", 3, cyclic);

    return 0;
}
