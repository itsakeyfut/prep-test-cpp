#include <iostream>
#include <vector>

class FenwickTree
{
private:
    std::vector<int> tree;

public:
    explicit FenwickTree(int n) : tree(n + 1, 0) {}

    void add(int i, int delta)
    {
        for (; i < static_cast<int>(tree.size()); i += i & -i)
            tree[i] += delta;
    }

    int prefix_sum(int i) const
    {
        int sum = 0;
        for (; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }

    int range_sum(int left, int right) const
    {
        return prefix_sum(right) - prefix_sum(left - 1);
    }
};

int main()
{
    std::vector<int> nums{1, 3, 5, 7, 9, 11};
    FenwickTree ft(static_cast<int>(nums.size()));

    for (int i = 0; i < static_cast<int>(nums.size()); ++i)
        ft.add(i + 1, nums[i]);

    std::cout << "prefix_sum(3) = " << ft.prefix_sum(3) << "\n";
    std::cout << "range_sum(2, 4) = " << ft.range_sum(2, 4) << "\n";
    std::cout << "range_sum(1, 6) = " << ft.range_sum(1, 6) << "\n";

    ft.add(2, 7);
    std::cout << "add(2, 7)\n";

    std::cout << "range_sum(2, 4) = " << ft.range_sum(2, 4) << "\n";
    std::cout << "range_sum(1, 6) = " << ft.range_sum(1, 6) << "\n";

    return 0;
}
