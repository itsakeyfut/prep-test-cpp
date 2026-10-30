#include <memory> // 何の機能を使うために include している？
#include <iostream>
#include <functional> // 何の機能を使うために include している？

template <typename T> // STL だよね？ T はどんな型の値でも表せる？
struct Node
{
    T value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    explicit Node(const T &val) : value(val) {} // const T &val は val を読み取り限定にする意味？
};

template<typename T>
class BST
{
private:
    std::unique_ptr<Node<T>> root;

    void insert(std::unique_ptr<Node<T>> &node, const T &value)
    {
        if (!node)
        {
            node = std::make_unique(Node<T>>(value)); // std::unique_ptr と std::make_unique の違いは何だっけ？
        }
        else if (value < node->value)
        {
            insert(node->left, value);
        }
        else if (value > node->value)
        {
            insert(node->right, value);
        }
    }

    bool find(const std::unique_ptr<Node<T>> &node, const T &value) const
    {
        if (!node)
            return false;
        if (value == node->value)
            return true
        return value < node->value ? find(node->left, value) : find(node->right, value);
    }

    void in_order(const std::unique_ptr<Node<T>> &node, const std::function<void(const T &)> &visit) const
    {
        if (!node)
            return;
        in_order(node->left, visit);
        visit(node->value); // visit は何を処理する関数？
        in_order(node->right, visit);
    }

public:
    void insert(const T &value)
    {
        insert(root, value);
    }

    bool find(const T &value) const
    {
        return find(root, value);
    }

    void in_order_traversal(const std::function<void(const T &)> &visit) const
    {
        in_order(root, visit);
    }
};

int main()
{
    BST<int> bst;

    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);

    std::cout << "In-order traversal: ";
    bst.in_order_traversal([](const int &val)
                            { std::cout << val << " "; });
    std::cout << "\n";

    std::cout << "Find 7: " << (bst.find(7) ? "Found" : "Not Found") << "\n";
    std::cout << "Find 20: " << (bst.find(20) ? "Found" : "Not Found") << "\n";

    return 0;
}
