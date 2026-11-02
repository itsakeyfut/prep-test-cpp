#include <iostream>
#include <memory>

template <typename T>
struct Node
{
    T value;
    std::unique_ptr<Node> next;

    explicit Node(const T &val) : value(val) {}
};

template <typename T>
class LinkedList
{
private:
    std::unique_ptr<Node<T>> head;
    std::size_t count = 0;

public:
    ~LinkedList()
    {
        while (head)
            head = std::move(head->next);
    }

    void push_front(const T &value)
    {
        auto node = std::make_unique<Node<T>>(value);
        node->next = std::move(head);
        head = std::move(node);
        ++count;
    }

    void push_back(const T &value)
    {
        std::unique_ptr<Node<T>> *cur = &head;
        while (*cur)
            cur = &(*cur)->next;
        *cur = std::make_unique<Node<T>>(value);
        ++count;
    }

    bool insert(std::size_t index, const T &value)
    {
        if (index > count)
            return false;

        std::unique_ptr<Node<T>> *cur = &head;
        for (std::size_t i = 0; i < index; ++i)
            cur = &(*cur)->next;

        auto node = std::make_unique<Node<T>>(value);
        node->next = std::move(*cur);
        *cur = std::move(node);
        ++count;
        return true;
    }

    bool remove(const T &value)
    {
        std::unique_ptr<Node<T>> *cur = &head;
        while (*cur && (*cur)->value != value)
            cur = &(*cur)->next;

        if (!*cur)
            return false;

        *cur = std::move((*cur)->next);
        --count;
        return true;
    }

    bool find(const T &value) const
    {
        for (Node<T> *cur = head.get(); cur; cur = cur->next.get())
        {
            if (cur->value == value)
                return true;
        }
        return false;
    }

    void reverse()
    {
        std::unique_ptr<Node<T>> prev;
        while (head)
        {
            std::unique_ptr<Node<T>> next = std::move(head->next);
            head->next = std::move(prev);
            prev = std::move(head);
            head = std::move(next);
        }
        head = std::move(prev);
    }

    const T *middle() const
    {
        Node<T> *slow = head.get();
        Node<T> *fast = head.get();
        while (fast && fast->next)
        {
            slow = slow->next.get();
            fast = fast->next->next.get();
        }
        return slow ? &slow->value : nullptr;
    }

    std::size_t size() const
    {
        return count;
    }

    void print() const
    {
        for (Node<T> *cur = head.get(); cur; cur = cur->next.get())
            std::cout << cur->value << " -> ";
        std::cout << "null\n";
    }
};

int main()
{
    LinkedList<int> list;

    list.push_back(2);
    list.push_back(3);
    list.push_front(1);
    list.push_back(5);
    list.insert(3, 4);
    std::cout << "List: ";
    list.print();
    std::cout << "Size: " << list.size() << "\n";
    std::cout << "Middle: " << *list.middle() << "\n";

    std::cout << "Find 3: " << (list.find(3) ? "Found" : "Not Found") << "\n";
    std::cout << "Find 9: " << (list.find(9) ? "Found" : "Not Found") << "\n";

    list.remove(3);
    std::cout << "After remove(3): ";
    list.print();

    list.reverse();
    std::cout << "After reverse: ";
    list.print();

    return 0;
}
