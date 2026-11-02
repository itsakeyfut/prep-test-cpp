#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <vector>

struct Node
{
    int value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    explicit Node(int val) : value(val) {}
};

void preorder(const Node *node, std::vector<int> &out)
{
    if (!node)
        return;
    out.push_back(node->value);
    preorder(node->left.get(), out);
    preorder(node->right.get(), out);
}

void inorder(const Node *node, std::vector<int> &out)
{
    if (!node)
        return;
    inorder(node->left.get(), out);
    out.push_back(node->value);
    inorder(node->right.get(), out);
}

void postorder(const Node *node, std::vector<int> &out)
{
    if (!node)
        return;
    postorder(node->left.get(), out);
    postorder(node->right.get(), out);
    out.push_back(node->value);
}

std::vector<int> preorder_iter(const Node *root)
{
    std::vector<int> out;
    if (!root)
        return out;
    std::stack<const Node *> st;
    st.push(root);
    while (!st.empty())
    {
        const Node *node = st.top();
        st.pop();
        out.push_back(node->value);
        if (node->right)
            st.push(node->right.get());
        if (node->left)
            st.push(node->left.get());
    }
    return out;
}

std::vector<int> inorder_iter(const Node *root)
{
    std::vector<int> out;
    std::stack<const Node *> st;
    const Node *cur = root;
    while (cur || !st.empty())
    {
        while (cur)
        {
            st.push(cur);
            cur = cur->left.get();
        }
        cur = st.top();
        st.pop();
        out.push_back(cur->value);
        cur = cur->right.get();
    }
    return out;
}

std::vector<int> postorder_iter(const Node *root)
{
    std::vector<int> out;
    if (!root)
        return out;
    std::stack<const Node *> st;
    st.push(root);
    while (!st.empty())
    {
        const Node *node = st.top();
        st.pop();
        out.push_back(node->value);
        if (node->left)
            st.push(node->left.get());
        if (node->right)
            st.push(node->right.get());
    }
    std::reverse(out.begin(), out.end());
    return out;
}

std::vector<std::vector<int>> level_order(const Node *root)
{
    std::vector<std::vector<int>> levels;
    if (!root)
        return levels;
    std::queue<const Node *> q;
    q.push(root);
    while (!q.empty())
    {
        std::size_t size = q.size();
        std::vector<int> level;
        for (std::size_t i = 0; i < size; ++i)
        {
            const Node *node = q.front();
            q.pop();
            level.push_back(node->value);
            if (node->left)
                q.push(node->left.get());
            if (node->right)
                q.push(node->right.get());
        }
        levels.push_back(level);
    }
    return levels;
}

int max_depth(const Node *node)
{
    if (!node)
        return 0;
    return 1 + std::max(max_depth(node->left.get()), max_depth(node->right.get()));
}

void print(const char *label, const std::vector<int> &v)
{
    std::cout << label << ": ";
    for (int x : v)
        std::cout << x << " ";
    std::cout << "\n";
}

int main()
{
    auto root = std::make_unique<Node>(1);
    root->left = std::make_unique<Node>(2);
    root->right = std::make_unique<Node>(3);
    root->left->left = std::make_unique<Node>(4);
    root->left->right = std::make_unique<Node>(5);
    root->right->right = std::make_unique<Node>(6);

    std::vector<int> pre, in, post;
    preorder(root.get(), pre);
    inorder(root.get(), in);
    postorder(root.get(), post);
    print("preorder (rec) ", pre);
    print("preorder (iter)", preorder_iter(root.get()));
    print("inorder (rec)  ", in);
    print("inorder (iter) ", inorder_iter(root.get()));
    print("postorder (rec) ", post);
    print("postorder (iter)", postorder_iter(root.get()));

    std::cout << "level_order:\n";
    for (const auto &level : level_order(root.get()))
        print("  level", level);

    std::cout << "max_depth: " << max_depth(root.get()) << "\n";

    return 0;
}
