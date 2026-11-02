# Deque - 両端キュー（リングバッファ実装）

## 概要
Deque（Double-Ended Queue、「デック」と読む）は、先頭と末尾の両方から O(1) で追加・削除ができるキューです。この実装ではリングバッファ（配列の終わりと始まりをつなげて輪のように使う）で作り、満杯になったら2倍の配列に拡張します。queue/main.cpp の固定長リングバッファに「前への追加」と「自動拡張」を足したものです。

## 目的
- LeetCode の「スライディングウィンドウの最大値」に代表される **単調キュー（monotonic deque）** のパターンを使えるようにする
- 0-1 BFS（辺の重みが 0 か 1 の最短路）で deque を使う理由を理解する
- リングバッファの添字計算（特に「1つ前」に戻る `(head + cap - 1) % cap`）を手で書けるようにする
- スタックとキューの両方として使えるので、BFS / DFS / 回文判定など応用範囲が広い

## 達成条件
- [ ] 何も見ずに main.cpp を15分以内に手書きできる
- [ ] `head` と `count` から末尾位置 `(head + count - 1) % cap` を求められる
- [ ] push_front で `head - 1` ではなく `(head + cap - 1) % cap` と書く理由（size_t のアンダーフロー）を説明できる
- [ ] grow で要素を `head` から順に新配列の 0 番目以降へ並べ直す理由を説明できる
- [ ] 各操作の計算量（push は償却 O(1)）を説明できる
- [ ] LeetCode 239. Sliding Window Maximum を解ける
- [ ] LeetCode 641. Design Circular Deque を解ける
- [ ] LeetCode 1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit を解ける
- [ ] LeetCode 862. Shortest Subarray with Sum at Least K を解ける

## Dequeの動き
```
容量 2 で開始。h = head

push_back(2):   [2][ ]       h=0 count=1
push_back(3):   [2][3]       h=0 count=2
push_front(1):  満杯 → grow（容量 4、h から順に詰め直す）
                [2][3][ ][ ] h=0
                h を1つ戻す (0 + 4 - 1) % 4 = 3
                [2][3][ ][1] h=3 count=3     論理順: 1 2 3
push_front(0):  h = 2
                [2][3][0][1] h=2 count=4     論理順: 0 1 2 3
push_back(4):   満杯 → grow（容量 8）
                [0][1][2][3][ ][ ][ ][ ] h=0  ← 論理順に並べ直される
                [0][1][2][3][4][ ][ ][ ] count=5

front() = data[h] = 0
back()  = data[(h + count - 1) % cap] = 4

pop_front(): h を1つ進める   → 論理順: 1 2 3 4
pop_back():  count を1減らす → 論理順: 1 2 3
```

## コードの解説

### メンバ変数（main.cpp:8-12）
```cpp
std::unique_ptr<T[]> data;  // リングバッファ本体
std::size_t cap;            // 容量
std::size_t head;           // 先頭の位置
std::size_t count;          // 要素数
```
- `tail` は持たず、`(head + count) % cap` で計算する（変数が少ないほうがバグりにくい）

### grow（拡張）（main.cpp:14-23）
```cpp
std::size_t new_cap = cap * 2;
auto new_data = std::make_unique<T[]>(new_cap);
for (std::size_t i = 0; i < count; ++i)
    new_data[i] = std::move(data[(head + i) % cap]); // 論理順に 0 から詰める
data = std::move(new_data);
cap = new_cap;
head = 0;                                            // 先頭は 0 番目になる
```
- 単純に memcpy すると、輪が途中で折り返している部分の順序が壊れるため、論理順に並べ直す

### コンストラクタ（main.cpp:26-30）
- 初期容量を受け取る（デフォルト 4）。0 を渡すと `% 0` になるので 1 以上を前提とする

### push_back（main.cpp:32-38）
```cpp
if (count == cap)
    grow();
data[(head + count) % cap] = value;  // 末尾の次の位置
++count;
```

### push_front（main.cpp:40-47）
```cpp
if (count == cap)
    grow();
head = (head + cap - 1) % cap;  // head を1つ戻す（0 なら cap-1 へ折り返す）
data[head] = value;
++count;
```
- `head - 1` だと head が 0 のとき size_t がアンダーフローして巨大な値になる。`+ cap` してから割るのが定番

### pop_front（main.cpp:49-55）
```cpp
if (empty())
    throw std::underflow_error("Deque is empty");
head = (head + 1) % cap;  // 先頭を1つ進める
--count;
```

### pop_back（main.cpp:57-62）
```cpp
if (empty())
    throw std::underflow_error("Deque is empty");
--count;  // 末尾は head + count から決まるので count を減らすだけ
```

### front / back（main.cpp:64-76）
```cpp
return data[head];                      // front
return data[(head + count - 1) % cap];  // back
```

## 計算量
- **時間計算量**:
  - push_front / push_back: 償却 O(1)（grow が起きる瞬間だけ O(n)）
  - pop_front / pop_back: O(1)
  - front / back: O(1)
- **空間計算量**: O(n)

## 特徴
- **両端が O(1)**: キューとしてもスタックとしても使える
- **ランダムアクセスも O(1)**: `data[(head + i) % cap]` で i 番目に行ける
- **途中への挿入は O(n)**

## 使いどころ
- 単調キュー（スライディングウィンドウの最大値・最小値）
- 0-1 BFS（重み 0 の辺は前に、重み 1 の辺は後ろに push）
- 回文チェック（両端から取り出して比較）
- Undo 履歴（古いものを前から捨てる）

## 注意点
- `std::deque` はリングバッファではなく「固定長ブロックの配列」で実装されており、拡張時に既存要素を動かさない（参照が無効にならない）
- 単調キューでは値ではなく **添字** を入れておくと、ウィンドウから外れたかの判定がしやすい

## 標準ライブラリ
C++では`std::deque`が標準で提供されています。
