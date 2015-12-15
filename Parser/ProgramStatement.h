#ifndef PROGRAMSTATEMENT_H
#define PROGRAMSTATEMENT_H

#include <string>
#include "ExpressionTree.h"

class Variable
{
    public:
        Variable(std::string var_type, std::string var_name);
        ~Variable();
        std::string Name();
    private:
    protected:
        std::string my_type;
        std::string my_name;
};

class ProgramStatement
{
    public:
        ProgramStatement();
        virtual void execute() = 0;             // implement this, children
        virtual void print_self() = 0;
    protected:
    private:
};


class Assignment : public ProgramStatement
{
    public:
        Assignment(Variable *target);
        ~Assignment();
        void set_expression(ExpressionTreeNode* tree);
        void execute();
        void print_self();
    private:
    protected:
        ExpressionTreeNode *expression_tree;
        Variable *assignment_target;
};
#endif // PROGRAMSTATEMENT_H
