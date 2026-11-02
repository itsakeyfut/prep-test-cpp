#include <iostream>
#include <vector>

class SegmentTree
{
private:
    int n;
    std::vector<int> tree;

public:
    explicit SegmentTree(const std::vector<int> &nums)
        : n(static_cast<int>(nums.size())), tree(2 * n, 0)
    {
        for (int i = 0; i < n; ++i)
            tree[n + i] = nums[i];
        for (int i = n - 1; i > 0; --i)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    void update(int index, int value)
    {
        int pos = index + n;
        tree[pos] = value;
        while (pos > 1)
        {
            pos /= 2;
            tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
        }
    }

    int query(int left, int right) const
    {
        int sum = 0;
        int l = left + n;
        int r = right + n + 1;
        while (l < r)
        {
            if (l & 1)
                sum += tree[l++];
            if (r & 1)
                sum += tree[--r];
            l /= 2;
            r /= 2;
        }
        return sum;
    }
};

int main()
{
    std::vector<int> nums{1, 3, 5, 7, 9, 11};
    SegmentTree st(nums);

    std::cout << "sum[0, 5] = " << st.query(0, 5) << "\n";
    std::cout << "sum[1, 3] = " << st.query(1, 3) << "\n";
    std::cout << "sum[2, 2] = " << st.query(2, 2) << "\n";

    st.update(1, 10);
    std::cout << "update(1, 10)\n";

    std::cout << "sum[0, 5] = " << st.query(0, 5) << "\n";
    std::cout << "sum[1, 3] = " << st.query(1, 3) << "\n";

    return 0;
}
