#include "ExpressionTree.h"
#include <iostream>

using namespace std;


ExpressionTreeNode::ExpressionTreeNode()
{
    //ctor
}

ExpressionTreeNode::~ExpressionTreeNode()
{
    //dtor
}

ExpressionTreeSingleOperand::ExpressionTreeSingleOperand(SingleOperands instruction, ExpressionTreeNode* child) :
    my_child(child),
    my_code(instruction)
    {
        // the body of the constructor
        // is devoid of any meaning....
    }

ExpressionTreeSingleOperand::~ExpressionTreeSingleOperand()
{
    if (my_child != nullptr)
        delete (my_child);
}

void ExpressionTreeSingleOperand::print_self()
{
    // I can't actually think of any single operand operations, save perhaps
    // for minus.
    //
    // Good thing I have that 'none' token type up my sleeve
    if (my_code == SingleOperands::SOLO_MINUS)
        cout << "-";

    if (my_child != nullptr)
        my_child -> print_self();
}

double ExpressionTreeSingleOperand::evaluate()
{
    double res;
    if (my_child == nullptr)
    {
        cout << endl << "This single operand node has no child. Unable to evaluate - aborting." << endl;
        exit (-1);
    }

    else
    {
        res = my_child -> evaluate();
        switch (my_code)
        {
            case SingleOperands::SOLO_MINUS:
                res = -res;
                break;
            case SingleOperands::NONE:
                // nothing
                break;
        }
    }
    return res;
}

void ExpressionTreeSingleOperand::set_child(ExpressionTreeNode *child)
{
    my_child = child;
}


ExpressionTreeLiteral::ExpressionTreeLiteral(double value) : my_value(value) {}

void ExpressionTreeLiteral::print_self()
{
    cout << my_value;
}

double ExpressionTreeLiteral::evaluate()
{
    return my_value;
}


ExpressionTreeDualOperand::ExpressionTreeDualOperand(DoubleOperands instruction, ExpressionTreeNode *left, ExpressionTreeNode *right):
    my_code(instruction),
    my_left_child(left),
    my_right_child(right)
    {
        // ahahhahahahhaahahahah
    }

ExpressionTreeDualOperand::~ExpressionTreeDualOperand()
{
    if (my_left_child != nullptr)
        delete(my_left_child);

    if (my_right_child != nullptr)
        delete(my_right_child);
}

void ExpressionTreeDualOperand::set_left(ExpressionTreeNode *left)
{
    my_left_child = left;
}

void ExpressionTreeDualOperand::set_right(ExpressionTreeNode *right)
{
    my_right_child = right;
}

void ExpressionTreeDualOperand::print_self()
{
    if (my_left_child != nullptr)
        my_left_child -> print_self();
    else
    {
        cout << endl << "Print_self error: Unable to print self as current dual operand node has no left child." << endl;
        exit(-1);
    }

    switch (my_code)
    {
        case DoubleOperands::PLUS:
            cout << " + ";
            break;
        case DoubleOperands::MINUS:
            cout << " - ";
            break;
        case DoubleOperands::MULT:
            cout << " * ";
            break;
        case DoubleOperands::DIV:
            cout << " / ";
            break;
        case DoubleOperands::MOD:
            cout << " % ";
            break;
    }

    if (my_right_child != nullptr)
        my_right_child -> print_self();
    else
    {
        cout << endl << "Print_self error: Unable to print self as current dual operand node has no right child." << endl;
        exit(-1);
    }
}

double ExpressionTreeDualOperand::evaluate()
{
    if (my_left_child == nullptr || my_right_child == nullptr)
    {
        cout << endl << "Print_self error: Unable to print self as current dual operand node is missing a child." << endl;
        exit(-1);
    }

    double res = 0.0;
    double left_side = my_left_child -> evaluate();
    double right_side = my_right_child -> evaluate();

    switch (my_code)
    {
        case DoubleOperands::PLUS:
            res = left_side + right_side;
            break;
        case DoubleOperands::MINUS:
            res = left_side - right_side;
            break;
        case DoubleOperands::MULT:
            res = left_side * right_side;
            break;
        case DoubleOperands::DIV:
            if (right_side == 0.0)
            {
                cout << endl << "Attempting to divide by zero! Aborting." << endl;
                exit(-1);
            }
            res = left_side / right_side;
            break;
        case DoubleOperands::MOD:
            res = (int)left_side % (int)right_side;
            break;
    }

    return res;
}
