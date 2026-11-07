#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class Deque
{
private:
    std::unique_ptr<T[]> data;
    std::size_t cap;
    std::size_t head;
    std::size_t count;

    void grow()
    {
        std::size_t new_cap = cap * 2;
        auto new_data = std::make_unique<T[]>(new_cap);
        for (std::size_t i = 0; i < count; ++i)
            new_data[i] = std::move(data[(head + 1) % cap]);
        data = std::move(new_data);
        cap = new_cap;
        head = 0;
    }

public:
    explicit Deque(std::size_t initial = 0)
        : data(std::make_unique<T[]>(initial)),
          cap(initial),
          head(0),
          count(0) {}

    void push_back(const T &value)
    {
        if (count == cap)
            grow();
        data[(head + count) % cap] = value;
        ++count;
    }

    void push_front(const T &value)
    {
        if (count == cap)
            grow();
        head = (head + cap - 1) % cap;
        data[head] = value;
        ++count;
    }

    void pop_front()
    {
        if (empty())
            throw std::underflow_error("Deque is empty");
        head = (head + 1) % cap;
        --count;
    }

    void pop_back()
    {
        if (empty())
            throw std::underflow_error("Deque is empty");
        --count;
    }

    T &front()
    {
        if (empty())
            throw std::underflow_error("Deque is empty");
        return data[head];
    }

    T &back()
    {
        if (empty())
            throw std::underflow_error("Deque is empty");
        return data[(head + count - 1) % cap];
    }

    bool empty() const
    {
        return count == 0;
    }

    std::size_t size() const
    {
        return count;
    }
};

int main()
{
    Deque<int> dq(2);

    dq.push_back(2);
    dq.push_back(3);
    dq.push_front(1);
    dq.push_front(0);
    dq.push_back(4);
    std::cout << "front=" << dq.front() << " back=" << dq.back()
              << " size=" << dq.size() << "\n";

    dq.pop_front();
    dq.pop_back();
    std::cout << "After pop_front/pop_back: front=" << dq.front()
              << " back=" << dq.back() << "\n";

    std::cout << "Drain from front: ";
    while (!dq.empty())
    {
        std::cout << dq.front() << " ";
        dq.pop_front();
    }
    std::cout << "\n";

    return 0;
}
