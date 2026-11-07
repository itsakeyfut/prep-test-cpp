class Solution
{
public:
    bool isPalindrome(int x)
    {
        // 負の数と、末尾が0の数（0そのものは除く）は回文にならない
        if (x < 0 || (x % 10 == 0 && x != 0))
            return false;

        int reversedHalf = 0;
        while (x > reversedHalf)
        {
            reversedHalf = reversedHalf * 10 + x % 10;
            x /= 10;
        }

        // 桁数が偶数なら x == reversedHalf、奇数なら真ん中の桁を捨てて比較する
        return x == reversedHalf || x == reversedHalf / 10;
    }
};