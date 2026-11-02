#include <algorithm>
#include <iostream>
#include <vector>

int binary_search(const std::vector<int> &a, int target)
{
    int lo = 0;
    int hi = static_cast<int>(a.size()) - 1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target)
            return mid;
        if (a[mid] < target)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return -1;
}

int lower_bound(const std::vector<int> &a, int target)
{
    int lo = 0;
    int hi = static_cast<int>(a.size());
    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] < target)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

int upper_bound(const std::vector<int> &a, int target)
{
    int lo = 0;
    int hi = static_cast<int>(a.size());
    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] <= target)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

bool can_ship(const std::vector<int> &weights, int days, int capacity)
{
    int used = 1;
    int load = 0;
    for (int w : weights)
    {
        if (load + w > capacity)
        {
            ++used;
            load = 0;
        }
        load += w;
    }
    return used <= days;
}

int ship_within_days(const std::vector<int> &weights, int days)
{
    int lo = 0;
    int hi = 0;
    for (int w : weights)
    {
        lo = std::max(lo, w);
        hi += w;
    }
    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (can_ship(weights, days, mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

int main()
{
    std::vector<int> a = {1, 3, 3, 3, 5, 7, 9};

    std::cout << "binary_search(5): " << binary_search(a, 5) << "\n";
    std::cout << "binary_search(4): " << binary_search(a, 4) << "\n";

    std::cout << "lower_bound(3): " << lower_bound(a, 3) << "\n";
    std::cout << "upper_bound(3): " << upper_bound(a, 3) << "\n";
    std::cout << "count of 3: " << upper_bound(a, 3) - lower_bound(a, 3) << "\n";
    std::cout << "lower_bound(10): " << lower_bound(a, 10) << "\n";

    std::vector<int> weights = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "ship_within_days(5): " << ship_within_days(weights, 5) << "\n";

    return 0;
}
