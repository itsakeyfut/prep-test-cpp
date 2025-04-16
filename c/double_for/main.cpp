#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
    int n, m;
    cin >> n >> m;

    vector<int> v(n), w(m);

    for (int i{0}; i < n; ++i)
        cin >> v[i];

    for (int i{0}; i < m; ++i)
        cin >> w[i];

    int idx{0};
    for (int i{0}; i < m; ++i)
    {
        for (int j{0}; j < w[i]; ++j)
        {
            cout << v[idx++];
            if (j + 1 != w[i])
                cout << " ";
        }
        cout << endl;
    }
    return 0;
}