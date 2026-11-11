#include <unordered_map>
#include <string>

class Solution {
public:
    int romanToInt(std::string s) {
        std::unordered_map<char, int> glyph = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000},
        };

        int convertedNumber = 0;
        for (int i{0}; i < s.size(); ++i) {
            int curr = glyph[s[i]];
            int next = (i + 1 < s.size()) ? glyph[s[i + 1]] : 0;

            if (curr < next) {
                convertedNumber -= curr;
            } else {
                convertedNumber += curr;
            }
        }

        return convertedNumber;
    }
};
