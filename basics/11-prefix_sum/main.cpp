#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> build_prefix(const std::vector<int> &a)
{
    std::vector<int> prefix(a.size() + 1, 0);
    for (std::size_t i = 0; i < a.size(); ++i)
        prefix[i + 1] = prefix[i] + a[i];
    return prefix;
}

int range_sum(const std::vector<int> &prefix, int l, int r)
{
    return prefix[r] - prefix[l];
}

std::vector<std::vector<int>> build_prefix_2d(const std::vector<std::vector<int>> &g)
{
    std::size_t h = g.size();
    std::size_t w = g[0].size();
    std::vector<std::vector<int>> s(h + 1, std::vector<int>(w + 1, 0));
    for (std::size_t i = 0; i < h; ++i)
        for (std::size_t j = 0; j < w; ++j)
            s[i + 1][j + 1] = s[i][j + 1] + s[i + 1][j] - s[i][j] + g[i][j];
    return s;
}

int rect_sum(const std::vector<std::vector<int>> &s, int r1, int c1, int r2, int c2)
{
    return s[r2][c2] - s[r1][c2] - s[r2][c1] + s[r1][c1];
}

int subarray_sum_k(const std::vector<int> &a, int k)
{
    std::unordered_map<int, int> seen;
    seen[0] = 1;
    int sum = 0;
    int count = 0;
    for (int x : a)
    {
        sum += x;
        auto it = seen.find(sum - k);
        if (it != seen.end())
            count += it->second;
        ++seen[sum];
    }
    return count;
}

std::vector<int> imos(int n, const std::vector<std::vector<int>> &updates)
{
    std::vector<int> diff(n + 1, 0);
    for (const auto &u : updates)
    {
        diff[u[0]] += u[2];
        diff[u[1]] -= u[2];
    }
    std::vector<int> result(n, 0);
    int cur = 0;
    for (int i = 0; i < n; ++i)
    {
        cur += diff[i];
        result[i] = cur;
    }
    return result;
}

int main()
{
    std::vector<int> a = {3, 1, 4, 1, 5, 9};
    std::vector<int> prefix = build_prefix(a);
    std::cout << "range_sum[1, 4): " << range_sum(prefix, 1, 4) << "\n";
    std::cout << "range_sum[0, 6): " << range_sum(prefix, 0, 6) << "\n";

    std::vector<std::vector<int>> g = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<std::vector<int>> s = build_prefix_2d(g);
    std::cout << "rect_sum rows[1,3) cols[1,3): " << rect_sum(s, 1, 1, 3, 3) << "\n";
    std::cout << "rect_sum all: " << rect_sum(s, 0, 0, 3, 3) << "\n";

    std::vector<int> b = {1, 2, 3, -2, 2};
    std::cout << "subarray_sum_k(3): " << subarray_sum_k(b, 3) << "\n";

    std::vector<int> result = imos(6, {{0, 3, 1}, {2, 5, 2}, {1, 2, 3}});
    std::cout << "imos: ";
    for (int x : result)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
