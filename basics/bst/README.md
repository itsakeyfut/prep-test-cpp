# BST - 二分探索木 (Binary Search Tree)

## 概要
二分探索木は、各ノードが最大2つの子（左と右）を持ち、左の子は親より小さく、右の子は親より大きいという性質を持つ木構造です。効率的な検索・挿入・削除が可能です。

## BSTの動き
値を挿入すると、自動的にソートされた構造が維持されます：

```
10, 5, 15, 3, 7 を挿入した場合

      10
     /  \
    5    15
   / \
  3   7
```

左側はすべて親より小さく、右側はすべて親より大きくなります。

## コードの解説

### ノード構造（main.cpp:5-13）
```cpp
template <typename T>
struct Node
{
    T value;                      // ノードの値
    std::unique_ptr<Node> left;   // 左の子
    std::unique_ptr<Node> right;  // 右の子
};
```
- `std::unique_ptr`で自動メモリ管理

### 挿入処理（main.cpp:21-35）
```cpp
void insert(std::unique_ptr<Node<T>> &node, const T &value)
{
    if (!node)
    {
        node = std::make_unique<Node<T>>(value);  // 空ならノード作成
    }
    else if (value < node->value)
    {
        insert(node->left, value);  // 小さければ左へ
    }
    else if (value > node->value)
    {
        insert(node->right, value); // 大きければ右へ
    }
}
```
- 再帰的に適切な位置を探して挿入
- 同じ値は挿入しない（重複を許可しない実装）

### 検索処理（main.cpp:37-44）
```cpp
bool find(const std::unique_ptr<Node<T>> &node, const T &value) const
{
    if (!node)
        return false;              // ノードがなければ見つからない
    if (value == node->value)
        return true;               // 見つかった
    return value < node->value ?
        find(node->left, value) :  // 小さければ左を探す
        find(node->right, value);  // 大きければ右を探す
}
```
- 三項演算子を使った簡潔な実装
- 二分探索と同じアルゴリズム

### 中順走査（main.cpp:46-53）
```cpp
void in_order(const std::unique_ptr<Node<T>> &node,
              const std::function<void(const T &)> &visit) const
{
    if (!node)
        return;
    in_order(node->left, visit);   // 左を訪問
    visit(node->value);            // 現在のノードを訪問
    in_order(node->right, visit);  // 右を訪問
}
```
- 左→親→右の順で訪問すると、昇順にデータを取得できる
- コールバック関数で柔軟な処理が可能

## 計算量
- **時間計算量**:
  - 平均: O(log n)（挿入、検索、削除）
  - 最悪: O(n)（木が一直線になった場合）
- **空間計算量**: O(n)（ノード数に比例）

## 特徴
- **ソート済み**: 中順走査で昇順に取得できる
- **動的**: サイズが可変で、挿入・削除が容易
- **バランス注意**: 挿入順序によっては効率が低下

## 使いどころ
- 動的なソート済みデータの管理
- 範囲検索が必要な場合
- 辞書やマップの実装（標準ライブラリの内部実装）
- 優先度付きキューの実装

## 改善版
実用では、バランスを保つAVL木やRed-Black木が使われます。
