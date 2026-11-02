#include <algorithm>
#include <deque>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

std::vector<int> next_greater(const std::vector<int> &a)
{
    int n = static_cast<int>(a.size());
    std::vector<int> result(n, -1);
    std::stack<int> st;
    for (int i = 0; i < n; ++i)
    {
        while (!st.empty() && a[st.top()] < a[i])
        {
            result[st.top()] = a[i];
            st.pop();
        }
        st.push(i);
    }
    return result;
}

std::vector<int> daily_temperatures(const std::vector<int> &t)
{
    int n = static_cast<int>(t.size());
    std::vector<int> result(n, 0);
    std::stack<int> st;
    for (int i = 0; i < n; ++i)
    {
        while (!st.empty() && t[st.top()] < t[i])
        {
            result[st.top()] = i - st.top();
            st.pop();
        }
        st.push(i);
    }
    return result;
}

int largest_rectangle(const std::vector<int> &heights)
{
    int n = static_cast<int>(heights.size());
    std::stack<int> st;
    int best = 0;
    for (int i = 0; i <= n; ++i)
    {
        int h = (i == n) ? 0 : heights[i];
        while (!st.empty() && heights[st.top()] >= h)
        {
            int height = heights[st.top()];
            st.pop();
            int left = st.empty() ? -1 : st.top();
            best = std::max(best, height * (i - left - 1));
        }
        st.push(i);
    }
    return best;
}

std::vector<int> sliding_window_max(const std::vector<int> &a, int k)
{
    std::deque<int> dq;
    std::vector<int> result;
    for (int i = 0; i < static_cast<int>(a.size()); ++i)
    {
        if (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();
        while (!dq.empty() && a[dq.back()] <= a[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1)
            result.push_back(a[dq.front()]);
    }
    return result;
}

void print(const std::string &label, const std::vector<int> &v)
{
    std::cout << label << ": ";
    for (int x : v)
        std::cout << x << " ";
    std::cout << "\n";
}

int main()
{
    print("next_greater", next_greater({2, 1, 2, 4, 3}));
    print("daily_temperatures", daily_temperatures({73, 74, 75, 71, 69, 72, 76, 73}));
    std::cout << "largest_rectangle: " << largest_rectangle({2, 1, 5, 6, 2, 3}) << "\n";
    print("sliding_window_max(k=3)", sliding_window_max({1, 3, -1, -3, 5, 3, 6, 7}, 3));

    return 0;
}
