#include <iostream>
#include <memory> // これって何をインクルードしているの？
#include <string> // stringってインクルードしなくても使えるんじゃないの？

enum class NodeType
{
    Number,
    BinaryOp,
};

struct ASTNode
{
    virtual ~ASTNode() = default; // 仮想デストラクタって何？
    virtual NodeType type() const = 0; 
    virtual void print() const = 0;
};

struct NumberNode : public ASTNode
{
    double value;

    explicit NumberNode(double val) : value(val) {} // explicitって何？

    NodeType type() const override { return NodeType::Number; }

    void print() const override
    {
        std::cout << value;
    }
};

struct BinaryOpNode : public ASTNode
{
    char op;
    std::unique_ptr<ASTNode> left; // std::unique_ptrって何？
    std::unique_ptr<ASTNode> right;

    BinaryOpNode(char op, std::unique_ptr<ASTNode> lhs, std::unique_ptr<ASTNode> rhs)
        : op(op), left(std::move(lhs)), right(std::move(rhs)) {} // std::moveって何？

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
    // 1 + 2 * 3
    auto expr = std::make_unique<BinaryOpNode>(
        '+',
        std::make_unique<NumberNode>(1),
        std::make_unique<BinaryOpNode>(
            '*',
            std::make_unique<NumberNode>(2),
            std::make_unique<NumberNode>(3)
        )
    ); // std::make_uniqueって何？

    std::cout << "Expression: ";
    expr->print(); // (1 + (2 * 3))
    std::cout << "\n";
}