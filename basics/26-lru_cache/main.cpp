#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>

class LRUCache
{
private:
    std::size_t capacity;
    std::list<std::pair<int, int>> items;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> index;

public:
    explicit LRUCache(std::size_t cap) : capacity(cap) {}

    int get(int key)
    {
        auto it = index.find(key);
        if (it == index.end())
            return -1;

        items.splice(items.begin(), items, it->second);
        return it->second->second;
    }

    void put(int key, int value)
    {
        auto it = index.find(key);
        if (it != index.end())
        {
            it->second->second = value;
            items.splice(items.begin(), items, it->second);
            return;
        }

        if (items.size() == capacity)
        {
            index.erase(items.back().first);
            items.pop_back();
        }

        items.emplace_front(key, value);
        index[key] = items.begin();
    }

    void print() const
    {
        std::cout << "[MRU] ";
        for (const auto &kv : items)
            std::cout << "(" << kv.first << ":" << kv.second << ") ";
        std::cout << "[LRU]\n";
    }
};

int main()
{
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    cache.print();

    std::cout << "get(1) = " << cache.get(1) << "\n";
    cache.print();

    cache.put(3, 3);
    std::cout << "put(3,3) evicts key 2\n";
    cache.print();

    std::cout << "get(2) = " << cache.get(2) << "\n";

    cache.put(4, 4);
    std::cout << "put(4,4) evicts key 1\n";
    cache.print();

    std::cout << "get(1) = " << cache.get(1) << "\n";
    std::cout << "get(3) = " << cache.get(3) << "\n";
    std::cout << "get(4) = " << cache.get(4) << "\n";

    return 0;
}
