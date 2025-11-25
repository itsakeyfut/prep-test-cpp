/**
 * Tree DFS/BFS - アクティブリコール問題
 *
 * 各パターンを見ずに書いてみましょう。
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;

// ========================================
// 問題0: TreeNode 定義
// ========================================

// Q0: TreeNode 構造体を定義（val, left, right）
struct TreeNode
{
    // TODO:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ========================================
// 問題1: DFS 3種（再帰）
// ========================================

// Q1-1: 前順走査（Preorder: Root -> Left -> Right）
void preorderRecursive(TreeNode *root)
{
    // TODO:
}

// Q1-2: 中順走査（Inorder: Left -> Root -> Right）
void inorderRecursive(TreeNode *root)
{
    // TODO:
}

// Q1-3: 後順走査（Postorder: Left -> Right -> Root）
void postorderRecursive(TreeNode *root)
{
    // TODO:
}

// ========================================
// 問題2: DFS（ラムダ再帰）
// ========================================

// Q2: 前順走査をラムダで書く
// ヒント: auto dfs = [&](auto&& self, TreeNode* node) -> void { ... }
void dfsWithLambda(TreeNode *root)
{
    // TODO:
}

// ========================================
// 問題3: DFS（反復、スタック使用）
// ========================================

// Q3-1: 前順走査（反復）
// ヒント: 右を先にpush、左を後にpush
void preorderIterative(TreeNode *root)
{
    // TODO:
}

// Q3-2: 中順走査（反復）
// ヒント: 左端まで行って、戻りながら処理
void inorderIterative(TreeNode *root)
{
    // TODO:
}

// ========================================
// 問題4: BFS（レベル順走査）
// ========================================

// Q4-1: 単純なBFS
void bfsLevelOrder(TreeNode *root)
{
    // TODO:
}

// Q4-2: レベルごとに処理（2重ループ）
// 戻り値: [[1], [2,3], [4,5,6,7]] のような形式
vector<vector<int>> levelOrder(TreeNode *root)
{
    // TODO:
    return {};
}

// ========================================
// 問題5: Maximum Depth (LC 104)
// ========================================

// Q5: 木の最大深さを求める
int maxDepth(TreeNode *root)
{
    // TODO:
    return 0;
}

// ========================================
// 問題6: Invert Binary Tree (LC 226)
// ========================================

// Q6: 木を左右反転する
TreeNode *invertTree(TreeNode *root)
{
    // TODO:
    return nullptr;
}

// ========================================
// 問題7: Same Tree (LC 100)
// ========================================

// Q7: 2つの木が同じかどうか判定
bool isSameTree(TreeNode *p, TreeNode *q)
{
    // TODO:
    return false;
}

// ========================================
// 問題8: Symmetric Tree (LC 101)
// ========================================

// Q8: 木が左右対称かどうか判定
// ヒント: 左の左と右の右、左の右と右の左を比較
bool isSymmetric(TreeNode *root)
{
    // TODO:
    return false;
}

// ========================================
// 問題9: Path Sum (LC 112)
// ========================================

// Q9: ルートから葉までのパスで合計が targetSum になるものがあるか
bool hasPathSum(TreeNode *root, int targetSum)
{
    // TODO:
    return false;
}

// ========================================
// 問題10: Lowest Common Ancestor (LC 236)
// ========================================

// Q10: 最小共通祖先を求める
// ヒント: 左右を再帰的に探索し、両方見つかればそのノードが答え
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    // TODO:
    return nullptr;
}

// ========================================
// 問題11: Diameter of Binary Tree (LC 543)
// ========================================

// Q11: 木の直径（最長パスのエッジ数）を求める
// ヒント: 各ノードで「左の高さ + 右の高さ」を計算
int diameterOfBinaryTree(TreeNode *root)
{
    // TODO:
    return 0;
}

// ========================================
// 問題12: Validate BST (LC 98)
// ========================================

// Q12: 有効な二分探索木かどうか判定
// ヒント: 各ノードで有効な範囲 (min, max) を持つ
bool isValidBST(TreeNode *root)
{
    // TODO:
    return false;
}

// ========================================
// 問題13: Kth Smallest in BST (LC 230)
// ========================================

// Q13: BST で k 番目に小さい要素を求める
// ヒント: 中順走査で k 番目を見つける
int kthSmallest(TreeNode *root, int k)
{
    // TODO:
    return 0;
}

// ========================================
// 問題14: Right Side View (LC 199)
// ========================================

// Q14: 木を右から見た時に見えるノードの値
// ヒント: BFS で各レベルの最後のノード
vector<int> rightSideView(TreeNode *root)
{
    // TODO:
    return {};
}

int main()
{
    // テストケース作成
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

/**
 * チェックリスト（答えを見ずに書けたか？）:
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
