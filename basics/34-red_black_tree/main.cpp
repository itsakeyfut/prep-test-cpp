#include <iostream>
#include <vector>

enum class Color
{
    Red,
    Black
};

struct Node
{
    int value;
    Color color = Color::Red;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;

    explicit Node(int val) : value(val) {}
};

class RedBlackTree
{
private:
    Node *root = nullptr;

    void rotate_left(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left)
            y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotate_right(Node *x)
    {
        Node *y = x->left;
        x->left = y->right;
        if (y->right)
            y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void fix_insert(Node *z)
    {
        while (z->parent && z->parent->color == Color::Red)
        {
            Node *parent = z->parent;
            Node *grand = parent->parent;

            if (parent == grand->left)
            {
                Node *uncle = grand->right;
                if (uncle && uncle->color == Color::Red)
                {
                    parent->color = Color::Black;
                    uncle->color = Color::Black;
                    grand->color = Color::Red;
                    z = grand;
                }
                else
                {
                    if (z == parent->right)
                    {
                        z = parent;
                        rotate_left(z);
                        parent = z->parent;
                    }
                    parent->color = Color::Black;
                    grand->color = Color::Red;
                    rotate_right(grand);
                }
            }
            else
            {
                Node *uncle = grand->left;
                if (uncle && uncle->color == Color::Red)
                {
                    parent->color = Color::Black;
                    uncle->color = Color::Black;
                    grand->color = Color::Red;
                    z = grand;
                }
                else
                {
                    if (z == parent->left)
                    {
                        z = parent;
                        rotate_right(z);
                        parent = z->parent;
                    }
                    parent->color = Color::Black;
                    grand->color = Color::Red;
                    rotate_left(grand);
                }
            }
        }
        root->color = Color::Black;
    }

    static int black_height(const Node *node)
    {
        if (!node)
            return 1;
        if (node->color == Color::Red &&
            ((node->left && node->left->color == Color::Red) ||
             (node->right && node->right->color == Color::Red)))
            return -1;

        int lh = black_height(node->left);
        int rh = black_height(node->right);
        if (lh == -1 || rh == -1 || lh != rh)
            return -1;
        return lh + (node->color == Color::Black ? 1 : 0);
    }

    static void in_order(const Node *node)
    {
        if (!node)
            return;
        in_order(node->left);
        std::cout << node->value << (node->color == Color::Red ? "(R) " : "(B) ");
        in_order(node->right);
    }

    static void destroy(Node *node)
    {
        if (!node)
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    RedBlackTree() = default;
    RedBlackTree(const RedBlackTree &) = delete;
    RedBlackTree &operator=(const RedBlackTree &) = delete;

    ~RedBlackTree()
    {
        destroy(root);
    }

    void insert(int value)
    {
        Node *parent = nullptr;
        Node *cur = root;
        while (cur)
        {
            parent = cur;
            if (value < cur->value)
                cur = cur->left;
            else if (value > cur->value)
                cur = cur->right;
            else
                return;
        }

        Node *node = new Node(value);
        node->parent = parent;
        if (!parent)
            root = node;
        else if (value < parent->value)
            parent->left = node;
        else
            parent->right = node;

        fix_insert(node);
    }

    void print() const
    {
        in_order(root);
        std::cout << "\n";
    }

    bool is_valid() const
    {
        if (root && root->color != Color::Black)
            return false;
        return black_height(root) != -1;
    }

    int root_value() const
    {
        return root->value;
    }

    int black_height() const
    {
        return black_height(root);
    }
};

int main()
{
    std::vector<std::vector<int>> inputs{
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {41, 38, 31, 12, 19, 8, 45, 50, 3, 25},
    };

    for (const auto &values : inputs)
    {
        RedBlackTree rb;
        for (int v : values)
            rb.insert(v);

        std::cout << "In-order traversal: ";
        rb.print();
        std::cout << "Root: " << rb.root_value() << "\n";
        std::cout << "Black height: " << rb.black_height() << "\n";
        std::cout << "Valid RB tree: " << (rb.is_valid() ? "Yes" : "No") << "\n\n";
    }

    return 0;
}
