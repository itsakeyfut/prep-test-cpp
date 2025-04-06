#include <iostream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

bool judge(char p1, char p2)
{
    if (p1 == p2)
        return false;
    if ((p1 == 'R' && p2 == 'S') ||
        (p1 == 'S' && p2 == 'P') ||
        (p1 == 'P' && p2 == 'R'))
        return true;
    else
        return false;
}

int main()
{
    unsigned int total{};
    unsigned int N;
    cin >> N;
    cin.ignore();

    vector<pair<char, char>> data;
    data.reserve(N);

    for (size_t i{0}; i < N; ++i)
    {
        char a, b;
        cin >> a >> b;
        data.emplace_back(a, b);
    }

    for (const auto &[p1, p2] : data)
        if (judge(p1, p2))
            total++;

    cout << total << endl;
}