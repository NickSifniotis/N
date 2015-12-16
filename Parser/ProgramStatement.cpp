#include "ProgramStatement.h"
#include <iostream>

using namespace std;


Variable::Variable(string type, string name) : my_type(type), my_name(name) {}

Variable::~Variable () {}

string Variable::Name()
{
    return my_name;
}

string Variable::Type()
{
    return my_type;
}


ProgramStatement::ProgramStatement()
{
    //ctor
}

ProgramStatement::~ProgramStatement() {}

Assignment::Assignment(Variable *target) : assignment_target(target) {}

Assignment::~Assignment()
{
    if (expression_tree != nullptr)
        delete (expression_tree);

    if (assignment_target != nullptr)
        delete (assignment_target);
}

void Assignment::set_expression(ExpressionTreeNode *tree)
{
    expression_tree = tree;
}

void Assignment::print_self()
{
    if (expression_tree == nullptr || assignment_target == nullptr)
    {
        cout << endl << "Unable to print assignment statement; data missing." << endl;
        exit (-1);
    }

    cout << assignment_target -> Name() << " = ";
    expression_tree -> print_self();
}

void Assignment::execute()
{
    // at this stage, do nothing.
}


FunctionCall::FunctionCall(string name)
{
    my_function = new ExpressionTreeVariable(name);
}

FunctionCall::~FunctionCall()
{
    delete (my_function);
}

void FunctionCall::add_parameter(ExpressionTreeNode *param)
{
    my_function -> add_parameter(param);
}

void FunctionCall::print_self()
{
    cout << "FUNCTION CALL ";
    my_function -> print_self();
}

void FunctionCall::execute()
{
    // todo
}

ExpressionTreeNode* FunctionCall::get_returner()
{
    return my_function;
}


Declaration::Declaration (string type, string name)
{
    my_variable = new Variable(type, name);
}

Declaration::~Declaration()
{
    delete (my_variable);
}

void Declaration::execute()
{
    // do nothing
}

void Declaration::print_self()
{
    cout << "DECLARING " << my_variable->Name() << " TO BE TYPE " << my_variable->Type();
}
