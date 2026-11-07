# Stack - スタック

## 概要
スタックは、最後に入れたデータを最初に取り出す「後入れ先出し（LIFO: Last In First Out）」のデータ構造です。本を積み重ねるイメージで、一番上の本から取り出します。この実装は内部に `std::vector` を使い、vector の末尾をスタックの top とみなします。

## 目的
- LIFO の性質と、それが「直前の状態に戻る」「入れ子を扱う」問題に向いている理由を理解する
- 動的配列の末尾操作（push_back / pop_back）だけでスタックが作れることを理解する
- 括弧の対応、逆ポーランド記法、DFS、単調スタック（19-monotonic_stack）などの土台にする
- 解ける問題の例: 20 Valid Parentheses、155 Min Stack、150 Evaluate Reverse Polish Notation、844 Backspace String Compare

## 達成条件
- [ ] 何も見ずに main.cpp を5分以内に手書きできる
- [ ] なぜ vector の「先頭」ではなく「末尾」を top にするのか説明できる（先頭操作は O(n)）
- [ ] push が「償却」O(1) である理由を説明できる（01-dynamic_array の再確保）
- [ ] 空のスタックで top() を呼ぶと未定義動作になる理由を説明できる
- [ ] 各操作の計算量を説明できる
- [ ] LeetCode 20. Valid Parentheses を解ける
- [ ] LeetCode 155. Min Stack を解ける
- [ ] LeetCode 150. Evaluate Reverse Polish Notation を解ける
- [ ] LeetCode 844. Backspace String Compare をスタックで解ける

## スタックの動き
```
初期状態: [ ]

push(100): [100]
push(200): [100, 200]
push(300): [100, 200, 300]
                      ↑ top（vector の末尾）

top(): 300           ← 一番上を確認
pop(): [100, 200]    ← 300が削除される
top(): 200           ← 一番上を確認
```

## コードの解説

### メンバ変数（main.cpp:8）
```cpp
std::vector<T> data;  // 内部はvectorで実装
```
- `std::vector`を使った動的サイズのスタック
- vectorが自動的にメモリを管理

### push（追加）（main.cpp:11-14）
```cpp
void push(const T &value)
{
    data.push_back(value);  // 末尾に追加
}
```
- `push_back`で末尾に要素を追加
- 容量が足りない場合、vectorが自動的に拡張（償却 O(1)）

### pop（削除）（main.cpp:16-22）
```cpp
void pop()
{
    if (!data.empty())
    {
        data.pop_back();  // 末尾を削除
    }
}
```
- `pop_back`で末尾の要素を削除
- 空のときは何もしない（例外は投げない）

### top（先頭取得）（main.cpp:24-27）
```cpp
T &top()
{
    return data.back();  // 末尾要素への参照を返す
}
```
- 削除せずに末尾要素を参照
- 参照を返すので、値の変更も可能
- 空チェックはしていない（呼ぶ側が `empty()` を確認する前提）

### empty / size（main.cpp:29-37）
```cpp
bool empty() const
{
    return data.empty();  // 空かどうか
}

std::size_t size() const
{
    return data.size();   // 要素数
}
```
- vectorの機能をそのまま利用

## 計算量
- **時間計算量**:
  - push: 償却 O(1)（再確保が起きる瞬間だけ O(n)）
  - pop: O(1)
  - top: O(1)
- **空間計算量**: O(n)（要素数に比例）

## 特徴
- **LIFO**: 入れた順の逆順でデータを取り出す
- **高速**: すべての操作がO(1)
- **動的サイズ**: 自動的にサイズが調整される
- **アクセス制限**: top 以外の要素には触れない（その制限が問題をシンプルにする）

## 使いどころ
- 関数呼び出しの管理（コールスタック）
- 括弧の対応チェック
- 深さ優先探索（DFS）を再帰なしで書く
- 式の評価（逆ポーランド記法など）
- アンドゥ機能の実装
- 単調スタック（次に大きい要素を探す問題など）

## 注意点
- 空のスタックで `top()` を呼ぶと `data.back()` が未定義動作になる（`std::stack` も同じ）
- この実装の `pop()` は空なら黙って無視するが、`std::stack::pop()` は空で呼ぶと未定義動作
- `std::stack::pop()` は値を返さない。取り出した値が必要なら先に `top()` で読む
- 再帰の深さが大きい DFS はスタックオーバーフローの危険があるので、明示的なスタックに書き換える

## 標準ライブラリ
C++では`std::stack`が標準で提供されています（内部コンテナはデフォルトで `std::deque`）。LeetCode では `std::vector` をそのままスタックとして使うことも多いです。
