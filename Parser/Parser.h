#ifndef PARSER_H
#define PARSER_H

#include "Tokeniser.h"
#include "Token.h"
#include "ExpressionTree.h"
#include "ProgramStatement.h"
#include <vector>
#include <string>


class Parser
{
    public:
        Parser();
        virtual ~Parser();
        std::vector<ProgramStatement*> *parse(std::string filename);
    protected:
    private:
        std::string readFile(std::string f);
        ProgramStatement *get_statement(Tokeniser *tk);
        ProgramStatement *get_assignment(Tokeniser *tk, std::string var_name);
        ProgramStatement *get_declaration(Tokeniser *tk, std::string var_type);
        ProgramStatement *get_function_call(Tokeniser *tk, std::string func_name);

        ExpressionTreeNode *get_expression(Tokeniser *tk);
        ExpressionTreeNode *get_term(Tokeniser *tk);
        ExpressionTreeNode *get_factor(Tokeniser *tk);
};

#endif // PARSER_H
