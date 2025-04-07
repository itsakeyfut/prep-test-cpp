#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
    vector<int> nums;
    int num;

    while (cin >> num)
        nums.push_back(num);

    for (size_t i{0}; i < nums.size(); ++i)
    {
        cout << nums.at(i);
        if (i != nums.size() - 1)
            cout << " | ";
    }
    cout << endl;
    return 0;
}