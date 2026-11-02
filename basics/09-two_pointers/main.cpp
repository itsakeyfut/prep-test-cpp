#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::pair<int, int> two_sum_sorted(const std::vector<int> &a, int target)
{
    int left = 0;
    int right = static_cast<int>(a.size()) - 1;
    while (left < right)
    {
        int sum = a[left] + a[right];
        if (sum == target)
            return {left, right};
        if (sum < target)
            ++left;
        else
            --right;
    }
    return {-1, -1};
}

int remove_duplicates(std::vector<int> &a)
{
    if (a.empty())
        return 0;
    int slow = 0;
    for (int fast = 1; fast < static_cast<int>(a.size()); ++fast)
    {
        if (a[fast] != a[slow])
        {
            ++slow;
            a[slow] = a[fast];
        }
    }
    return slow + 1;
}

bool is_palindrome(const std::string &s)
{
    int left = 0;
    int right = static_cast<int>(s.size()) - 1;
    while (left < right)
    {
        if (s[left] != s[right])
            return false;
        ++left;
        --right;
    }
    return true;
}

int max_area(const std::vector<int> &height)
{
    int left = 0;
    int right = static_cast<int>(height.size()) - 1;
    int best = 0;
    while (left < right)
    {
        int h = std::min(height[left], height[right]);
        best = std::max(best, h * (right - left));
        if (height[left] < height[right])
            ++left;
        else
            --right;
    }
    return best;
}

int main()
{
    std::vector<int> sorted = {1, 2, 4, 7, 11, 15};
    auto [i, j] = two_sum_sorted(sorted, 15);
    std::cout << "two_sum_sorted(15): [" << i << ", " << j << "]\n";

    std::vector<int> dup = {1, 1, 2, 3, 3, 3, 4};
    int len = remove_duplicates(dup);
    std::cout << "remove_duplicates: ";
    for (int k = 0; k < len; ++k)
        std::cout << dup[k] << " ";
    std::cout << "(length " << len << ")\n";

    std::cout << "is_palindrome(racecar): " << (is_palindrome("racecar") ? "true" : "false") << "\n";
    std::cout << "is_palindrome(hello): " << (is_palindrome("hello") ? "true" : "false") << "\n";

    std::vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    std::cout << "max_area: " << max_area(height) << "\n";

    return 0;
}
