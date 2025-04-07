#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main(void)
{
    string num;
    cin >> num;

    int len = num.length();
    int cnt = 0;

    for (size_t i{0}; i <= len - 1; ++i)
    {
        cout << num.at(i);
        cnt++;

        if (cnt == 3 && i != 0)
        {
            if (i != len - 1)
                cout << ",";
            cnt = 0;
        }
    }
    cout << endl;
    return 0;
}