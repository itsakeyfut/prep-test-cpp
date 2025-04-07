#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main(void)
{
    string s;
    cin >> s;
    int remainder = s.size() % 3;
    for (size_t i{0}; i < s.size(); i++)
    {
        if (i % 3 == remainder && i != 0)
        {
            cout << ",";
        }
        cout << s[i];
    }
    cout << endl;
    return 0;
}