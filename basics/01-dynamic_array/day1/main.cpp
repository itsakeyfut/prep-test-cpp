#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

template <typename T>
class DynamicArray
{
private:
    std::unique_ptr<T[]> data;
    std::size_t length;
    std::size_t cap;

    void reserve(std::size_t new_cap)
    {
        auto new_data = std::make_unique<T[]>(new_cap);
        for (std::size_t i = 0; i < length; ++i)
            new_data[i] = std::move(data[i]); // move はコピーとは異なるけど、なぜコピーよりも効率的なのか？
        data = std::move(new_data);
        cap = new_cap;
    }

public:
    DynamicArray() : data(nullptr), length(0), cap(0) {}

    void push_back(const T &value)
    {
        if (length == cap)
            reserve(cap == 0 ? 1 : cap * 2);
        data[length++] = value;
    }

    void pop_back()
    {
        if (empty())
            throw std::underflow_error("Array is empty");
        --length;
    }

    T &operator[](std::size_t index) // operator[] って何だっけ？
    {
        return data[index];
    }

    const T &operator[](std::size_t index) const
    {
        return data[index];
    }

    T &at(std::size_t index)
    {
        if (index >= length)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    std::size_t size() const
    {
        return length;
    }

    std::size_t capacity() const
    {
        return cap;
    }

    bool empty() const
    {
        return length == 0;
    }
};

int main()
{
    DynamicArray<int> arr;

    for (int i = 1; i <= 9; ++i)
    {
        arr.push_back(i * 10);
        std::cout << "push_back(" << i * 10 << ") size=" << arr.size()
                  << " capacity=" << arr.capacity() << "\n";
    }

    arr[0] = 5;
    std::cout << "Elements: ";
    for (std::size_t i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";

    arr.pop_back();
    arr.pop_back();
    std::cout << "After 2x pop_back: size=" << arr.size()
              << " capacity=" << arr.capacity() << "\n";

    try
    {
        arr.at(100);
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "at(100): " << e.what() << "\n";
    }

    DynamicArray<std::string> words;
    words.push_back("hello");
    words.push_back("world");
    std::cout << "Words: " << words[0] << " " << words[1] << "\n";

    return 0;
}