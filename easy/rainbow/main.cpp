#include <iostream>
#include <vector>
using namespace std;

int main()
{
    unsigned int days;
    cin >> days;

    vector<int> weather(days);
    for (unsigned int i = 0; i < days; ++i)
    {
        cin >> weather[i];
    }

    vector<int> rainbow_days;

    for (unsigned int i = 1; i < days; ++i)
    {
        if (weather[i - 1] == 2 && weather[i] == 0)
        {
            rainbow_days.push_back(i);
        }
    }

    if (rainbow_days.empty())
    {
        cout << -1 << endl;
        return 0;
    }

    for (size_t i = 0; i < rainbow_days.size(); ++i)
    {
        cout << rainbow_days[i];
        if (i < rainbow_days.size() - 1)
            cout << " ";
        else
            cout << endl;
    }

    return 0;
}
