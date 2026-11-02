#include <iostream>
#include <memory>
#include <string>

enum class NodeType
{
    Number,
    BinaryOp,
};

struct ASTNode
{
    virtual ~ASTNode() = default; // これはデストラクタで合っている？ = default は常につける？
    virtual NodeType type() const = 0; // virtual は仮想関数で合っている？interface みたいなもの？
    virtual void print() const = 0; // 関数名() const = 0; の関数名の後の const = 0 は何を意味する？
};

struct NumberNode : public ASTNode
{
    double value;

    explicit NumberNode(double val) : value(val) {} // explicit って何を意味する？

    NodeType type() const override { return NodeType::Number; } // なぜ const override なの？ override だけじゃダメ？

    void print() const override
    {
        std::cout << value;
    }
};

struct BinaryOpNode : public ASTNode
{
    char op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

    BinaryOpNode(char op, std::unique_ptr<ASTNode> lhs, std::unique_ptr<ASTNode> rhs)
        : op(op), left(std::move(lhs)), right(std::move(rhs)) {} // : から後のは何だっけ？デフォルト引数みたいな？

    NodeType type() const override { return NodeType::BinaryOp; }

    void print() const override
    {
        std::cout << "(";
        left->print();
        std::cout << " " << op << " ";
        right->print();
        std::cout << ")";
    }
};

int main()
{
    auto expr = std::make_unique<BinaryOpNode>(
        '+',
        std::make_unique<NumberNode>(1),
        std::make_unique<BinaryOpNode>(
            '*',
            std::make_unique<NumberNode>(2),
            std::make_unique<NumberNode>(3)));

    std::cout << "Expression: ";
    expr->print();
    std::cout << "\n";
}