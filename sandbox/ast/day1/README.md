# 疑問点
## `include <memory>` は何をインクルードしているの？
`<memory>` はスマートポインタ（`std::unique_ptr`, `std::shared_ptr`）やアロケータ関連のユーティリティが入っているヘッダ。

## `include <string>` は必要？ `string` ってインクルードしなくても使えるんじゃないの？

`std::string` を使うときは本来 `<string>` のインクルードが必要。
ただし、他の標準ヘッダが内部的に `<string>` を読み込む場合があり、たまたま使えてしまうことがあるというだけ。完全に偶然。

> 「動いてるから大丈夫でしょ？」と油断すると後でビルドが爆発してしまう。

明示的に `<string>` を入れるのが正しい書き方。

## 仮想デストラクタ（virtual ~ASTNode() = default;）って何？
ポリモフィックなクラス（基底クラスをポインタで扱う）には必ず仮想デストラクタが必要。

```cpp
ASTNode* n = new NumberNode(1);
delete n;
```

このとき、仮想デストラクタが無いと派生クラス（NumberNode）のデストラクタが呼ばれない。
→ リソースリークや破壊されないオブジェクトが発生する。

## `explicit` って何？
コンストラクタが暗黙の型変換に使われるのを防ぐキーワード。

```cpp
NumberNode n = 10; // explicit がない場合は勝手に変換されてしまう
```

`explicit` を付けると、このような暗黙変換が禁止される。

## `std::unique_ptr` って何？
所有権が1つだけのスマートポインタ。

特徴は以下：
- 自動で delete してくれる（メモリリーク防止）
- コピーできない（所有権は1ヶ所のみ）
- ムーブ（所有権の移譲）は可能

使用例：
```cpp
std::unique_ptr<ASTNode> node = std::make_unique<NumberNode>(5);
```

## `std::move` って何？
オブジェクトを "ムーブ可能" として扱うためのキャスト

`unique_ptr` はコピー禁止なので、以下はできない：
```cpp
left = std::move(lhs); // 所有権が移る
```

`std::move` は実体を移動する魔法ではなく、
「右辺値として扱って良いよ」という合図。

## `std::make_unique` って何？
`new` より安全に `unique_ptr` を作るための関数。

```cpp
auto p = std::make_unique<NumberNode>(10);
```

メリット：
- `new` を書かなくて良い（例外安全）
- コードが簡潔
- C++の推奨スタイル
