# Red-Black Tree - 赤黒木

## 概要
赤黒木は、各ノードに**赤か黒の色**を持たせ、色に関するルール（不変条件）を守ることでバランスを保つ**自己平衡二分探索木**です。AVL木ほど厳密ではありませんが、回転の回数が少なく、挿入・削除が多い用途に向いています。C++ の `std::map` / `std::set` の内部実装として広く使われています。

### 不変条件（5つのルール）
1. 各ノードは赤か黒
2. **根は黒**
3. 葉（nullptr = NIL）は黒とみなす
4. **赤ノードの子は必ず黒**（赤が連続しない）
5. **どのノードから NIL までの経路も、通る黒ノードの数（黒高さ）が等しい**

→ 最短経路は「黒だけ」、最長経路は「黒と赤が交互」なので、最長は最短の2倍以下。よって高さは O(log n)。

## 目的
- **正直に言うと、このコードを面接で何も見ずに書けるようになることは目的ではありません。** 赤黒木を手書きさせる面接はほぼありません。
- 目的は次の2つです：
  - **5つの不変条件**と、それがなぜ高さ O(log n) を保証するのかを理解する
  - **なぜ `std::map` / `std::set` は AVL木ではなく赤黒木なのか**を説明できるようになる
- その上で、「`std::map` の挿入・検索・削除が O(log n)」「イテレータが順序付きで回る」といった性質を自信を持って使えるようになる

## 達成条件
- [ ] 赤黒木の5つの不変条件を何も見ずに書ける
- [ ] 「最長経路は最短経路の2倍以下」→ 高さ ≤ 2 log(n+1) になる理由を説明できる
- [ ] 挿入時の3ケース（叔父が赤 / 叔父が黒で内側 / 叔父が黒で外側）を図で説明できる
- [ ] AVL木との違い（バランスの厳しさ・回転回数）と、`std::map` が赤黒木を採用する理由を説明できる
- [ ] main.cpp の `is_valid` / `black_height` を自分で書ける（不変条件の確認なので、ここは書けるようにする）
- [ ] （余裕があれば）main.cpp の挿入を見ながら40分程度で再現できる

## 赤黒木の動き
新しいノードは**赤**で挿入します（黒で入れるとルール5が壊れるため）。親が赤だとルール4に違反するので、**叔父（親の兄弟）の色**で場合分けします（親が祖父の左の子の場合）：

```
【Case 1】叔父が赤 → 色の塗り替えのみ（回転なし）

       G(B)                  G(R)  ← 祖父を赤に。G を新しい z として上へ続く
      /    \                /    \
    P(R)   U(R)    →     P(B)   U(B)
    /                    /
  z(R)                 z(R)


【Case 2】叔父が黒、z が内側（親の右の子）→ 親で左回転して Case 3 へ

       G(B)                 G(B)
      /    \               /    \
    P(R)   U(B)   →     z(R)   U(B)
       \                /
       z(R)           P(R)   ← 元の P を新しい z として Case 3 へ


【Case 3】叔父が黒、z が外側（親の左の子）→ 親と祖父の色を入れ替えて祖父で右回転

       G(B)                 P(B)
      /    \               /    \
    P(R)   U(B)   →     z(R)    G(R)
    /                              \
  z(R)                             U(B)
```

親が祖父の右の子の場合は、左右をすべて反転します。

1〜10 をソート順に挿入した結果（main.cpp の出力と一致）：

```
              4(B)
           /        \
        2(B)          6(B)
       /    \        /    \
     1(B)  3(B)   5(B)    8(R)
                         /    \
                       7(B)   9(B)
                                 \
                                 10(R)

黒高さ（NIL を1と数える）: 4 → 2 → 1 → NIL = 4
```

## コードの解説

### ノード構造（main.cpp:4-19）
```cpp
enum class Color { Red, Black };

struct Node
{
    int value;
    Color color = Color::Red;   // 新しいノードは赤
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;     // 祖父・叔父をたどるために親ポインタが必要
};
```
- 親ポインタがあるため `unique_ptr` ではなく生ポインタを使い、デストラクタで解放する

### 左回転（main.cpp:26-41）
```cpp
void rotate_left(Node *x)
{
    Node *y = x->right;           // y が x の位置に上がる
    x->right = y->left;           // y の左部分木を x の右へ
    if (y->left)
        y->left->parent = x;
    y->parent = x->parent;        // y を x の親につなぐ
    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;                  // x を y の左の子に
    x->parent = y;
}
```
- AVL木の回転と同じ形だが、**親ポインタの付け替え**が増える
- `rotate_right`（main.cpp:43-58）は left と right を入れ替えただけ

### 挿入後の修正 fix_insert（main.cpp:60-115）
```cpp
while (z->parent && z->parent->color == Color::Red)   // 赤-赤違反がある間
{
    Node *parent = z->parent;
    Node *grand = parent->parent;     // 親が赤 → 親は根ではない → 祖父は必ず存在

    if (parent == grand->left)
    {
        Node *uncle = grand->right;
        if (uncle && uncle->color == Color::Red)      // Case 1: 塗り替え
        {
            parent->color = Color::Black;
            uncle->color = Color::Black;
            grand->color = Color::Red;
            z = grand;                                // 祖父で再チェック
        }
        else
        {
            if (z == parent->right)                   // Case 2: 内側 → 外側にする
            {
                z = parent;
                rotate_left(z);
                parent = z->parent;
            }
            parent->color = Color::Black;             // Case 3: 外側
            grand->color = Color::Red;
            rotate_right(grand);
        }
    }
    else
    {
        // 左右を反転した同じ処理（main.cpp:90-113）
    }
}
root->color = Color::Black;                           // ルール2を必ず守る
```
- Case 1 は上に伝播する可能性がある（O(log n) 回）が、回転（Case 2, 3）は1回の挿入で最大2回

### 挿入 insert（main.cpp:161-186）
```cpp
void insert(int value)
{
    Node *parent = nullptr;
    Node *cur = root;
    while (cur)                          // 通常の BST と同じく挿入位置を探す
    {
        parent = cur;
        if (value < cur->value)
            cur = cur->left;
        else if (value > cur->value)
            cur = cur->right;
        else
            return;                      // 重複は無視
    }

    Node *node = new Node(value);        // 赤ノードとして作成
    node->parent = parent;
    if (!parent)
        root = node;
    else if (value < parent->value)
        parent->left = node;
    else
        parent->right = node;

    fix_insert(node);                    // ルールを修復
}
```

### 不変条件の検証（main.cpp:117-131, 194-199）
```cpp
static int black_height(const Node *node)
{
    if (!node)
        return 1;                                   // NIL は黒
    if (node->color == Color::Red &&
        ((node->left && node->left->color == Color::Red) ||
         (node->right && node->right->color == Color::Red)))
        return -1;                                  // ルール4違反（赤-赤）

    int lh = black_height(node->left);
    int rh = black_height(node->right);
    if (lh == -1 || rh == -1 || lh != rh)
        return -1;                                  // ルール5違反（黒高さ不一致）
    return lh + (node->color == Color::Black ? 1 : 0);
}

bool is_valid() const
{
    if (root && root->color != Color::Black)
        return false;                               // ルール2違反
    return black_height(root) != -1;
}
```
- 1回の後順走査で「赤-赤なし」と「黒高さが等しい」を同時にチェックする
- -1 を「違反」のシグナルとして上に伝える（110 Balanced Binary Tree と同じテクニック）

### メモリ解放（main.cpp:142-149, 156-159）
```cpp
static void destroy(Node *node)
{
    if (!node)
        return;
    destroy(node->left);
    destroy(node->right);
    delete node;            // 子を消してから自分を消す（後順）
}
```
- コピーすると二重解放になるので、コピーコンストラクタ・代入は `= delete` にしている

## 計算量
- **時間計算量**:
  - 挿入: O(log n)（回転は最大2回、塗り替えは O(log n) 回）
  - 検索: O(log n)
  - 削除: O(log n)（このコードでは省略、回転は最大3回）
- **空間計算量**: O(n)

## 特徴
- **ゆるいバランス**: 高さ ≤ 2 log(n+1)（AVL は約 1.44 log n）
- **回転が少ない**: 挿入で最大2回、削除で最大3回（AVL の削除は O(log n) 回の回転が起こりうる）
- **色1ビットで済む**: 高さ（int）を持つ AVL より省メモリ

## なぜ std::map は赤黒木なのか
| 項目 | AVL木 | 赤黒木 |
| ---- | ----- | ------ |
| 高さ | 約 1.44 log n（低い） | ≤ 2 log n（やや高い） |
| 検索 | やや速い | やや遅い |
| 挿入・削除の回転回数 | 多い（削除は O(log n)） | 少ない（定数回） |
| 追加情報 | 高さ | 色（1ビット） |

- 汎用のコンテナは挿入・削除・検索がバランスよく行われるため、**更新コストが定数回の回転に抑えられる赤黒木**が選ばれている
- 検索のみが極端に多いなら AVL の方が有利な場合もある

## 使いどころ
- 実装するのではなく、`std::map` / `std::set` / `std::multiset` として使う
- LeetCode では「順序付き集合で lower_bound したい」問題（220 Contains Duplicate III、352 Data Stream as Disjoint Intervals、715 Range Module など）で `std::set` / `std::map` を使う＝赤黒木を使っている

## 注意点
- 削除は場合分けがさらに多く（4ケース × 左右）、学習コストに見合わないので省略している
- 生ポインタを使うので、デストラクタでの解放とコピー禁止を忘れない
