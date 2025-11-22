#include <vector>
#include <string>

class Solution
{
public:
    int convertCharToNum(char c)
    {
        switch (c)
        {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return 0;
        }
    }

    int romanToInt(std::string s)
    {
        int result{0};
        for (size_t i{0}; i < s.length(); i++)
        {
            if (i + 1 < s.length() && convertCharToNum(s[i]) < convertCharToNum(s[i + 1]))
                result -= convertCharToNum(s[i]);
            else
                result += convertCharToNum(s[i]);
        }
        return result;
    }
};