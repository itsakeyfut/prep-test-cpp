#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(void)
{
    unsigned int total{10};
    vector<string> words;
    words.reserve(total);
    for (size_t i{0}; i < total; ++i)
    {
        string word;
        cin >> word;
        words.push_back(word);
    }

    for (auto it = words.begin(); it != words.end(); ++it)
    {
        cout << *it;
        if (next(it) != words.end())
            cout << " ";
        else
            cout << endl;
    }

    return 0;
}