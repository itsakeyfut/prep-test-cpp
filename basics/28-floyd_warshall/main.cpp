#include <iostream>
#include <vector>

constexpr int INF = 1'000'000'000;

void floyd_warshall(std::vector<std::vector<int>> &dist)
{
    int n = dist.size();
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

bool has_negative_cycle(const std::vector<std::vector<int>> &dist)
{
    for (int i = 0; i < static_cast<int>(dist.size()); ++i)
    {
        if (dist[i][i] < 0)
            return true;
    }
    return false;
}

int main()
{
    int n = 5;
    std::vector<std::vector<int>> dist(n, std::vector<int>(n, INF));
    for (int i = 0; i < n; ++i)
    {
        dist[i][i] = 0;
    }

    dist[0][1] = 3;
    dist[0][3] = 7;
    dist[1][0] = 8;
    dist[1][2] = 2;
    dist[2][0] = 5;
    dist[2][3] = 1;
    dist[3][0] = 2;
    dist[4][0] = 1;

    floyd_warshall(dist);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (dist[i][j] == INF)
                std::cout << "INF ";
            else
                std::cout << dist[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Negative cycle: " << (has_negative_cycle(dist) ? "Yes" : "No") << "\n";

    return 0;
}
