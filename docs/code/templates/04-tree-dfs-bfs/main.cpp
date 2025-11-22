/**
 * Tree（木構造）DFS/BFS テンプレート
 * Big Tech 面接で必須のパターン
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

// ========================================
// TreeNode 定義（LeetCode標準）
// ========================================

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ========================================
// パターン1: DFS（深さ優先探索）- 再帰
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
// BST では昇順になる
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
// パターン2: DFS - ラムダ再帰（現代的な書き方）
// ========================================

void dfsWithLambda(TreeNode *root)
{
    // 前順走査のラムダ版
    auto dfs = [&](auto &&self, TreeNode *node) -> void
    {
        if (!node)
            return;

        cout << node->val << " "; // 処理
        self(self, node->left);
        self(self, node->right);
    };

    dfs(dfs, root);
}

// 戻り値ありのラムダDFS
int maxDepthLambda(TreeNode *root)
{
    auto dfs = [&](auto &&self, TreeNode *node) -> int
    {
        if (!node)
            return 0;

        int left = self(self, node->left);
        int right = self(self, node->right);

        return 1 + max(left, right);
    };

    return dfs(dfs, root);
}

// ========================================
// パターン3: DFS - 反復（スタック使用）
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
// パターン4: BFS（幅優先探索）- レベル順走査
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

// レベルごとに処理
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
// 実戦問題パターン
// ========================================

// 問題1: Maximum Depth of Binary Tree (LC 104)
int maxDepth(TreeNode *root)
{
    if (!root)
        return 0;

    int left = maxDepth(root->left);
    int right = maxDepth(root->right);

    return 1 + max(left, right);
}

// 問題2: Invert Binary Tree (LC 226)
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

// 問題3: Same Tree (LC 100)
bool isSameTree(TreeNode *p, TreeNode *q)
{
    if (!p && !q)
        return true;
    if (!p || !q)
        return false;

    return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

// 問題4: Symmetric Tree (LC 101)
bool isSymmetric(TreeNode *root)
{
    auto isMirror = [&](auto &&self, TreeNode *left, TreeNode *right) -> bool
    {
        if (!left && !right)
            return true;
        if (!left || !right)
            return false;

        return left->val == right->val && self(self, left->left, right->right) && self(self, left->right, right->left);
    };

    return isMirror(isMirror, root->left, root->right);
}

// 問題5: Path Sum (LC 112)
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
    return hasPathSum(root->left, remaining) || hasPathSum(root->right, remaining);
}

// 問題6: Lowest Common Ancestor (LC 236)
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

// 問題7: Diameter of Binary Tree (LC 543)
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

// 問題8: Binary Tree Right Side View (LC 199)
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

// ========================================
// BST（二分探索木）特有のパターン
// ========================================

// Validate BST (LC 98)
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

        return self(self, node->left, min_val, node->val) && self(self, node->right, node->val, max_val);
    };

    return validate(validate, root, LONG_MIN, LONG_MAX);
}

// Kth Smallest Element in BST (LC 230)
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

// Insert into BST (LC 701)
TreeNode *insertIntoBST(TreeNode *root, int val)
{
    if (!root)
        return new TreeNode(val);

    if (val < root->val)
    {
        root->left = insertIntoBST(root->left, val);
    }
    else
    {
        root->right = insertIntoBST(root->right, val);
    }

    return root;
}

// ========================================
// 木の構築
// ========================================

// Construct Binary Tree from Preorder and Inorder (LC 105)
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
{
    int preIdx = 0;

    auto build = [&](auto &&self, int inStart, int inEnd) -> TreeNode *
    {
        if (inStart > inEnd)
            return nullptr;

        int rootVal = preorder[preIdx++];
        TreeNode *root = new TreeNode(rootVal);

        // inorder で root の位置を探す
        int inIdx = inStart;
        while (inorder[inIdx] != rootVal)
            inIdx++;

        root->left = self(self, inStart, inIdx - 1);
        root->right = self(self, inIdx + 1, inEnd);

        return root;
    };

    return build(build, 0, inorder.size() - 1);
}

// ========================================
// 便利な補助関数
// ========================================

// 木を配列から構築（LeetCode形式）
TreeNode *buildTreeFromArray(vector<int> &arr)
{
    if (arr.empty() || arr[0] == -1)
        return nullptr;

    TreeNode *root = new TreeNode(arr[0]);
    queue<TreeNode *> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < arr.size())
    {
        TreeNode *node = q.front();
        q.pop();

        if (i < arr.size() && arr[i] != -1)
        {
            node->left = new TreeNode(arr[i]);
            q.push(node->left);
        }
        i++;

        if (i < arr.size() && arr[i] != -1)
        {
            node->right = new TreeNode(arr[i]);
            q.push(node->right);
        }
        i++;
    }

    return root;
}

// 木を削除
void deleteTree(TreeNode *root)
{
    if (!root)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// ========================================
// デバッグ用：木を視覚的に出力
// ========================================

void printTree(TreeNode *root, string prefix = "", bool isLeft = true)
{
    if (!root)
        return;

    cout << prefix;
    cout << (isLeft ? "├──" : "└──");
    cout << root->val << "\n";

    printTree(root->left, prefix + (isLeft ? "│   " : "    "), true);
    printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
}

int main()
{
    // テストケース作成
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

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

    cout << "Max Depth: " << maxDepth(root) << "\n";

    cout << "Tree structure:\n";
    printTree(root);

    // メモリ解放
    deleteTree(root);

    return 0;
}

/**
 * 暗記チェックリスト:
 *
 * [ ] TreeNode 構造体の定義
 * [ ] DFS 3種（前順・中順・後順）を再帰で書ける
 * [ ] ラムダ再帰の書き方
 * [ ] BFS（レベル順走査）をキューで書ける
 * [ ] レベルごとに処理するBFS
 * [ ] 木の最大深さ
 * [ ] 木の反転
 * [ ] 同じ木かの判定
 * [ ] Lowest Common Ancestor
 * [ ] BST の検証
 * [ ] BST の k 番目の要素
 * [ ] null チェックの重要性
 */