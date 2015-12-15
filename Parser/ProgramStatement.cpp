#include "ProgramStatement.h"
#include <iostream>

using namespace std;


Variable::Variable(string type, string name) : my_type(type), my_name(name) {}

Variable::~Variable () {}

string Variable::Name()
{
    return my_name;
}


ProgramStatement::ProgramStatement()
{
    //ctor
}

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
