#include <iostream>
#include <vector>

bool has_bit(int n, int i)
{
    return (n >> i) & 1;
}

int set_bit(int n, int i)
{
    return n | (1 << i);
}

int clear_bit(int n, int i)
{
    return n & ~(1 << i);
}

int toggle_bit(int n, int i)
{
    return n ^ (1 << i);
}

int popcount(unsigned int n)
{
    int count = 0;
    while (n)
    {
        n &= n - 1;
        ++count;
    }
    return count;
}

int single_number(const std::vector<int> &a)
{
    int result = 0;
    for (int x : a)
        result ^= x;
    return result;
}

bool is_power_of_two(int n)
{
    return n > 0 && (n & (n - 1)) == 0;
}

void enumerate_subsets(const std::vector<int> &a)
{
    int n = static_cast<int>(a.size());
    for (int mask = 0; mask < (1 << n); ++mask)
    {
        int sum = 0;
        std::cout << "{ ";
        for (int i = 0; i < n; ++i)
        {
            if (mask & (1 << i))
            {
                std::cout << a[i] << " ";
                sum += a[i];
            }
        }
        std::cout << "} sum=" << sum << "\n";
    }
}

int main()
{
    int n = 10;
    std::cout << "has_bit(10, 1): " << has_bit(n, 1) << "\n";
    std::cout << "has_bit(10, 2): " << has_bit(n, 2) << "\n";
    std::cout << "set_bit(10, 0): " << set_bit(n, 0) << "\n";
    std::cout << "clear_bit(10, 3): " << clear_bit(n, 3) << "\n";
    std::cout << "toggle_bit(10, 2): " << toggle_bit(n, 2) << "\n";

    std::cout << "popcount(13): " << popcount(13) << "\n";
    std::cout << "single_number: " << single_number({4, 1, 2, 1, 2}) << "\n";
    std::cout << "is_power_of_two(16): " << (is_power_of_two(16) ? "true" : "false") << "\n";
    std::cout << "is_power_of_two(18): " << (is_power_of_two(18) ? "true" : "false") << "\n";

    enumerate_subsets({1, 2, 4});

    return 0;
}
