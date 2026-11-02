# Tree Traversal - 二分木の走査

## 概要
木の走査とは、木のすべてのノードを決まった順番で1回ずつ訪問することです。深さ優先（DFS）の前順・中順・後順と、幅優先（BFS）のレベル順があります。DFS は再帰でもスタックを使った反復でも書けます。

## 目的
- 木の問題の大半は「どの順番で走査して、各ノードで何をするか」に帰着する。その土台を作る
- 再帰とスタックの対応関係（再帰 = 暗黙のコールスタック）を理解する
- BFS をキューで書けるようにし、「レベルごとの処理」パターンを身につける

## 達成条件
- [ ] 何も見ずに main.cpp を20分以内に手書きできる
- [ ] 図の木について、前順・中順・後順・レベル順の出力を手で書ける
- [ ] 前順の反復版で「右を先に push する」理由を説明できる
- [ ] 後順の反復版が「根→右→左」を反転して得られる理由を説明できる
- [ ] レベル順で `q.size()` を先に保存する理由を説明できる
- [ ] LeetCode 144. Binary Tree Preorder Traversal を解ける
- [ ] LeetCode 94. Binary Tree Inorder Traversal を解ける
- [ ] LeetCode 145. Binary Tree Postorder Traversal を解ける
- [ ] LeetCode 102. Binary Tree Level Order Traversal を解ける
- [ ] LeetCode 104. Maximum Depth of Binary Tree を解ける
- [ ] LeetCode 199. Binary Tree Right Side View を解ける

## 走査の動き
main で作る木：

```
          1
        /   \
       2     3
      / \     \
     4   5     6
```

| 走査 | 順番 | 結果 |
|------|------|------|
| 前順 (preorder) | 根 → 左 → 右 | 1 2 4 5 3 6 |
| 中順 (inorder) | 左 → 根 → 右 | 4 2 5 1 3 6 |
| 後順 (postorder) | 左 → 右 → 根 | 4 5 2 6 3 1 |
| レベル順 (level order) | 上の段から左→右 | [1] [2 3] [4 5 6] |

前順の反復版のスタックの変化：

```
pop 1 → push 3, 2   stack: [3, 2]     out: 1
pop 2 → push 5, 4   stack: [3, 5, 4]  out: 1 2
pop 4               stack: [3, 5]     out: 1 2 4
pop 5               stack: [3]        out: 1 2 4 5
pop 3 → push 6      stack: [6]        out: 1 2 4 5 3
pop 6               stack: []         out: 1 2 4 5 3 6
```

## コードの解説

### ノード構造（main.cpp:8-15）
```cpp
struct Node
{
    int value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    explicit Node(int val) : value(val) {}
};
```
- 走査関数は所有権を持たないので `const Node *`（`.get()`）で受け取る

### 再帰版 前順・中順・後順（main.cpp:17-42）
```cpp
void preorder(const Node *node, std::vector<int> &out)
{
    if (!node)
        return;
    out.push_back(node->value);        // 根
    preorder(node->left.get(), out);   // 左
    preorder(node->right.get(), out);  // 右
}
```
- 3つとも同じ形で、`push_back` の位置（前・間・後）だけが違う

### 反復版 前順（main.cpp:44-62）
```cpp
std::stack<const Node *> st;
st.push(root);
while (!st.empty())
{
    const Node *node = st.top();
    st.pop();
    out.push_back(node->value);
    if (node->right)
        st.push(node->right.get());   // 右を先に積む
    if (node->left)
        st.push(node->left.get());    // 左が先に取り出される
}
```
- スタックは後入れ先出しなので、左を先に処理したいなら右を先に push

### 反復版 中順（main.cpp:64-82）
```cpp
const Node *cur = root;
while (cur || !st.empty())
{
    while (cur)
    {
        st.push(cur);
        cur = cur->left.get();        // 左端まで降りる
    }
    cur = st.top();
    st.pop();
    out.push_back(cur->value);        // 左がなくなったら訪問
    cur = cur->right.get();           // 右部分木へ
}
```
- BST の中順走査はソート順になる（LC 230. Kth Smallest Element in a BST に使える）

### 反復版 後順（main.cpp:84-103）
```cpp
while (!st.empty())
{
    const Node *node = st.top();
    st.pop();
    out.push_back(node->value);
    if (node->left)
        st.push(node->left.get());    // 前順と逆に左を先に積む
    if (node->right)
        st.push(node->right.get());
}
std::reverse(out.begin(), out.end()); // 根→右→左 を反転 = 左→右→根
```

### レベル順（main.cpp:105-129）
```cpp
std::queue<const Node *> q;
q.push(root);
while (!q.empty())
{
    std::size_t size = q.size();      // この段のノード数を固定
    std::vector<int> level;
    for (std::size_t i = 0; i < size; ++i)
    {
        const Node *node = q.front();
        q.pop();
        level.push_back(node->value);
        if (node->left)
            q.push(node->left.get());  // 次の段を積む
        if (node->right)
            q.push(node->right.get());
    }
    levels.push_back(level);
}
```
- ループ中にキューのサイズが変わるので、先に `size` を保存しておく

### 最大深さ（main.cpp:131-136）
```cpp
int max_depth(const Node *node)
{
    if (!node)
        return 0;                       // 空の木の深さは 0
    return 1 + std::max(max_depth(node->left.get()), max_depth(node->right.get()));
}
```
- 後順の考え方（子の結果を使って親の答えを作る）

## 計算量
- **時間計算量**: すべて O(n)（各ノードを1回ずつ訪問）
- **空間計算量**:
  - DFS（再帰・反復）: O(h)（h は木の高さ。偏った木では O(n)）
  - BFS: O(w)（w は最大の幅。完全二分木では O(n/2)）

## 特徴
- **前順**: 親を先に処理する。木のコピー・シリアライズ向き
- **中順**: BST ではソート順になる
- **後順**: 子を先に処理する。高さ・削除・部分木の集計向き
- **レベル順**: 根に近い順。最短距離・段ごとの処理向き

## 使いどころ
- 木の高さ・ノード数・パスの和などの集計
- BST の検証（中順が昇順か、LC 98）
- 木のシリアライズ / デシリアライズ（LC 297）
- 右から見た図・ジグザグ走査（BFS の応用）

## 注意点
- 反復版は `nullptr` を push しないように子の存在を確認する
- 偏った木で再帰が深くなるとスタックオーバーフローの可能性がある
- レベル順で `q.size()` をループ条件に直接書くと段の区切りが崩れる
