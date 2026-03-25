class Solution
{
public:
    bool isPalindrome(int x)
    {
        if (x < 0)
            return false;

        long reverse = 0;
        int x_clone = x;

        while (x > 0)
        {
            reverse = (reverse * 10) + (x % 10);
            x /= 10;
        }

        return reverse == x_clone;
    }
};