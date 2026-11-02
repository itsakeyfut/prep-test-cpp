#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int max_non_overlapping(std::vector<std::pair<int, int>> intervals)
{
    std::sort(intervals.begin(), intervals.end(), [](const auto &a, const auto &b)
              { return a.second < b.second; });
    int count = 0;
    int last_end = -1000000000;
    for (const auto &[start, end] : intervals)
    {
        if (start >= last_end)
        {
            ++count;
            last_end = end;
        }
    }
    return count;
}

bool can_jump(const std::vector<int> &nums)
{
    int reach = 0;
    for (int i = 0; i < static_cast<int>(nums.size()); ++i)
    {
        if (i > reach)
            return false;
        reach = std::max(reach, i + nums[i]);
    }
    return true;
}

int greedy_coin_change(std::vector<int> coins, int amount)
{
    std::sort(coins.rbegin(), coins.rend());
    int count = 0;
    for (int c : coins)
    {
        count += amount / c;
        amount %= c;
    }
    return amount == 0 ? count : -1;
}

int dp_coin_change(const std::vector<int> &coins, int amount)
{
    const int INF = 1000000000;
    std::vector<int> dp(amount + 1, INF);
    dp[0] = 0;
    for (int x = 1; x <= amount; ++x)
        for (int c : coins)
            if (c <= x && dp[x - c] != INF)
                dp[x] = std::min(dp[x], dp[x - c] + 1);
    return dp[amount] == INF ? -1 : dp[amount];
}

int main()
{
    std::vector<std::pair<int, int>> intervals = {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {8, 11}};
    std::cout << "max_non_overlapping: " << max_non_overlapping(intervals) << "\n";

    std::cout << "can_jump({2,3,1,1,4}): " << (can_jump({2, 3, 1, 1, 4}) ? "true" : "false") << "\n";
    std::cout << "can_jump({3,2,1,0,4}): " << (can_jump({3, 2, 1, 0, 4}) ? "true" : "false") << "\n";

    std::vector<int> yen = {1, 5, 10, 50, 100, 500};
    std::cout << "greedy {1,5,10,50,100,500} 678: " << greedy_coin_change(yen, 678) << "\n";

    std::vector<int> bad = {1, 3, 4};
    std::cout << "greedy {1,3,4} 6: " << greedy_coin_change(bad, 6) << "\n";
    std::cout << "dp     {1,3,4} 6: " << dp_coin_change(bad, 6) << "\n";

    return 0;
}
