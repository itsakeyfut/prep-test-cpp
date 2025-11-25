/**
 * Tree DFS/BFS - 解答
 *
 * problems.cpp の解答です。
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;

// ========================================
// 解答0: TreeNode 定義
// ========================================

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ========================================
// 解答1: DFS 3種（再帰）
// ========================================

// 前順走査（Preorder: Root -> Left -> Right）
void preorderRecursive(TreeNode *root)
{
    if (!root)
        return;

    cout << root->val << " "; // 処理（前）
    preorderRecursive(root->left);
    preorderRecursive(root->right);
}

// 中順走査（Inorder: Left -> Root -> Right）
void inorderRecursive(TreeNode *root)
{
    if (!root)
        return;

    inorderRecursive(root->left);
    cout << root->val << " "; // 処理（中）
    inorderRecursive(root->right);
}

// 後順走査（Postorder: Left -> Right -> Root）
void postorderRecursive(TreeNode *root)
{
    if (!root)
        return;

    postorderRecursive(root->left);
    postorderRecursive(root->right);
    cout << root->val << " "; // 処理（後）
}

// ========================================
// 解答2: DFS（ラムダ再帰）
// ========================================

void dfsWithLambda(TreeNode *root)
{
    auto dfs = [&](auto &&self, TreeNode *node) -> void
    {
        if (!node)
            return;

        cout << node->val << " ";
        self(self, node->left);
        self(self, node->right);
    };

    dfs(dfs, root);
}

// ========================================
// 解答3: DFS（反復、スタック使用）
// ========================================

void preorderIterative(TreeNode *root)
{
    if (!root)
        return;

    stack<TreeNode *> st;
    st.push(root);

    while (!st.empty())
    {
        TreeNode *node = st.top();
        st.pop();

        cout << node->val << " ";

        // 右を先にpush（後で左が先に出る）
        if (node->right)
            st.push(node->right);
        if (node->left)
            st.push(node->left);
    }
}

void inorderIterative(TreeNode *root)
{
    stack<TreeNode *> st;
    TreeNode *curr = root;

    while (curr || !st.empty())
    {
        // 左端まで行く
        while (curr)
        {
            st.push(curr);
            curr = curr->left;
        }

        curr = st.top();
        st.pop();
        cout << curr->val << " ";

        curr = curr->right;
    }
}

// ========================================
// 解答4: BFS（レベル順走査）
// ========================================

void bfsLevelOrder(TreeNode *root)
{
    if (!root)
        return;

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *node = q.front();
        q.pop();

        cout << node->val << " ";

        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }
}

vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> result;
    if (!root)
        return result;

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        int size = q.size();
        vector<int> level;

        for (int i = 0; i < size; i++)
        {
            TreeNode *node = q.front();
            q.pop();

            level.push_back(node->val);

            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }

        result.push_back(level);
    }

    return result;
}

// ========================================
// 解答5: Maximum Depth
// ========================================

int maxDepth(TreeNode *root)
{
    if (!root)
        return 0;

    int left = maxDepth(root->left);
    int right = maxDepth(root->right);

    return 1 + max(left, right);
}

// ========================================
// 解答6: Invert Binary Tree
// ========================================

TreeNode *invertTree(TreeNode *root)
{
    if (!root)
        return nullptr;

    // 左右を入れ替え
    TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;

    invertTree(root->left);
    invertTree(root->right);

    return root;
}

// ========================================
// 解答7: Same Tree
// ========================================

bool isSameTree(TreeNode *p, TreeNode *q)
{
    if (!p && !q)
        return true;
    if (!p || !q)
        return false;

    return p->val == q->val &&
           isSameTree(p->left, q->left) &&
           isSameTree(p->right, q->right);
}

// ========================================
// 解答8: Symmetric Tree
// ========================================

bool isSymmetric(TreeNode *root)
{
    auto isMirror = [&](auto &&self, TreeNode *left, TreeNode *right) -> bool
    {
        if (!left && !right)
            return true;
        if (!left || !right)
            return false;

        return left->val == right->val &&
               self(self, left->left, right->right) &&
               self(self, left->right, right->left);
    };

    return isMirror(isMirror, root->left, root->right);
}

// ========================================
// 解答9: Path Sum
// ========================================

bool hasPathSum(TreeNode *root, int targetSum)
{
    if (!root)
        return false;

    // 葉ノードで判定
    if (!root->left && !root->right)
    {
        return root->val == targetSum;
    }

    int remaining = targetSum - root->val;
    return hasPathSum(root->left, remaining) ||
           hasPathSum(root->right, remaining);
}

// ========================================
// 解答10: Lowest Common Ancestor
// ========================================

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (!root || root == p || root == q)
        return root;

    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);

    if (left && right)
        return root;            // 両方見つかった
    return left ? left : right; // どちらか一方
}

// ========================================
// 解答11: Diameter of Binary Tree
// ========================================

int diameterOfBinaryTree(TreeNode *root)
{
    int diameter = 0;

    auto height = [&](auto &&self, TreeNode *node) -> int
    {
        if (!node)
            return 0;

        int left = self(self, node->left);
        int right = self(self, node->right);

        // このノードを通る最長パス
        diameter = max(diameter, left + right);

        return 1 + max(left, right);
    };

    height(height, root);
    return diameter;
}

// ========================================
// 解答12: Validate BST
// ========================================

bool isValidBST(TreeNode *root)
{
    auto validate = [&](auto &&self, TreeNode *node, long min_val, long max_val) -> bool
    {
        if (!node)
            return true;

        if (node->val <= min_val || node->val >= max_val)
        {
            return false;
        }

        return self(self, node->left, min_val, node->val) &&
               self(self, node->right, node->val, max_val);
    };

    return validate(validate, root, LONG_MIN, LONG_MAX);
}

// ========================================
// 解答13: Kth Smallest in BST
// ========================================

int kthSmallest(TreeNode *root, int k)
{
    int count = 0;
    int result = 0;

    auto inorder = [&](auto &&self, TreeNode *node) -> void
    {
        if (!node)
            return;

        self(self, node->left);

        count++;
        if (count == k)
        {
            result = node->val;
            return;
        }

        self(self, node->right);
    };

    inorder(inorder, root);
    return result;
}

// ========================================
// 解答14: Right Side View
// ========================================

vector<int> rightSideView(TreeNode *root)
{
    vector<int> result;
    if (!root)
        return result;

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        int size = q.size();

        for (int i = 0; i < size; i++)
        {
            TreeNode *node = q.front();
            q.pop();

            // 各レベルの最後のノード
            if (i == size - 1)
            {
                result.push_back(node->val);
            }

            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
    }

    return result;
}

int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << "=== Traversals ===\n";
    cout << "Preorder: ";
    preorderRecursive(root);
    cout << "\n";

    cout << "Inorder: ";
    inorderRecursive(root);
    cout << "\n";

    cout << "Postorder: ";
    postorderRecursive(root);
    cout << "\n";

    cout << "BFS: ";
    bfsLevelOrder(root);
    cout << "\n";

    cout << "\n=== Problems ===\n";
    cout << "Max Depth: " << maxDepth(root) << "\n";
    cout << "Diameter: " << diameterOfBinaryTree(root) << "\n";

    return 0;
}
