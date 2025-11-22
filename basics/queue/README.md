# Queue - キュー

## 概要
キューは、先に入れたデータを先に取り出す「先入れ先出し（FIFO: First In First Out）」のデータ構造です。行列に並ぶイメージで、最初に並んだ人が最初にサービスを受けます。

## キューの動き
```
初期状態: [ ]

enqueue(10): [10]
enqueue(20): [10, 20]
enqueue(30): [10, 20, 30]

dequeue(): [20, 30]  ← 10が取り出される
front(): 20          ← 先頭の確認
```

## コードの解説

### メンバ変数（main.cpp:8-13）
```cpp
std::unique_ptr<T[]> data;  // 配列で実装
std::size_t capacity;       // 容量
std::size_t head;           // 先頭の位置
std::size_t tail;           // 末尾の位置
std::size_t count;          // 要素数
```
- 配列を使った固定サイズのキュー
- `head`と`tail`でキューの範囲を管理

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
- 先頭要素を削除（実際には`head`を進めるだけ）

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

## 計算量
- **時間計算量**:
  - enqueue: O(1)
  - dequeue: O(1)
  - front: O(1)
- **空間計算量**: O(n)（容量に比例）

## 特徴
- **FIFO**: 順序が保証される
- **高速**: すべての操作がO(1)
- **固定サイズ**: この実装は容量が固定（動的に拡張する実装も可能）

## 使いどころ
- タスクキュー（処理待ちのタスク管理）
- 幅優先探索（BFS）
- メッセージキュー
- バッファリング（データの一時保管）

## 標準ライブラリ
C++では`std::queue`が標準で提供されています。
