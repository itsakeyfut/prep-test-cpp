#include <iostream>
#include <string>
#include <vector>

std::vector<int> prefix_function(const std::string &p)
{
    std::vector<int> pi(p.size(), 0);
    for (std::size_t i = 1; i < p.size(); ++i)
    {
        int k = pi[i - 1];
        while (k > 0 && p[i] != p[k])
            k = pi[k - 1];
        if (p[i] == p[k])
            ++k;
        pi[i] = k;
    }
    return pi;
}

std::vector<int> kmp_search(const std::string &text, const std::string &p)
{
    std::vector<int> result;
    if (p.empty())
        return result;
    std::vector<int> pi = prefix_function(p);
    int k = 0;
    for (std::size_t i = 0; i < text.size(); ++i)
    {
        while (k > 0 && text[i] != p[k])
            k = pi[k - 1];
        if (text[i] == p[k])
            ++k;
        if (k == static_cast<int>(p.size()))
        {
            result.push_back(static_cast<int>(i) - k + 1);
            k = pi[k - 1];
        }
    }
    return result;
}

std::vector<int> rabin_karp(const std::string &text, const std::string &p)
{
    std::vector<int> result;
    std::size_t n = text.size();
    std::size_t m = p.size();
    if (m == 0 || m > n)
        return result;

    const long long BASE = 256;
    const long long MOD = 1000000007;
    long long high = 1;
    for (std::size_t i = 1; i < m; ++i)
        high = high * BASE % MOD;

    long long hp = 0;
    long long ht = 0;
    for (std::size_t i = 0; i < m; ++i)
    {
        hp = (hp * BASE + static_cast<unsigned char>(p[i])) % MOD;
        ht = (ht * BASE + static_cast<unsigned char>(text[i])) % MOD;
    }

    for (std::size_t i = 0; i + m <= n; ++i)
    {
        if (hp == ht && text.compare(i, m, p) == 0)
            result.push_back(static_cast<int>(i));
        if (i + m < n)
        {
            ht = (ht - static_cast<unsigned char>(text[i]) * high % MOD + MOD) % MOD;
            ht = (ht * BASE + static_cast<unsigned char>(text[i + m])) % MOD;
        }
    }
    return result;
}

void print(const std::string &label, const std::vector<int> &v)
{
    std::cout << label << ": ";
    for (int x : v)
        std::cout << x << " ";
    std::cout << "\n";
}

int main()
{
    std::string pattern = "ababaca";
    print("prefix_function(\"" + pattern + "\")", prefix_function(pattern));

    std::string text = "abababcabababab";
    std::string p = "abab";
    print("kmp_search", kmp_search(text, p));
    print("rabin_karp", rabin_karp(text, p));

    print("kmp_search(\"aaaaa\", \"aa\")", kmp_search("aaaaa", "aa"));
    print("rabin_karp(\"aaaaa\", \"aa\")", rabin_karp("aaaaa", "aa"));

    return 0;
}
