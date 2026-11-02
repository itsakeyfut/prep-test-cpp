#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int max_sum_fixed(const std::vector<int> &a, int k)
{
    int sum = 0;
    for (int i = 0; i < k; ++i)
        sum += a[i];
    int best = sum;
    for (int i = k; i < static_cast<int>(a.size()); ++i)
    {
        sum += a[i] - a[i - k];
        best = std::max(best, sum);
    }
    return best;
}

int longest_unique_substring(const std::string &s)
{
    std::vector<int> count(256, 0);
    int left = 0;
    int best = 0;
    for (int right = 0; right < static_cast<int>(s.size()); ++right)
    {
        unsigned char c = s[right];
        ++count[c];
        while (count[c] > 1)
        {
            --count[static_cast<unsigned char>(s[left])];
            ++left;
        }
        best = std::max(best, right - left + 1);
    }
    return best;
}

int min_subarray_len(const std::vector<int> &a, int target)
{
    int n = static_cast<int>(a.size());
    int left = 0;
    int sum = 0;
    int best = n + 1;
    for (int right = 0; right < n; ++right)
    {
        sum += a[right];
        while (sum >= target)
        {
            best = std::min(best, right - left + 1);
            sum -= a[left];
            ++left;
        }
    }
    return best == n + 1 ? 0 : best;
}

int main()
{
    std::vector<int> a = {2, 1, 5, 1, 3, 2};
    std::cout << "max_sum_fixed(k=3): " << max_sum_fixed(a, 3) << "\n";

    std::cout << "longest_unique_substring(abcabcbb): " << longest_unique_substring("abcabcbb") << "\n";
    std::cout << "longest_unique_substring(pwwkew): " << longest_unique_substring("pwwkew") << "\n";

    std::vector<int> b = {2, 3, 1, 2, 4, 3};
    std::cout << "min_subarray_len(7): " << min_subarray_len(b, 7) << "\n";
    std::cout << "min_subarray_len(100): " << min_subarray_len(b, 100) << "\n";

    return 0;
}
