#ifndef PROGRAMSTATEMENT_H
#define PROGRAMSTATEMENT_H

#include <string>
#include "ExpressionTree.h"

class Variable
{
    public:
        Variable(std::string var_type, std::string var_name);
        virtual ~Variable();
        std::string Name();
        std::string Type();
    private:
    protected:
        std::string my_type;
        std::string my_name;
};

class ProgramStatement
{
    public:
        ProgramStatement();
        virtual ~ProgramStatement();
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

class FunctionCall : public ProgramStatement
{
    public:
        FunctionCall(std::string name);
        ~FunctionCall();
        void add_parameter(ExpressionTreeNode *param);
        void print_self();
        void execute();
        ExpressionTreeNode *get_returner();
    private:
    protected:
        ExpressionTreeVariable *my_function;

};

class Declaration : public ProgramStatement
{
    public:
        Declaration(std::string my_type, std::string my_name);
        ~Declaration();
        void print_self();
        void execute();
    private:
    protected:
        Variable *my_variable;
};

#endif // PROGRAMSTATEMENT_H
