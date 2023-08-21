#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <memory>
#include <iostream>
#include <cmath>

// Temel düğüm sınıfı
class Node
{
public:
    virtual ~Node() = default;
    virtual double evaluate() const = 0; // Bu düğümün değerini hesaplar
};

using NodePtr = std::shared_ptr<Node>;

class UnaryOperationNode : public Node
{
public:
    explicit UnaryOperationNode(NodePtr operand) : operand_(operand) {}
    virtual ~UnaryOperationNode() = default;

protected:
    NodePtr operand_;
};

// Sabit değerleri temsil eden düğüm
class ConstantNode : public Node
{
public:
    ConstantNode(double value);
    double evaluate() const override;

private:
    double value_;
};

// İki alt düğüm arasında toplama işlemi yapan düğüm
class AdditionNode : public Node
{
public:
    AdditionNode(NodePtr left, NodePtr right);
    double evaluate() const override;

private:
    NodePtr left_;
    NodePtr right_;
};

// İki alt düğüm arasında çıkarma işlemi yapan düğüm
class SubtractionNode : public Node
{
public:
    SubtractionNode(NodePtr left, NodePtr right);
    double evaluate() const override;

private:
    NodePtr left_;
    NodePtr right_;
};

// İki alt düğüm arasında çarpma işlemi yapan düğüm
class MultiplicationNode : public Node
{
public:
    MultiplicationNode(NodePtr left, NodePtr right);
    double evaluate() const override;

private:
    NodePtr left_;
    NodePtr right_;
};

// İki alt düğüm arasında bölme işlemi yapan düğüm
class DivisionNode : public Node
{
public:
    DivisionNode(NodePtr left, NodePtr right);
    double evaluate() const override;

private:
    NodePtr left_;
    NodePtr right_;
};

class PowerNode : public Node
{
public:
    PowerNode(NodePtr left, NodePtr right) : left_(left), right_(right) {}

    double evaluate() const override
    {
        return std::pow(left_->evaluate(), right_->evaluate());
    }

private:
    NodePtr left_;
    NodePtr right_;
};

class SinNode : public Node
{
public:
    SinNode(NodePtr operand);
    double evaluate() const override;

private:
    NodePtr operand_;
};

class CosNode : public Node
{
public:
    CosNode(NodePtr operand);
    double evaluate() const override;

private:
    NodePtr operand_;
};

class TanNode : public Node
{
public:
    TanNode(NodePtr operand);
    double evaluate() const override;

private:
    NodePtr operand_;
};

class CotNode : public Node
{
public:
    CotNode(NodePtr operand);
    double evaluate() const override;

private:
    NodePtr operand_;
};

class LnNode : public UnaryOperationNode
{
public:
    explicit LnNode(NodePtr operand) : UnaryOperationNode(operand) {}

    double evaluate() const override;
};

class LogNode : public UnaryOperationNode
{
public:
    explicit LogNode(NodePtr operand) : UnaryOperationNode(operand) {}

    double evaluate() const override;
};

class SqrtNode : public UnaryOperationNode
{
public:
    explicit SqrtNode(NodePtr operand) : UnaryOperationNode(operand) {}

    double evaluate() const override;
};

class SinhNode : public UnaryOperationNode
{
public:
    SinhNode(const NodePtr &operand) : UnaryOperationNode(operand) {}

    double evaluate() const override
    {
        return std::sinh(operand_->evaluate());
    }
};

class CoshNode : public UnaryOperationNode
{
public:
    CoshNode(const NodePtr &operand) : UnaryOperationNode(operand) {}

    double evaluate() const override
    {
        return std::cosh(operand_->evaluate());
    }
};

class TanhNode : public UnaryOperationNode
{
public:
    TanhNode(const NodePtr &operand) : UnaryOperationNode(operand) {}

    double evaluate() const override
    {
        return std::tanh(operand_->evaluate());
    }
};

class CothNode : public UnaryOperationNode
{
public:
    CothNode(const NodePtr &operand) : UnaryOperationNode(operand) {}

    double evaluate() const override
    {
        double tanhVal = std::tanh(operand_->evaluate());
        if (tanhVal != 0)
        {
            return 1 / tanhVal;
        }
        return HUGE_VAL; // Infinity for division by zero
    }
};

class SechNode : public UnaryOperationNode
{
public:
    SechNode(const NodePtr &operand) : UnaryOperationNode(operand) {}

    double evaluate() const override
    {
        return 1 / std::cosh(operand_->evaluate());
    }
};

class CschNode : public UnaryOperationNode
{
public:
    CschNode(const NodePtr &operand) : UnaryOperationNode(operand) {}

    double evaluate() const override
    {
        double sinhVal = std::sinh(operand_->evaluate());
        if (sinhVal != 0)
        {
            return 1 / sinhVal;
        }
        return HUGE_VAL; // Infinity for division by zero
    }
};

class FactorialNode : public UnaryOperationNode
{
public:
    FactorialNode(const NodePtr &operand) : UnaryOperationNode(operand) {}

    double evaluate() const override
    {
        int n = static_cast<int>(operand_->evaluate());
        if (n < 0)
            throw std::runtime_error("Negatif faktöriyel hesaplanamaz");
        return factorial(n);
    }

private:
    double factorial(int n) const
    {
        if (n <= 1)
            return 1;
        return n * factorial(n - 1);
    }
};

#endif // EXPRESSION_TREE_H
