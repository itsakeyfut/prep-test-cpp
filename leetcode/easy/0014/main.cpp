#include <cstddef>
#include <string>
#include <vector>

class Solution {
public:
    // 水平スキャン
    std::string longestCommonPrefixHorizontal(const std::vector<std::string>& strs) {
        if (strs.empty()) return "";

        std::string prefix = strs[0];
        for (const std::string& str : strs) {
            while (!str.starts_with(prefix)) {
                prefix.pop_back();
                if (prefix.empty()) return "";
            }
        }
        return prefix;
    }

    // 垂直スキャン
    // こちらの方が無駄がなく面接向き
    std::string longestCommonPrefixVertex(const std::vector<std::string>& strs) {
        if (strs.empty()) return "";

        const std::string& first = strs[0];
        for (std::size_t pos = 0; pos < first.size(); ++pos) {
            const char expected = first[pos];
            for (const std::string& str : strs) {
                if (pos >= str.size() || str[pos] != expected)
                    return first.substr(0, pos);
            }
        }
        return first;
    }
};