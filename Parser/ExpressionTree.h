#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H


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
        void print_self();
        double evaluate();
    private:
    protected:
        double my_value;
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
