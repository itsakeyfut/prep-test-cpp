#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

class UnionFind
{
private:
    std::vector<int> parent;
    std::vector<int> rank;
    int components;

public:
    explicit UnionFind(int n) : parent(n), rank(n, 0), components(n)
    {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b)
    {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb)
            return false;
        if (rank[ra] < rank[rb])
            std::swap(ra, rb);
        parent[rb] = ra;
        if (rank[ra] == rank[rb])
            ++rank[ra];
        --components;
        return true;
    }

    bool same(int a, int b)
    {
        return find(a) == find(b);
    }

    int count() const
    {
        return components;
    }
};

int find_circle_num(const std::vector<std::vector<int>> &is_connected)
{
    int n = static_cast<int>(is_connected.size());
    UnionFind uf(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (is_connected[i][j])
                uf.unite(i, j);
        }
    }
    return uf.count();
}

int main()
{
    UnionFind uf(6);
    uf.unite(0, 1);
    uf.unite(1, 2);
    uf.unite(3, 4);

    std::cout << std::boolalpha;
    std::cout << "same(0, 2): " << uf.same(0, 2) << "\n";
    std::cout << "same(0, 3): " << uf.same(0, 3) << "\n";
    std::cout << "unite(2, 0): " << uf.unite(2, 0) << "\n";
    std::cout << "components: " << uf.count() << "\n";

    std::vector<std::vector<int>> is_connected = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1},
    };
    std::cout << "find_circle_num: " << find_circle_num(is_connected) << "\n";

    return 0;
}
