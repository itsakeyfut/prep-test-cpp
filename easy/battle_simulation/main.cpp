#include <iostream>
#include <vector>
using namespace std;

void battle(int &your_level, int opponent_level)
{
    if (your_level == opponent_level)
        return;

    your_level += (your_level > opponent_level) ? opponent_level / 2 : -your_level / 2;
}

int main(void)
{
    unsigned int num_of_battles{};
    int your_level{};

    cin >> num_of_battles >> your_level;

    vector<int> data(num_of_battles);
    for (int &opponent_level : data)
        cin >> opponent_level;

    for (const int &opponent_level : data)
        battle(your_level, opponent_level);

    cout << your_level << endl;
    return 0;
}