#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

struct Edge
{
    int u;
    int v;
    int weight;
};

struct UnionFind
{
    std::vector<int> parent;
    std::vector<int> rank;

    explicit UnionFind(int n) : parent(n), rank(n, 0)
    {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (rank[a] < rank[b])
            std::swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            ++rank[a];
        return true;
    }
};

int kruskal(int n, std::vector<Edge> edges)
{
    std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
              { return a.weight < b.weight; });
    UnionFind uf(n);
    int total = 0;
    for (const auto &e : edges)
    {
        if (uf.unite(e.u, e.v))
        {
            std::cout << "  " << e.u << "-" << e.v << " (" << e.weight << ")\n";
            total += e.weight;
        }
    }
    return total;
}

int prim(int n, const std::vector<Edge> &edges)
{
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (const auto &e : edges)
    {
        adj[e.u].push_back({e.v, e.weight});
        adj[e.v].push_back({e.u, e.weight});
    }

    std::vector<bool> in_tree(n, false);
    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<>> pq;
    pq.push({0, 0, -1});
    int total = 0;
    while (!pq.empty())
    {
        auto [w, v, from] = pq.top();
        pq.pop();
        if (in_tree[v])
            continue;
        in_tree[v] = true;
        if (from != -1)
        {
            std::cout << "  " << from << "-" << v << " (" << w << ")\n";
            total += w;
        }
        for (auto [to, weight] : adj[v])
        {
            if (!in_tree[to])
                pq.push({weight, to, v});
        }
    }
    return total;
}

int main()
{
    std::vector<Edge> edges = {
        {0, 1, 2}, {0, 3, 6}, {1, 2, 3}, {1, 3, 8}, {1, 4, 5}, {2, 4, 7}, {3, 4, 9}};

    std::cout << "Kruskal:\n";
    int kruskal_total = kruskal(5, edges);
    std::cout << "Total: " << kruskal_total << "\n";

    std::cout << "Prim:\n";
    int prim_total = prim(5, edges);
    std::cout << "Total: " << prim_total << "\n";

    return 0;
}
