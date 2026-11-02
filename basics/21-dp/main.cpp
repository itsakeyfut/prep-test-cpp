#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

long long fib_memo(int n, std::vector<long long> &memo)
{
    if (n <= 1)
        return n;
    if (memo[n] != -1)
        return memo[n];
    return memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);
}

long long fib_table(int n)
{
    if (n <= 1)
        return n;
    std::vector<long long> dp(n + 1, 0);
    dp[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

int knapsack(const std::vector<int> &weights, const std::vector<int> &values, int capacity)
{
    std::vector<int> dp(capacity + 1, 0);
    for (std::size_t i = 0; i < weights.size(); ++i)
    {
        for (int w = capacity; w >= weights[i]; --w)
        {
            dp[w] = std::max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }
    return dp[capacity];
}

int lcs(const std::string &a, const std::string &b)
{
    std::size_t n = a.size();
    std::size_t m = b.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    for (std::size_t i = 1; i <= n; ++i)
    {
        for (std::size_t j = 1; j <= m; ++j)
        {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
}

int lis_n2(const std::vector<int> &nums)
{
    if (nums.empty())
        return 0;
    std::vector<int> dp(nums.size(), 1);
    for (std::size_t i = 1; i < nums.size(); ++i)
    {
        for (std::size_t j = 0; j < i; ++j)
        {
            if (nums[j] < nums[i])
                dp[i] = std::max(dp[i], dp[j] + 1);
        }
    }
    return *std::max_element(dp.begin(), dp.end());
}

int lis_nlogn(const std::vector<int> &nums)
{
    std::vector<int> tails;
    for (int x : nums)
    {
        auto it = std::lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end())
            tails.push_back(x);
        else
            *it = x;
    }
    return static_cast<int>(tails.size());
}

int coin_change(const std::vector<int> &coins, int amount)
{
    const int INF = amount + 1;
    std::vector<int> dp(amount + 1, INF);
    dp[0] = 0;
    for (int a = 1; a <= amount; ++a)
    {
        for (int c : coins)
        {
            if (c <= a)
                dp[a] = std::min(dp[a], dp[a - c] + 1);
        }
    }
    return dp[amount] == INF ? -1 : dp[amount];
}

int main()
{
    int n = 50;
    std::vector<long long> memo(n + 1, -1);
    std::cout << "fib_memo(" << n << "): " << fib_memo(n, memo) << "\n";
    std::cout << "fib_table(" << n << "): " << fib_table(n) << "\n";

    std::vector<int> weights = {1, 3, 4, 5};
    std::vector<int> values = {1, 4, 5, 7};
    std::cout << "knapsack(cap=7): " << knapsack(weights, values, 7) << "\n";

    std::cout << "lcs(\"abcde\", \"ace\"): " << lcs("abcde", "ace") << "\n";

    std::vector<int> seq = {10, 9, 2, 5, 3, 7, 101, 18};
    std::cout << "lis_n2: " << lis_n2(seq) << "\n";
    std::cout << "lis_nlogn: " << lis_nlogn(seq) << "\n";

    std::cout << "coin_change({1,2,5}, 11): " << coin_change({1, 2, 5}, 11) << "\n";
    std::cout << "coin_change({2}, 3): " << coin_change({2}, 3) << "\n";

    return 0;
}
