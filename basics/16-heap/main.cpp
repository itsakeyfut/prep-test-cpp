#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T>
class MinHeap
{
private:
    std::vector<T> data;

    void sift_up(std::size_t i)
    {
        while (i > 0)
        {
            std::size_t parent = (i - 1) / 2;
            if (data[parent] <= data[i])
                break;
            std::swap(data[parent], data[i]);
            i = parent;
        }
    }

    void sift_down(std::size_t i)
    {
        std::size_t n = data.size();
        while (true)
        {
            std::size_t smallest = i;
            std::size_t left = 2 * i + 1;
            std::size_t right = 2 * i + 2;

            if (left < n && data[left] < data[smallest])
                smallest = left;
            if (right < n && data[right] < data[smallest])
                smallest = right;
            if (smallest == i)
                break;

            std::swap(data[i], data[smallest]);
            i = smallest;
        }
    }

public:
    MinHeap() = default;

    explicit MinHeap(std::vector<T> values) : data(std::move(values))
    {
        for (std::size_t i = data.size() / 2; i-- > 0;)
            sift_down(i);
    }

    void push(const T &value)
    {
        data.push_back(value);
        sift_up(data.size() - 1);
    }

    void pop()
    {
        if (empty())
            throw std::underflow_error("Heap is empty");
        data[0] = std::move(data.back());
        data.pop_back();
        if (!empty())
            sift_down(0);
    }

    const T &top() const
    {
        if (empty())
            throw std::underflow_error("Heap is empty");
        return data[0];
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
    MinHeap<int> heap;

    for (int v : {5, 3, 8, 1, 9, 2})
    {
        heap.push(v);
        std::cout << "push(" << v << ")  top=" << heap.top() << "\n";
    }

    std::cout << "Pop order: ";
    while (!heap.empty())
    {
        std::cout << heap.top() << " ";
        heap.pop();
    }
    std::cout << "\n";

    MinHeap<int> built({7, 4, 6, 2, 10, 1, 3});
    std::cout << "Heapify then pop: ";
    while (!built.empty())
    {
        std::cout << built.top() << " ";
        built.pop();
    }
    std::cout << "\n";

    return 0;
}
