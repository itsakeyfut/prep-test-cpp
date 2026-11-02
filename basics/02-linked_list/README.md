# Linked List - 単方向連結リスト

## 概要
単方向連結リストは、各ノードが「値」と「次のノードへのポインタ」を持ち、それを鎖のようにつないだデータ構造です。配列と違って要素がメモリ上に連続して並んでいないため、ランダムアクセスはできませんが、ポインタの付け替えだけで挿入・削除ができます。

## 目的
- LeetCode の連結リスト問題（反転・マージ・サイクル検出・中央探索など）はポインタ操作そのものが問われるため、手で書けることが必須
- fast/slow ポインタ（ウサギとカメ）や「ダミーヘッド」「ポインタへのポインタ」といったテクニックの土台になる
- LRU Cache、ハッシュマップのチェイン法、グラフの隣接リストなど、他のデータ構造の部品として頻出

## 達成条件
- [ ] 何も見ずに main.cpp を15分以内に手書きできる
- [ ] `reverse` を prev / cur / next の3変数で、図を描かずに書ける
- [ ] `std::unique_ptr<Node<T>> *cur`（ポインタへのポインタ）を使うと先頭の特別扱いが不要になる理由を説明できる
- [ ] fast/slow ポインタで中央ノードが求まる理由を説明できる
- [ ] 各操作の計算量（push_front O(1)、push_back O(n)、find O(n) など）を説明できる
- [ ] LeetCode 206. Reverse Linked List を解ける
- [ ] LeetCode 21. Merge Two Sorted Lists を解ける
- [ ] LeetCode 876. Middle of the Linked List を解ける
- [ ] LeetCode 141. Linked List Cycle を解ける
- [ ] LeetCode 19. Remove Nth Node From End of List を解ける

## 連結リストの動き
```
push_back(2), push_back(3):   head -> [2] -> [3] -> null
push_front(1):                head -> [1] -> [2] -> [3] -> null
push_back(5):                 head -> [1] -> [2] -> [3] -> [5] -> null
insert(3, 4):                 head -> [1] -> [2] -> [3] -> [4] -> [5] -> null

remove(3):  [2] の next を [3] の next に付け替える
            head -> [1] -> [2] ---------> [4] -> [5] -> null

reverse():  矢印の向きを1つずつ逆にする
  prev=null  head=[1]->[2]->[4]->[5]
  prev=[1]   head=[2]->[4]->[5]
  prev=[2]->[1]   head=[4]->[5]
  prev=[4]->[2]->[1]   head=[5]
  prev=[5]->[4]->[2]->[1]   head=null  → head = prev

middle():  slow は1歩、fast は2歩
  [1] [2] [3] [4] [5]
   s   f                 開始
       s       f
           s           f(末尾)  → slow = 3
```

## コードの解説

### ノード構造（main.cpp:4-11）
```cpp
template <typename T>
struct Node
{
    T value;                     // ノードの値
    std::unique_ptr<Node> next;  // 次のノード（所有権を持つ）
};
```
- 各ノードが次のノードを所有するので、`head` を消すと連鎖的に全ノードが解放される

### メンバ変数とデストラクタ（main.cpp:16-25）
```cpp
std::unique_ptr<Node<T>> head;  // 先頭ノード
std::size_t count = 0;          // 要素数

~LinkedList()
{
    while (head)
        head = std::move(head->next);  // 1つずつ解放
}
```
- デフォルトのデストラクタだと再帰的に解放され、長いリストでスタックオーバーフローする可能性があるため、ループで解放する

### push_front（main.cpp:27-33）
```cpp
auto node = std::make_unique<Node<T>>(value);
node->next = std::move(head);  // 新ノード → 旧先頭
head = std::move(node);        // 先頭を新ノードに
++count;
```
- O(1)。連結リストが最も得意な操作

### push_back（main.cpp:35-42）
```cpp
std::unique_ptr<Node<T>> *cur = &head;  // 「次を指すポインタ」へのポインタ
while (*cur)
    cur = &(*cur)->next;                // 末尾の null まで進む
*cur = std::make_unique<Node<T>>(value);
```
- `cur` は「ノード」ではなく「ノードを指す unique_ptr の場所」を指す
- 空リストでも `cur == &head` となるので特別扱いが不要
- tail ポインタを持たないので O(n)

### insert（main.cpp:44-58）
```cpp
if (index > count)
    return false;                       // 範囲外

std::unique_ptr<Node<T>> *cur = &head;
for (std::size_t i = 0; i < index; ++i)
    cur = &(*cur)->next;                // index 番目の場所へ

auto node = std::make_unique<Node<T>>(value);
node->next = std::move(*cur);           // 新ノード → 元の index 番目
*cur = std::move(node);                 // 前の next を新ノードに
```
- index == 0 なら push_front、index == count なら push_back と同じ動きになる

### remove（main.cpp:60-72）
```cpp
std::unique_ptr<Node<T>> *cur = &head;
while (*cur && (*cur)->value != value)
    cur = &(*cur)->next;                // 削除対象の場所を探す

if (!*cur)
    return false;                       // 見つからない

*cur = std::move((*cur)->next);         // 対象を飛ばして付け替え（対象は自動解放）
```
- ポインタへのポインタのおかげで「先頭を消す場合」の分岐が不要

### find（main.cpp:74-82）
```cpp
for (Node<T> *cur = head.get(); cur; cur = cur->next.get())
{
    if (cur->value == value)
        return true;
}
return false;
```
- 読むだけなので生ポインタ（`get()`）で走査する

### reverse（main.cpp:84-95）
```cpp
std::unique_ptr<Node<T>> prev;                              // 反転済みの先頭
while (head)
{
    std::unique_ptr<Node<T>> next = std::move(head->next);  // 次を退避
    head->next = std::move(prev);                           // 矢印を逆向きに
    prev = std::move(head);                                 // prev を1つ進める
    head = std::move(next);                                 // head を1つ進める
}
head = std::move(prev);
```
- 「退避 → 付け替え → prev 前進 → cur 前進」の4行を丸暗記する
- LeetCode 206 そのもの

### middle（main.cpp:97-107）
```cpp
Node<T> *slow = head.get();
Node<T> *fast = head.get();
while (fast && fast->next)
{
    slow = slow->next.get();        // 1歩
    fast = fast->next->next.get();  // 2歩
}
return slow ? &slow->value : nullptr;
```
- fast が末尾に着いたとき slow はちょうど半分の位置
- 偶数個のときは後ろ側の中央を返す（LeetCode 876 と同じ）

### print（main.cpp:114-119）
- `1 -> 2 -> 3 -> null` の形式で出力

## 計算量
- **時間計算量**:
  - push_front: O(1)
  - push_back: O(n)（tail ポインタを持てば O(1)）
  - insert / remove / find: O(n)
  - reverse: O(n)
  - middle: O(n)
- **空間計算量**: O(n)（reverse / middle の追加領域は O(1)）

## 特徴
- **先頭への挿入・削除が O(1)**: 配列のように要素をずらす必要がない
- **ランダムアクセス不可**: i 番目に行くには先頭からたどる必要がある
- **キャッシュ効率が悪い**: ノードがメモリ上でバラバラ

## 使いどころ
- 先頭・途中への挿入削除が多い場合
- LRU Cache などで「ノードを O(1) で付け替えたい」場合（双方向リスト）
- スタックの実装

## 注意点
- 実装ではダミーヘッド（番兵）を使う書き方もよく使われる。LeetCode では `ListNode dummy(0); dummy.next = head;` が定番
- LeetCode の `ListNode` は生ポインタなので、本番では `unique_ptr` ではなく生ポインタで書く練習もしておく

## 標準ライブラリ
C++では`std::forward_list`（単方向）と`std::list`（双方向）が提供されています。
