#include <iostream>
#include <vector>

template <typename T>
class Stack
{
private:
    std::vector<T> data;

public:
    void push(const T &value)
    {
        data.push_back(value);
    }

    void pop()
    {
        if (!data.empty())
        {
            data.pop_back();
        }
    }

    T &top()
    {
        return data.back();
    }

    bool empty() const
    {
        return data.empty();
    }

    std::size_t size() const
    {
        return data.size();
    }
};

int main()
{
    Stack<int> s;
    s.push(100);
    s.push(200);

    while (!s.empty())
    {
        std::cout << "Top: " << s.top() << "\n";
        s.pop();
    }

    return 0;
}
