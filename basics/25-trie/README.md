# Trie - トライ木 (Prefix Tree)

## 概要
トライ木は、文字列を1文字ずつ木の枝としてたどって格納するデータ構造です。共通の接頭辞を持つ単語は同じ経路を共有するので、「この接頭辞で始まる単語があるか」を単語の長さだけの時間で判定できます。

## 目的
- 接頭辞（prefix）検索を高速に行う方法を身につける
- 単語辞書を使う探索問題（オートコンプリート、Word Search II など）の基礎にする
- 26 分岐の木を `std::unique_ptr` で安全に管理する書き方に慣れる

## 達成条件
- [ ] 何も見ずに main.cpp を10分以内に手書きできる
- [ ] `search` と `starts_with` の違い（`is_end` を見るかどうか）を説明できる
- [ ] 各操作が O(L)（L は文字列長）になる理由を説明できる
- [ ] 配列 26 個と `std::unordered_map` の子の持ち方のトレードオフを説明できる
- [ ] LeetCode 208. Implement Trie (Prefix Tree) を解ける
- [ ] LeetCode 211. Design Add and Search Words Data Structure を解ける
- [ ] LeetCode 212. Word Search II を解ける
- [ ] LeetCode 648. Replace Words を解ける

## トライ木の動き
`"apple"`, `"app"`, `"bat"` を挿入した場合（`*` は `is_end = true`）：

```
          (root)
          /    \
         a      b
         |      |
         p      a
         |      |
         p*     t*
         |
         l
         |
         e*
```

- `search("app")` → p* に到達、`is_end` が true → true
- `search("appl")` → l に到達、`is_end` が false → false
- `starts_with("appl")` → l に到達できた → true
- `starts_with("cat")` → root に c の子がない → false

## コードの解説

### ノード構造（main.cpp:6-10）
```cpp
struct TrieNode
{
    std::array<std::unique_ptr<TrieNode>, 26> children;  // 'a'〜'z' の子
    bool is_end = false;                                 // ここで単語が終わるか
};
```
- 子は `c - 'a'` をインデックスにして直接アクセス
- `unique_ptr` なので木全体がデストラクタで自動解放される

### ノード探索（main.cpp:17-28）
```cpp
const TrieNode *find_node(const std::string &s) const
{
    const TrieNode *node = root.get();
    for (char c : s)
    {
        int i = c - 'a';
        if (!node->children[i])
            return nullptr;              // 途中で枝がない
        node = node->children[i].get();  // 1文字進む
    }
    return node;                         // 最後の文字のノード
}
```
- `search` と `starts_with` の共通部分をまとめたヘルパー

### 挿入（main.cpp:33-44）
```cpp
void insert(const std::string &word)
{
    TrieNode *node = root.get();
    for (char c : word)
    {
        int i = c - 'a';
        if (!node->children[i])
            node->children[i] = std::make_unique<TrieNode>();  // なければ作る
        node = node->children[i].get();
    }
    node->is_end = true;                 // 単語の終わりに印をつける
}
```

### 検索（main.cpp:46-50）
```cpp
bool search(const std::string &word) const
{
    const TrieNode *node = find_node(word);
    return node && node->is_end;         // 到達でき、かつ単語の終わり
}
```

### 接頭辞検索（main.cpp:52-55）
```cpp
bool starts_with(const std::string &prefix) const
{
    return find_node(prefix) != nullptr; // 到達できれば OK
}
```

## 計算量
- **時間計算量**:
  - insert: O(L)
  - search: O(L)
  - starts_with: O(L)
- **空間計算量**: O(総文字数 × 26)（各ノードが 26 個のポインタを持つ）

## 特徴
- **接頭辞の共有**: 共通部分をまとめて保存する
- **単語数に依存しない**: 辞書の大きさに関係なく、検索は文字列長だけで決まる
- **メモリを食う**: ノードごとに 26 ポインタ分の領域が必要

## 使いどころ
- オートコンプリート・予測変換
- スペルチェック・辞書検索
- グリッド上で複数単語を同時に探す（Word Search II）
- XOR 最大化（ビットごとのトライ、LC 421）

## 注意点
- 入力が小文字英字以外を含む場合は `children` のサイズを変えるか `unordered_map` を使う
- `search` で `is_end` を確認し忘れると、接頭辞も「単語あり」と判定してしまう
