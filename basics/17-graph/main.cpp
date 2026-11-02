#include <iostream>
#include <utility>
#include <vector>

class Graph
{
private:
    int n;
    bool directed;
    std::vector<std::vector<int>> adj_list;
    std::vector<std::vector<int>> adj_matrix;

public:
    Graph(int size, bool is_directed)
        : n(size), directed(is_directed), adj_list(size), adj_matrix(size, std::vector<int>(size, 0)) {}

    void add_edge(int u, int v)
    {
        adj_list[u].push_back(v);
        adj_matrix[u][v] = 1;
        if (!directed)
        {
            adj_list[v].push_back(u);
            adj_matrix[v][u] = 1;
        }
    }

    bool has_edge(int u, int v) const
    {
        return adj_matrix[u][v] == 1;
    }

    const std::vector<int> &neighbors(int u) const
    {
        return adj_list[u];
    }

    void print_list() const
    {
        for (int u = 0; u < n; ++u)
        {
            std::cout << u << ":";
            for (int v : adj_list[u])
            {
                std::cout << " " << v;
            }
            std::cout << "\n";
        }
    }

    void print_matrix() const
    {
        for (int u = 0; u < n; ++u)
        {
            for (int v = 0; v < n; ++v)
            {
                std::cout << adj_matrix[u][v] << " ";
            }
            std::cout << "\n";
        }
    }
};

int main()
{
    std::vector<std::pair<int, int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}};

    Graph undirected(5, false);
    Graph directed(5, true);
    for (const auto &[u, v] : edges)
    {
        undirected.add_edge(u, v);
        directed.add_edge(u, v);
    }

    std::cout << "Undirected adjacency list:\n";
    undirected.print_list();
    std::cout << "Undirected adjacency matrix:\n";
    undirected.print_matrix();

    std::cout << "Directed adjacency list:\n";
    directed.print_list();
    std::cout << "Directed adjacency matrix:\n";
    directed.print_matrix();

    std::cout << "Neighbors of 3 (undirected):";
    for (int v : undirected.neighbors(3))
    {
        std::cout << " " << v;
    }
    std::cout << "\n";

    std::cout << "Edge 3->1 (undirected): " << (undirected.has_edge(3, 1) ? "Yes" : "No") << "\n";
    std::cout << "Edge 3->1 (directed): " << (directed.has_edge(3, 1) ? "Yes" : "No") << "\n";

    return 0;
}
