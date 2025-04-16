#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
int main(void)
{
    string line;
    // 1行丸ごと文字列として読みこむ
    getline(cin, line);

    // 文字列ストリームを使用
    stringstream ss(line);
    string word;
    // 空白区切りで単語を取り出す
    while (ss >> word)
        cout << word << endl;
    return 0;
}