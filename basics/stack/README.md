# Stack - スタック

## 概要
スタックは、最後に入れたデータを最初に取り出す「後入れ先出し（LIFO: Last In First Out）」のデータ構造です。本を積み重ねるイメージで、一番上の本から取り出します。

## スタックの動き
```
初期状態: [ ]

push(100): [100]
push(200): [100, 200]
push(300): [100, 200, 300]

top(): 300           ← 一番上を確認
pop(): [100, 200]    ← 300が削除される
top(): 200           ← 一番上を確認
```

## コードの解説

### メンバ変数（main.cpp:7-8）
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
- 容量が足りない場合、vectorが自動的に拡張

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
- 空チェックを行い、安全に削除

### top（先頭取得）（main.cpp:24-27）
```cpp
T &top()
{
    return data.back();  // 末尾要素への参照を返す
}
```
- 削除せずに末尾要素を参照
- 参照を返すので、値の変更も可能

### empty/size（main.cpp:29-37）
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
  - push: O(1)（償却）
  - pop: O(1)
  - top: O(1)
- **空間計算量**: O(n)（要素数に比例）

## 特徴
- **LIFO**: 逆順でデータを取り出す
- **高速**: すべての操作がO(1)
- **動的サイズ**: 自動的にサイズが調整される

## 使いどころ
- 関数呼び出しの管理（コールスタック）
- 括弧の対応チェック
- 深さ優先探索（DFS）
- 式の評価（逆ポーランド記法など）
- アンドゥ機能の実装

## 標準ライブラリ
C++では`std::stack`が標準で提供されています。
