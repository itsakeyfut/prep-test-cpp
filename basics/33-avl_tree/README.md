# AVL Tree - AVL木

## 概要
AVL木は、**自己平衡二分探索木**の一種です。すべてのノードで「左部分木の高さ − 右部分木の高さ」（**バランス係数**）が -1, 0, 1 のいずれかになるように、挿入のたびに**回転**して形を整えます。これにより、BST の弱点だった「ソート済みデータを入れると一直線になる」問題を防ぎ、常に O(log n) を保証します。

## 目的
- BST がなぜ遅くなるのか、それをどう直すのか（回転）を理解する
- 4種類の回転（LL, RR, LR, RL）を図と一緒に説明できるようにする
- 「高さを持たせて、帰りがけに更新する」という再帰パターンを身につける（木の DP 全般で使う）
- 関連する問題: 110 Balanced Binary Tree、1382 Balance a Binary Search Tree、108 Convert Sorted Array to Binary Search Tree

## 達成条件
- [ ] 何も見ずに main.cpp を25分以内に手書きできる
- [ ] 4つの回転（LL, RR, LR, RL）を図で描いて説明できる
- [ ] バランス係数の符号から、どの回転を使うか判断できる
- [ ] `rotate_right` / `rotate_left` を unique_ptr の move で書ける
- [ ] 1〜7 をソート順に挿入した結果が高さ3の完全二分木になることを説明できる（BST なら高さ7）
- [ ] 挿入・検索が O(log n) になる理由を説明できる
- [ ] LeetCode 110 Balanced Binary Tree を解ける
- [ ] LeetCode 1382 Balance a Binary Search Tree を解ける

## AVL木の動き
4種類の不均衡パターンと回転（数字は値、`bf` はバランス係数）：

```
【LL】左の左に偏る → 右回転          【RR】右の右に偏る → 左回転

      3 (bf=+2)                         1 (bf=-2)
     /                                   \
    2              →     2                2          →     2
   /                    / \                \              / \
  1                    1   3                3            1   3


【LR】左の右に偏る → 左回転 → 右回転   【RL】右の左に偏る → 右回転 → 左回転

    3              3                   1            1
   /              /                     \            \
  1      →       2       →    2          3    →       2      →    2
   \            /            / \        /              \         / \
    2          1            1   3      2                3       1   3
```

1〜7 をソート順に挿入した場合：

```
BST（回転なし）        AVL木
1
 \                        4
  2                     /   \
   \                   2     6
    3      ...        / \   / \
     \               1   3 5   7
      7
高さ 7                高さ 3
```

## コードの解説

### ノード構造（main.cpp:9-18）
```cpp
template <typename T>
struct Node
{
    T value;
    int height = 1;                 // 葉の高さを 1 とする
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};
```
- BST のノードに `height` を追加しただけ

### 高さとバランス係数（main.cpp:27-40）
```cpp
static int height(const NodePtr &node)
{
    return node ? node->height : 0;     // 空の木は高さ 0
}

static int balance_factor(const NodePtr &node)
{
    return node ? height(node->left) - height(node->right) : 0;  // 正なら左が重い
}

static void update_height(NodePtr &node)
{
    node->height = 1 + std::max(height(node->left), height(node->right));
}
```

### 右回転（main.cpp:42-50）
```cpp
static NodePtr rotate_right(NodePtr node)
{
    NodePtr new_root = std::move(node->left);   // 左の子が新しい根
    node->left = std::move(new_root->right);    // 新しい根の右部分木を付け替え
    update_height(node);                        // 下になった方を先に更新
    new_root->right = std::move(node);          // 元の根を右の子にする
    update_height(new_root);
    return new_root;
}
```
```
      node              new_root
      /  \               /    \
 new_root  C    →       A     node
   /  \                       /  \
  A    B                     B    C
```
- `rotate_left`（main.cpp:52-60）は left と right を入れ替えただけ
- 高さは「下になったノード → 上になったノード」の順に更新する

### 再平衡（main.cpp:62-80）
```cpp
static NodePtr rebalance(NodePtr node)
{
    update_height(node);
    int bf = balance_factor(node);

    if (bf > 1)                                       // 左が重い
    {
        if (balance_factor(node->left) < 0)           // LR: 先に左の子を左回転
            node->left = rotate_left(std::move(node->left));
        return rotate_right(std::move(node));         // LL（または LR の2回目）
    }
    if (bf < -1)                                      // 右が重い
    {
        if (balance_factor(node->right) > 0)          // RL: 先に右の子を右回転
            node->right = rotate_right(std::move(node->right));
        return rotate_left(std::move(node));          // RR（または RL の2回目）
    }
    return node;                                      // バランスOK
}
```
- 4ケースを「重い側」×「子の向き」の2段階で判定している

### 挿入（main.cpp:82-97）
```cpp
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
        return;                              // 重複は無視

    node = rebalance(std::move(node));       // 帰りがけに再平衡
}
```
- BST の挿入と同じ流れで、最後に `rebalance` を1行足すだけ
- 再帰の帰りがけに、挿入位置から根に向かって順に高さ更新・回転が行われる

### バランス確認（main.cpp:108-113）
```cpp
static bool is_balanced(const NodePtr &node)
{
    if (!node)
        return true;
    return std::abs(balance_factor(node)) <= 1 &&
           is_balanced(node->left) && is_balanced(node->right);
}
```
- 全ノードでバランス係数が -1〜1 に収まっているかを確認する

## 計算量
- **時間計算量**:
  - 挿入: O(log n)（回転は1回の挿入につき最大2回）
  - 検索: O(log n)
- **空間計算量**: O(n)（ノード数）、再帰スタック O(log n)

## 特徴
- **厳密なバランス**: 高さは最悪でも約 1.44 log n
- **検索が速い**: Red-Black 木より木が低い
- **更新はやや重い**: 回転が多めに起きる

## 使いどころ
- 検索が多く、挿入・削除が少ない用途
- 回転と「帰りがけの高さ更新」の練習（面接では回転の説明を求められることがある）

## 注意点
- 実務・競技では自分で書かず `std::set` / `std::map` を使う
- 削除も同じく `rebalance` を帰りがけに呼べば実装できる（このコードでは省略）
