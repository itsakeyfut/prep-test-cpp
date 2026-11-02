#include <array>
#include <iostream>
#include <memory>
#include <string>

struct TrieNode
{
    std::array<std::unique_ptr<TrieNode>, 26> children;
    bool is_end = false;
};

class Trie
{
private:
    std::unique_ptr<TrieNode> root;

    const TrieNode *find_node(const std::string &s) const
    {
        const TrieNode *node = root.get();
        for (char c : s)
        {
            int i = c - 'a';
            if (!node->children[i])
                return nullptr;
            node = node->children[i].get();
        }
        return node;
    }

public:
    Trie() : root(std::make_unique<TrieNode>()) {}

    void insert(const std::string &word)
    {
        TrieNode *node = root.get();
        for (char c : word)
        {
            int i = c - 'a';
            if (!node->children[i])
                node->children[i] = std::make_unique<TrieNode>();
            node = node->children[i].get();
        }
        node->is_end = true;
    }

    bool search(const std::string &word) const
    {
        const TrieNode *node = find_node(word);
        return node && node->is_end;
    }

    bool starts_with(const std::string &prefix) const
    {
        return find_node(prefix) != nullptr;
    }
};

int main()
{
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("bat");

    std::cout << std::boolalpha;
    std::cout << "search(\"apple\"): " << trie.search("apple") << "\n";
    std::cout << "search(\"app\"): " << trie.search("app") << "\n";
    std::cout << "search(\"appl\"): " << trie.search("appl") << "\n";
    std::cout << "starts_with(\"appl\"): " << trie.starts_with("appl") << "\n";
    std::cout << "starts_with(\"ba\"): " << trie.starts_with("ba") << "\n";
    std::cout << "starts_with(\"cat\"): " << trie.starts_with("cat") << "\n";

    return 0;
}
