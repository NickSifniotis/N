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
        std::vector<ProgramStatement> parse(std::string filename);
    protected:
    private:

};

#endif // PARSER_H
