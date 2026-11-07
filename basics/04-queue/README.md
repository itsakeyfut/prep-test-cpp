# Queue - キュー

## 概要
キューは、先に入れたデータを先に取り出す「先入れ先出し（FIFO: First In First Out）」のデータ構造です。行列に並ぶイメージで、最初に並んだ人が最初にサービスを受けます。この実装は固定長の配列を**リングバッファ（循環バッファ）**として使い、`head` と `tail` を `%` で回すことで、要素をずらさずにすべての操作を O(1) で行います。

## 目的
- FIFO の性質と、それが「来た順に処理する」「近いものから順に広げる（BFS）」問題に向いている理由を理解する
- 配列の先頭から取り出すと O(n) になる問題を、リングバッファで O(1) にするテクニックを身につける
- `head` / `tail` / `count` の3つで状態を管理する考え方を理解する（満杯と空の区別）
- 幅優先探索（18-bfs_dfs）、トポロジカルソート（23）、スライディングウィンドウの土台にする
- 解ける問題の例: 622 Design Circular Queue、933 Number of Recent Calls、232 Implement Queue using Stacks、225 Implement Stack using Queues

## 達成条件
- [ ] 何も見ずに main.cpp を10分以内に手書きできる
- [ ] `(tail + 1) % capacity` で配列を循環利用できる理由を説明できる
- [ ] `count` を持たない場合、`head == tail` だけでは「空」と「満杯」を区別できない理由を説明できる
- [ ] vector の先頭を erase するキューだと dequeue が O(n) になる理由を説明できる
- [ ] 各操作の計算量を説明できる
- [ ] LeetCode 622. Design Circular Queue を解ける
- [ ] LeetCode 933. Number of Recent Calls を解ける
- [ ] LeetCode 232. Implement Queue using Stacks を解き、償却 O(1) になる理由を説明できる
- [ ] LeetCode 225. Implement Stack using Queues を解ける

## キューの動き
```
初期状態: [ ]

enqueue(10): [10]
enqueue(20): [10, 20]
enqueue(30): [10, 20, 30]

dequeue(): [20, 30]  ← 10が取り出される
front(): 20          ← 先頭の確認
```

### リングバッファの中身（capacity = 3）
```
               data          head tail count
初期:          [  ][  ][  ]    0    0    0
enqueue(10):   [10][  ][  ]    0    1    1
enqueue(20):   [10][20][  ]    0    2    2
enqueue(30):   [10][20][30]    0    0    3   ← tail が末尾を越えて 0 に戻る（満杯）
dequeue():     [  ][20][30]    1    0    2   ← head を進めるだけ
enqueue(40):   [40][20][30]    1    1    3   ← 空いた先頭を再利用
                    ↑head
並び順（論理）: 20 → 30 → 40
```

## コードの解説

### メンバ変数（main.cpp:9-13）
```cpp
std::unique_ptr<T[]> data;  // 配列で実装
std::size_t capacity;       // 容量
std::size_t head;           // 先頭の位置（次に取り出す場所）
std::size_t tail;           // 末尾の位置（次に入れる場所）
std::size_t count;          // 要素数
```
- 配列を使った固定サイズのキュー
- `head`と`tail`でキューの範囲を管理し、`count`で空・満杯を判定

### コンストラクタ（main.cpp:16-21）
```cpp
explicit Queue(std::size_t size)
    : data(std::make_unique<T[]>(size)),
      capacity(size), head(0), tail(0), count(0) {}
```
- 容量を指定して配列を確保する
- `explicit` で `Queue<int> q = 5;` のような暗黙変換を禁止

### enqueue（追加）（main.cpp:23-31）
```cpp
void enqueue(const T &value)
{
    if (count == capacity)
        throw std::overflow_error("Queue overflow");  // 満杯チェック

    data[tail] = value;
    tail = (tail + 1) % capacity;  // 循環バッファ
    ++count;
}
```
- `%`演算子で配列を循環利用（リングバッファ）
- 満杯の場合は例外を投げる

### dequeue（削除）（main.cpp:33-40）
```cpp
void dequeue()
{
    if (empty())
        throw std::underflow_error("Queue underflow");  // 空チェック

    head = (head + 1) % capacity;  // 循環バッファ
    --count;
}
```
- 先頭要素を削除（実際には`head`を進めるだけで、要素はずらさない）

### front（先頭取得）（main.cpp:42-56）
```cpp
T &front()
{
    if (empty())
        throw std::underflow_error("Queue is empty");

    return data[head];  // 先頭要素を返す
}
```
- 削除せずに先頭要素を参照
- const 版の `front()` も用意して、const オブジェクトからも読めるようにする

### empty / size（main.cpp:58-66）
- それぞれ `count == 0`、`count` を返すだけ

## 計算量
- **時間計算量**:
  - enqueue: O(1)
  - dequeue: O(1)
  - front: O(1)
- **空間計算量**: O(n)（容量に比例）

## 特徴
- **FIFO**: 入れた順序が保たれる
- **高速**: すべての操作がO(1)
- **要素をずらさない**: `head` を進めるだけなので、配列の先頭削除のような O(n) が発生しない
- **固定サイズ**: この実装は容量が固定（満杯時に2倍に拡張する実装も可能）

## 使いどころ
- タスクキュー（処理待ちのタスク管理）
- 幅優先探索（BFS）、最短経路（重みなしグラフ）
- メッセージキュー
- バッファリング（データの一時保管、ストリーム処理）
- 「直近 k 件」を保持するスライディングウィンドウ（933）

## 注意点
- `count` を持たない実装では、1マス空けておき「`(tail + 1) % capacity == head` なら満杯」と判定する方法がよく使われる
- dequeue は要素を消さず `head` を進めるだけなので、`std::string` などの中身は次に上書きされるまで残る
- 容量を拡張する場合は、`head` から順に新しい配列の先頭へ詰め直す必要がある（単純コピーだと順序が崩れる）
- `std::queue::pop()` は値を返さない。取り出した値が必要なら先に `front()` で読む

## 標準ライブラリ
C++では`std::queue`が標準で提供されています（内部コンテナはデフォルトで `std::deque`）。両端から操作したい場合は `std::deque`（05-deque）を使います。
