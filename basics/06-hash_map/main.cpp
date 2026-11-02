#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>

template <typename K, typename V>
class HashMap
{
private:
    std::vector<std::list<std::pair<K, V>>> buckets;
    std::size_t count;

    std::size_t index_of(const K &key) const
    {
        return std::hash<K>{}(key) % buckets.size();
    }

    void rehash()
    {
        std::vector<std::list<std::pair<K, V>>> old = std::move(buckets);
        buckets = std::vector<std::list<std::pair<K, V>>>(old.size() * 2);
        for (auto &bucket : old)
        {
            for (auto &kv : bucket)
                buckets[index_of(kv.first)].push_back(std::move(kv));
        }
    }

public:
    explicit HashMap(std::size_t bucket_count = 8)
        : buckets(bucket_count), count(0) {}

    void insert(const K &key, const V &value)
    {
        auto &bucket = buckets[index_of(key)];
        for (auto &kv : bucket)
        {
            if (kv.first == key)
            {
                kv.second = value;
                return;
            }
        }

        bucket.emplace_back(key, value);
        ++count;
        if (static_cast<double>(count) / buckets.size() > 0.75)
            rehash();
    }

    V *find(const K &key)
    {
        for (auto &kv : buckets[index_of(key)])
        {
            if (kv.first == key)
                return &kv.second;
        }
        return nullptr;
    }

    bool erase(const K &key)
    {
        auto &bucket = buckets[index_of(key)];
        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->first == key)
            {
                bucket.erase(it);
                --count;
                return true;
            }
        }
        return false;
    }

    std::size_t size() const
    {
        return count;
    }

    std::size_t bucket_count() const
    {
        return buckets.size();
    }
};

int main()
{
    HashMap<std::string, int> map(4);

    map.insert("apple", 100);
    map.insert("banana", 200);
    map.insert("cherry", 300);
    std::cout << "size=" << map.size() << " buckets=" << map.bucket_count() << "\n";

    map.insert("durian", 400);
    std::cout << "After rehash: size=" << map.size() << " buckets=" << map.bucket_count() << "\n";

    map.insert("apple", 150);
    if (int *v = map.find("apple"))
        std::cout << "apple -> " << *v << "\n";

    std::cout << "find(grape): " << (map.find("grape") ? "Found" : "Not Found") << "\n";

    map.erase("banana");
    std::cout << "After erase(banana): find(banana) = "
              << (map.find("banana") ? "Found" : "Not Found")
              << ", size=" << map.size() << "\n";

    return 0;
}
