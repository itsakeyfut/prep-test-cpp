# Tree DFS/BFS 解説

## 1. TreeNode 構造体

```cpp
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```

**これは暗記必須！** LeetCode 標準の定義。

---

## 2. DFS の3種類

| 名前 | 順序 | 用途 |
|------|------|------|
| 前順 (Preorder) | Root → Left → Right | コピー、シリアライズ |
| 中順 (Inorder) | Left → Root → Right | BST で昇順取得 |
| 後順 (Postorder) | Left → Right → Root | 削除、子の結果を使う |

### 図解

```
      1
     / \
    2   3
   / \
  4   5

Preorder:  1, 2, 4, 5, 3  (ルートを先に)
Inorder:   4, 2, 5, 1, 3  (ルートを真ん中に)
Postorder: 4, 5, 2, 3, 1  (ルートを最後に)
```

---

## 3. DFS 再帰パターン

```cpp
void preorder(TreeNode* root) {
    if (!root) return;      // ベースケース

    // 処理（前）
    preorder(root->left);
    // 処理（中）← Inorder ならここ
    preorder(root->right);
    // 処理（後）← Postorder ならここ
}
```

**覚え方:** 処理の位置が「前」「中」「後」

---

## 4. ラムダ再帰（モダンな書き方）

```cpp
auto dfs = [&](auto&& self, TreeNode* node) -> void {
    if (!node) return;

    cout << node->val << " ";
    self(self, node->left);
    self(self, node->right);
};

dfs(dfs, root);
```

**ポイント:**
- `auto&& self` で自分自身を参照
- 呼び出し時は `self(self, ...)` と第1引数に自分を渡す
- 戻り値が必要なら `-> int` のように指定

---

## 5. DFS 反復（スタック使用）

### 前順走査

```cpp
void preorderIterative(TreeNode* root) {
    if (!root) return;

    stack<TreeNode*> st;
    st.push(root);

    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();

        cout << node->val << " ";

        // 右を先にpush（スタックは LIFO なので左が先に出る）
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }
}
```

### 中順走査

```cpp
void inorderIterative(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* curr = root;

    while (curr || !st.empty()) {
        // 左端まで行く
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }

        curr = st.top();
        st.pop();
        cout << curr->val << " ";

        curr = curr->right;
    }
}
```

---

## 6. BFS（レベル順走査）

### 基本パターン

```cpp
void bfs(TreeNode* root) {
    if (!root) return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        cout << node->val << " ";

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}
```

### レベルごとに処理

```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();  // このレベルのノード数
        vector<int> level;

        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();

            level.push_back(node->val);

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        result.push_back(level);
    }

    return result;
}
```

**ポイント:** `size = q.size()` をループ前に保存

---

## 7. 典型問題

### Maximum Depth (LC 104)

```cpp
int maxDepth(TreeNode* root) {
    if (!root) return 0;

    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}
```

**考え方:** 「高さ = 1 + 子の高さの最大値」

---

### Invert Binary Tree (LC 226)

```cpp
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;

    swap(root->left, root->right);

    invertTree(root->left);
    invertTree(root->right);

    return root;
}
```

---

### Same Tree (LC 100)

```cpp
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;   // 両方 null
    if (!p || !q) return false;  // 片方だけ null

    return p->val == q->val &&
           isSameTree(p->left, q->left) &&
           isSameTree(p->right, q->right);
}
```

---

### Lowest Common Ancestor (LC 236)

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;

    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    if (left && right) return root;  // 両方見つかった→このノードがLCA
    return left ? left : right;       // 片方だけ見つかった
}
```

**考え方:**
1. p か q に到達したら、そのノードを返す
2. 左右両方から結果が返ってきたら、現在のノードが LCA
3. 片方だけなら、その結果を上に伝播

---

### Diameter of Binary Tree (LC 543)

```cpp
int diameterOfBinaryTree(TreeNode* root) {
    int diameter = 0;

    auto height = [&](auto&& self, TreeNode* node) -> int {
        if (!node) return 0;

        int left = self(self, node->left);
        int right = self(self, node->right);

        diameter = max(diameter, left + right);  // このノードを通る最長パス

        return 1 + max(left, right);
    };

    height(height, root);
    return diameter;
}
```

**考え方:** 各ノードで「左の高さ + 右の高さ」を計算し、最大を記録

---

## 8. BST 特有のパターン

### Validate BST (LC 98)

```cpp
bool isValidBST(TreeNode* root) {
    auto validate = [&](auto&& self, TreeNode* node, long min, long max) -> bool {
        if (!node) return true;

        if (node->val <= min || node->val >= max) return false;

        return self(self, node->left, min, node->val) &&
               self(self, node->right, node->val, max);
    };

    return validate(validate, root, LONG_MIN, LONG_MAX);
}
```

**考え方:** 各ノードで「有効な値の範囲」を持つ

---

### Kth Smallest in BST (LC 230)

```cpp
int kthSmallest(TreeNode* root, int k) {
    int count = 0, result = 0;

    auto inorder = [&](auto&& self, TreeNode* node) -> void {
        if (!node) return;

        self(self, node->left);

        count++;
        if (count == k) {
            result = node->val;
            return;
        }

        self(self, node->right);
    };

    inorder(inorder, root);
    return result;
}
```

**考え方:** BST の中順走査は昇順 → k 番目が答え

---

## 9. null チェックの重要性

```cpp
// 必須パターン
if (!root) return ...;

// 両方 null / 片方 null の判定
if (!p && !q) return true;   // 両方 null
if (!p || !q) return false;  // 片方だけ null

// 子ノードを queue に入れる前
if (node->left) q.push(node->left);
if (node->right) q.push(node->right);
```

---

## 10. DFS vs BFS の使い分け

| 問題タイプ | 推奨 | 理由 |
|-----------|------|------|
| パスの探索 | DFS | 再帰で自然に書ける |
| 最短距離 | BFS | レベル順 = 距離 |
| レベルごとの処理 | BFS | size を使って分離 |
| 木の高さ・深さ | DFS | 再帰で簡単 |
| 全ノード処理 | どちらでも | |

---

## 11. 計算量

| アルゴリズム | 時間 | 空間 |
|-------------|------|------|
| DFS | O(n) | O(h) ※h=高さ |
| BFS | O(n) | O(w) ※w=最大幅 |

**最悪ケース:**
- スキュー木（一直線）: DFS の空間が O(n)
- 完全二分木: BFS の空間が O(n/2) ≈ O(n)

---

## 12. よくある間違い

### 間違い1: null チェック忘れ

```cpp
// NG: root が null の時にクラッシュ
cout << root->val;

// OK
if (!root) return;
cout << root->val;
```

### 間違い2: 葉ノードの判定ミス

```cpp
// 葉ノード = 左右の子が両方 null
if (!root->left && !root->right) {
    // これが葉ノード
}
```

### 間違い3: BST の境界条件

```cpp
// NG: int だとオーバーフローの可能性
validate(node, INT_MIN, INT_MAX);

// OK: long を使う
validate(node, LONG_MIN, LONG_MAX);
```
