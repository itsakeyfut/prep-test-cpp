# AST - 抽象構文木 (Abstract Syntax Tree)

## 概要
抽象構文木（AST）は、プログラムの構造を木構造で表現したものです。コンパイラやインタプリタが、ソースコードを解析して実行可能な形式に変換する際に使用されます。

## ASTの動き
数式 `1 + 2 * 3` をASTで表現すると以下のような木構造になります：

```
      +
     / \
    1   *
       / \
      2   3
```

演算子が内部ノード、数値が葉ノードになります。

## コードの解説

### ノードの種類（main.cpp:5-9）
```cpp
enum class NodeType
{
    Number,    // 数値ノード
    BinaryOp,  // 二項演算子ノード
};
```

### 基底クラス（main.cpp:11-16）
```cpp
struct ASTNode
{
    virtual NodeType type() const = 0;  // ノードの型
    virtual void print() const = 0;     // ノードの表示
};
```
- すべてのノードが継承する抽象基底クラス
- 仮想関数により、派生クラスでの実装を強制

### 数値ノード（main.cpp:18-30）
```cpp
struct NumberNode : public ASTNode
{
    double value;  // 数値を保持
    void print() const override
    {
        std::cout << value;
    }
};
```
- 数値リテラルを表現するノード

### 二項演算子ノード（main.cpp:32-51）
```cpp
struct BinaryOpNode : public ASTNode
{
    char op;                        // 演算子 (+, -, *, / など)
    std::unique_ptr<ASTNode> left;  // 左の子ノード
    std::unique_ptr<ASTNode> right; // 右の子ノード

    void print() const override
    {
        std::cout << "(";
        left->print();          // 再帰的に左を表示
        std::cout << " " << op << " ";
        right->print();         // 再帰的に右を表示
        std::cout << ")";
    }
};
```
- 二項演算（+, -, *, / など）を表現するノード
- `std::unique_ptr`で子ノードを管理（自動メモリ管理）

### ASTの構築（main.cpp:55-62）
```cpp
// 1 + 2 * 3 のASTを構築
auto expr = std::make_unique<BinaryOpNode>(
    '+',
    std::make_unique<NumberNode>(1),
    std::make_unique<BinaryOpNode>(
        '*',
        std::make_unique<NumberNode>(2),
        std::make_unique<NumberNode>(3)));
```
- 内側から外側へ木を構築
- `2 * 3`を先に作成し、それを`1 + ...`の右側に配置

## 計算量
- **時間計算量**: O(n)（nはノード数）
  - 木の走査に各ノード1回ずつアクセス
- **空間計算量**: O(h)（hは木の高さ）
  - 再帰呼び出しのスタックサイズ

## 特徴
- **階層構造**: 演算の優先順位を木の構造で表現
- **再帰的**: 各ノードが同じインターフェースを持つ
- **拡張可能**: 新しいノード型を簡単に追加できる

## 使いどころ
- コンパイラやインタプリタの実装
- 数式パーサー
- プログラム解析ツール
- コード変換ツール（トランスパイラなど）
