#include <stack>
#include <string>

class Solution {
public:
    bool isValid(std::string s) {
        if (s.size() % 2 != 0) return false;

        std::stack<char> expectedClosers;
        for (char ch : s) {
            switch (ch) {
                case '(': expectedClosers.push(')'); break;
                case '[': expectedClosers.push(']'); break;
                case '{': expectedClosers.push('}'); break;
                default:
                    if (expectedClosers.empty() || expectedClosers.top() != ch)
                        return false;
                    expectedClosers.pop();
            }
        }
        return expectedClosers.empty();
    }
};
