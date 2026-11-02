# LRU Cache - LRUキャッシュ

## 概要
LRU（Least Recently Used）キャッシュは、容量がいっぱいになったら「最も長い間使われていないもの」から捨てるキャッシュです。get / put をどちらも O(1) で実現するために、**ハッシュマップ**（キー → ノードの位置）と **双方向連結リスト**（使われた順の並び）を組み合わせます。LeetCode 146 そのもので、設計問題として面接で非常によく出ます。

## 目的
- 「2つのデータ構造を組み合わせて、それぞれの弱点を補う」という設計の考え方を身につける
  - ハッシュマップ: 検索 O(1) だが順序がない
  - 双方向リスト: 順序を持ち、ノードの移動・削除が O(1) だが検索が O(n)
- `std::list::splice` でノードを O(1) で移動する方法と、`std::list` のイテレータが無効化されない性質を理解する
- LFU Cache など、発展的なキャッシュ設計問題の土台

## 達成条件
- [ ] 何も見ずに main.cpp を10分以内に手書きできる
- [ ] ハッシュマップだけ、リストだけでは O(1) にならない理由を説明できる
- [ ] 単方向ではなく双方向リストが必要な理由を説明できる（途中のノードを O(1) で外すには前のノードが要る）
- [ ] リストに key も保存する理由を説明できる（追い出すときにマップからも消すため）
- [ ] `splice` の引数の意味と、splice してもイテレータが有効なままである理由を説明できる
- [ ] get / put の計算量を説明できる
- [ ] LeetCode 146. LRU Cache を解ける
- [ ] LeetCode 460. LFU Cache に挑戦できる
- [ ] std::list を使わず、自作の双方向リスト（ダミーの head / tail ノード付き）でも書ける

## LRUキャッシュの動き
```
容量 2。左が最近使ったもの（MRU）、右が最も古いもの（LRU）

put(1,1):  [MRU] (1:1) [LRU]
put(2,2):  [MRU] (2:2) (1:1) [LRU]
get(1):    1 を先頭へ移動 → [MRU] (1:1) (2:2) [LRU]   戻り値 1
put(3,3):  満杯 → 末尾 (2:2) を追い出す
           [MRU] (3:3) (1:1) [LRU]
get(2):    存在しない → -1
put(4,4):  満杯 → 末尾 (1:1) を追い出す
           [MRU] (4:4) (3:3) [LRU]

構造:
  index (unordered_map)          items (list)
  +-----+--------+
  |  4  |  ●-----+------->  (4:4) <-> (3:3)
  |  3  |  ●-----+----------------------^
  +-----+--------+
```

## コードの解説

### メンバ変数（main.cpp:9-11）
```cpp
std::size_t capacity;
std::list<std::pair<int, int>> items;                                    // (key, value) を使用順に並べる。先頭が最新
std::unordered_map<int, std::list<std::pair<int, int>>::iterator> index; // key → リスト内の位置
```
- マップの値がリストの **イテレータ** なのがポイント。これでリスト内のノードに O(1) で直接たどり着ける
- `std::list` のイテレータは、他の要素を追加・削除・splice しても無効にならない

### get（main.cpp:16-24）
```cpp
int get(int key)
{
    auto it = index.find(key);
    if (it == index.end())
        return -1;                                     // ない

    items.splice(items.begin(), items, it->second);    // 使ったので先頭へ移動
    return it->second->second;                         // イテレータ → pair → value
}
```
- `splice(移動先, 移動元リスト, 移動する要素)` はポインタの付け替えだけなので O(1)。コピーも発生しない
- `it->second` はリストのイテレータ、`it->second->second` はその pair の value

### put（main.cpp:26-44）
```cpp
void put(int key, int value)
{
    auto it = index.find(key);
    if (it != index.end())
    {
        it->second->second = value;                    // 既存キー: 値を更新して
        items.splice(items.begin(), items, it->second); // 先頭へ移動
        return;
    }

    if (items.size() == capacity)
    {
        index.erase(items.back().first);               // 末尾（LRU）のキーをマップから消す
        items.pop_back();                              // リストからも消す
    }

    items.emplace_front(key, value);                   // 新しい要素を先頭に
    index[key] = items.begin();                        // 位置を記録
}
```
- 追い出し時に「どのキーをマップから消すか」を知るために、リストに key も持たせている
- `index.erase` を `items.pop_back` より先に呼ぶ（pop_back の後だと `back()` が別の要素になる）
- `std::list::size()` は C++11 以降 O(1)

### print（main.cpp:46-51）
- 先頭（MRU）から末尾（LRU）の順に `(key:value)` を出力

## 計算量
- **時間計算量**:
  - get: O(1)（平均。ハッシュマップの検索に依存）
  - put: O(1)（平均）
- **空間計算量**: O(capacity)

## 特徴
- **get / put ともに O(1)**: マップで場所を見つけ、リストで順序を更新する
- **使用順を常に保持**: 先頭が最新、末尾が最古

## 使いどころ
- Web ブラウザやCDNのキャッシュ
- データベースのバッファプール
- OS のページ置換アルゴリズム
- メモ化で使うメモリに上限を設けたいとき

## 注意点
- LeetCode では `std::list` + `std::unordered_map` で十分だが、面接では「std::list を使わずに書いて」と言われることがある。その場合はダミーの head / tail を持つ双方向リストを自作すると、端の特別扱いが不要になる
- 容量 0 の場合の扱い（put で即追い出し）に注意。LeetCode 146 では capacity >= 1 が保証されている
