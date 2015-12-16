#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <string>
#include <vector>


enum class SingleOperands
{
    SOLO_MINUS,
    NONE
};

enum class DoubleOperands
{
    PLUS,
    MINUS,
    MULT,
    DIV,
    MOD
};


class ExpressionTreeNode
{
    public:
        ExpressionTreeNode();
        virtual ~ExpressionTreeNode();
        virtual void print_self() = 0;
        virtual double evaluate() = 0;      // lets keep these nice and abstract
    protected:
    private:
};


class ExpressionTreeSingleOperand : public ExpressionTreeNode
{
    public:
        ExpressionTreeSingleOperand(SingleOperands instruction, ExpressionTreeNode *child = nullptr);
        ~ExpressionTreeSingleOperand();
        void set_child(ExpressionTreeNode *child);
        void print_self();
        double evaluate();
    private:
    protected:
        ExpressionTreeNode *my_child;
        SingleOperands my_code;
};


class ExpressionTreeLiteral : public ExpressionTreeNode
{
    public:
        ExpressionTreeLiteral(double value);
        ExpressionTreeLiteral(std::string value);
        ~ExpressionTreeLiteral();
        void print_self();
        double evaluate();
    private:
    protected:
        bool i_am_string;
        void *my_value;
};


class ExpressionTreeVariable : public ExpressionTreeNode
{
    // this crafty class handles both variables per se, and function calls too
    public:
        ExpressionTreeVariable(std::string name);
        virtual ~ExpressionTreeVariable();
        void add_parameter (ExpressionTreeNode *param);
        void print_self();
        double evaluate();
    private:
    protected:
        std::string my_name;
        std::vector <ExpressionTreeNode *> *my_parameters;
};


class ExpressionTreeDualOperand : public ExpressionTreeNode
{
    public:
        ExpressionTreeDualOperand(DoubleOperands instruction, ExpressionTreeNode *left = nullptr, ExpressionTreeNode *right = nullptr);
        ~ExpressionTreeDualOperand();
        void print_self();
        double evaluate();
        void set_left(ExpressionTreeNode *left);
        void set_right(ExpressionTreeNode *right);
    private:
    protected:
        ExpressionTreeNode *my_left_child;
        ExpressionTreeNode *my_right_child;
        DoubleOperands my_code;
};
#endif // EXPRESSIONTREE_H
