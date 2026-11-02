#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

template <typename T>
struct Node
{
    T value;
    int height = 1;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    explicit Node(const T &val) : value(val) {}
};

template <typename T>
class AVLTree
{
private:
    using NodePtr = std::unique_ptr<Node<T>>;
    NodePtr root;

    static int height(const NodePtr &node)
    {
        return node ? node->height : 0;
    }

    static int balance_factor(const NodePtr &node)
    {
        return node ? height(node->left) - height(node->right) : 0;
    }

    static void update_height(NodePtr &node)
    {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    static NodePtr rotate_right(NodePtr node)
    {
        NodePtr new_root = std::move(node->left);
        node->left = std::move(new_root->right);
        update_height(node);
        new_root->right = std::move(node);
        update_height(new_root);
        return new_root;
    }

    static NodePtr rotate_left(NodePtr node)
    {
        NodePtr new_root = std::move(node->right);
        node->right = std::move(new_root->left);
        update_height(node);
        new_root->left = std::move(node);
        update_height(new_root);
        return new_root;
    }

    static NodePtr rebalance(NodePtr node)
    {
        update_height(node);
        int bf = balance_factor(node);

        if (bf > 1)
        {
            if (balance_factor(node->left) < 0)
                node->left = rotate_left(std::move(node->left));
            return rotate_right(std::move(node));
        }
        if (bf < -1)
        {
            if (balance_factor(node->right) > 0)
                node->right = rotate_right(std::move(node->right));
            return rotate_left(std::move(node));
        }
        return node;
    }

    void insert(NodePtr &node, const T &value)
    {
        if (!node)
        {
            node = std::make_unique<Node<T>>(value);
            return;
        }
        if (value < node->value)
            insert(node->left, value);
        else if (value > node->value)
            insert(node->right, value);
        else
            return;

        node = rebalance(std::move(node));
    }

    void in_order(const NodePtr &node, const std::function<void(const T &)> &visit) const
    {
        if (!node)
            return;
        in_order(node->left, visit);
        visit(node->value);
        in_order(node->right, visit);
    }

    static bool is_balanced(const NodePtr &node)
    {
        if (!node)
            return true;
        return std::abs(balance_factor(node)) <= 1 && is_balanced(node->left) && is_balanced(node->right);
    }

public:
    void insert(const T &value)
    {
        insert(root, value);
    }

    void in_order_traversal(const std::function<void(const T &)> &visit) const
    {
        in_order(root, visit);
    }

    int height() const
    {
        return height(root);
    }

    const T &root_value() const
    {
        return root->value;
    }

    bool is_balanced() const
    {
        return is_balanced(root);
    }
};

int main()
{
    AVLTree<int> avl;
    for (int i = 1; i <= 7; ++i)
        avl.insert(i);

    std::cout << "In-order traversal: ";
    avl.in_order_traversal([](const int &val)
                           { std::cout << val << " "; });
    std::cout << "\n";
    std::cout << "Root: " << avl.root_value() << "\n";
    std::cout << "Height: " << avl.height() << "\n";
    std::cout << "Balanced: " << (avl.is_balanced() ? "Yes" : "No") << "\n";

    std::vector<std::pair<std::string, std::vector<int>>> cases{
        {"LL", {3, 2, 1}},
        {"RR", {1, 2, 3}},
        {"LR", {3, 1, 2}},
        {"RL", {1, 3, 2}},
    };

    for (const auto &[name, values] : cases)
    {
        AVLTree<int> tree;
        for (int v : values)
            tree.insert(v);
        std::cout << name << ": root=" << tree.root_value() << " height=" << tree.height() << "\n";
    }

    return 0;
}
