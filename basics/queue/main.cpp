#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class Queue
{
private:
    std::unique_ptr<T[]> data;
    std::size_t capacity;
    std::size_t head;
    std::size_t tail;
    std::size_t count;

public:
    explicit Queue(std::size_t size)
        : data(std::make_unique<T[]>(size)),
          capacity(size),
          head(0),
          tail(0),
          count(0) {}

    void enqueue(const T &value)
    {
        if (count == capacity)
            throw std::overflow_error("Queue overflow");

        data[tail] = value;
        tail = (tail + 1) % capacity;
        ++count;
    }

    void dequeue()
    {
        if (empty())
            throw std::underflow_error("Queue underflow");

        head = (head + 1) % capacity;
        --count;
    }

    T &front()
    {
        if (empty())
            throw std::underflow_error("Queue is empty");

        return data[head];
    }

    const T &front() const
    {
        if (empty())
            throw std::underflow_error("Queue is empty");

        return data[head];
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
    Queue<int> queue(5);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    std::cout << "Front: " << queue.front() << std::endl;
    queue.dequeue();

    std::cout << "Front after dequeue: " << queue.front() << std::endl;

    while (!queue.empty())
    {
        std::cout << "Dequeueing: " << queue.front() << std::endl;
        queue.dequeue();
    }

    Queue<std::string> stringQueue(3);
    stringQueue.enqueue("one");
    stringQueue.enqueue("two");

    std::cout << "Front: " << stringQueue.front() << "\n";
    stringQueue.dequeue();

    stringQueue.enqueue("three");

    while (!stringQueue.empty())
    {
        std::cout << "Dequeueing: " << stringQueue.front() << "\n";
        stringQueue.dequeue();
    }

    return 0;
}