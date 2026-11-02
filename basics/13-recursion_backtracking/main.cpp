#include <iostream>
#include <string>
#include <vector>

void print(const std::vector<int> &v)
{
    std::cout << "[";
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << (i + 1 < v.size() ? "," : "");
    }
    std::cout << "] ";
}

void permute(const std::vector<int> &nums, std::vector<bool> &used, std::vector<int> &path, std::vector<std::vector<int>> &result)
{
    if (path.size() == nums.size())
    {
        result.push_back(path);
        return;
    }
    for (std::size_t i = 0; i < nums.size(); ++i)
    {
        if (used[i])
            continue;
        used[i] = true;
        path.push_back(nums[i]);
        permute(nums, used, path, result);
        path.pop_back();
        used[i] = false;
    }
}

void combine(int start, int n, int k, std::vector<int> &path, std::vector<std::vector<int>> &result)
{
    if (static_cast<int>(path.size()) == k)
    {
        result.push_back(path);
        return;
    }
    for (int i = start; i <= n; ++i)
    {
        path.push_back(i);
        combine(i + 1, n, k, path, result);
        path.pop_back();
    }
}

void subsets(const std::vector<int> &nums, std::size_t start, std::vector<int> &path, std::vector<std::vector<int>> &result)
{
    result.push_back(path);
    for (std::size_t i = start; i < nums.size(); ++i)
    {
        path.push_back(nums[i]);
        subsets(nums, i + 1, path, result);
        path.pop_back();
    }
}

bool is_safe(const std::vector<std::string> &board, int row, int col)
{
    int n = static_cast<int>(board.size());
    for (int r = 0; r < row; ++r)
    {
        if (board[r][col] == 'Q')
            return false;
        int d = row - r;
        if (col - d >= 0 && board[r][col - d] == 'Q')
            return false;
        if (col + d < n && board[r][col + d] == 'Q')
            return false;
    }
    return true;
}

void solve_queens(int row, std::vector<std::string> &board, std::vector<std::vector<std::string>> &solutions)
{
    int n = static_cast<int>(board.size());
    if (row == n)
    {
        solutions.push_back(board);
        return;
    }
    for (int col = 0; col < n; ++col)
    {
        if (!is_safe(board, row, col))
            continue;
        board[row][col] = 'Q';
        solve_queens(row + 1, board, solutions);
        board[row][col] = '.';
    }
}

int main()
{
    std::vector<int> nums = {1, 2, 3};

    std::vector<std::vector<int>> perms;
    std::vector<bool> used(nums.size(), false);
    std::vector<int> path;
    permute(nums, used, path, perms);
    std::cout << "Permutations (" << perms.size() << "): ";
    for (const auto &p : perms)
        print(p);
    std::cout << "\n";

    std::vector<std::vector<int>> combs;
    combine(1, 4, 2, path, combs);
    std::cout << "Combinations C(4,2) (" << combs.size() << "): ";
    for (const auto &c : combs)
        print(c);
    std::cout << "\n";

    std::vector<std::vector<int>> subs;
    subsets(nums, 0, path, subs);
    std::cout << "Subsets (" << subs.size() << "): ";
    for (const auto &s : subs)
        print(s);
    std::cout << "\n";

    int n = 4;
    std::vector<std::string> board(n, std::string(n, '.'));
    std::vector<std::vector<std::string>> solutions;
    solve_queens(0, board, solutions);
    std::cout << "N-Queens n=" << n << ": " << solutions.size() << " solutions\n";
    for (const auto &sol : solutions)
    {
        for (const auto &row : sol)
            std::cout << row << "\n";
        std::cout << "\n";
    }

    return 0;
}
