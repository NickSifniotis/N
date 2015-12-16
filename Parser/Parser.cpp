#include "Parser.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


Parser::Parser()
{
    //ctor
}

Parser::~Parser()
{
    //dtor
}

vector<ProgramStatement*> *Parser::parse(string filename)
{
    string file_contents = readFile(filename);
    vector<ProgramStatement*> *results = new vector<ProgramStatement*>();
    Tokeniser *tk = new Tokeniser(file_contents);

    tk->advance();
    while (tk->currentToken().type != TokenType::END_OF_FILE)
        results -> push_back(get_statement(tk));

    delete (tk);
    return results;
}

string Parser::readFile(string f)
{
    char *filename = &f[0];
    string app;
    string line;

    ifstream inFile;
    inFile.open(filename);//open the input file

    stringstream strStream;
    strStream << inFile.rdbuf();//read the file
    app = strStream.str();//str holds the content of the file
    inFile.close();

    return app;
}

ProgramStatement *Parser::get_statement(Tokeniser *tk)
{
    if (tk->currentToken().type != TokenType::ALPHANUMERIC)
    {
        cout << endl << "Parse error: Identifier expected, found ";
        tk->currentToken().print_self();
        cout << endl;
        exit(-1);
    }

    // the thing is, every statement starts with an identifier - so far. It's actually the next token
    // that will determine what sort of statement this is.
    string first_datum = tk->currentToken().data_payload;
    tk->advance();

    if (tk->currentToken().type == TokenType::END_OF_FILE)
    {
        cout << endl << "Parse error: More data expected." << endl;
        exit(-1);
    }

    Token toke = tk->currentToken();
    ProgramStatement *res = nullptr;
    switch (toke.type)
    {
        case TokenType::ALPHANUMERIC:
            res = get_declaration(tk, first_datum);
            break;
        case TokenType::L_BRACKET:
            res = get_function_call(tk, first_datum);
            break;
        case TokenType::EQUALS:
            res = get_assignment(tk, first_datum);
            break;
        default:
            cout << endl << "Parse error: Unable to parse statement. Found ";
            toke.print_self();
            cout << endl;
            exit(-1);
            break;
    }

    // this is just to help debug
    cout << "Successfully parsed a statement: ";
    if (res == nullptr)
        cout << "Null statement";
    else
        res -> print_self();
    cout << endl;

    return res;
}

ProgramStatement *Parser::get_assignment(Tokeniser *tk, string var_name)
{
    // impossible condition here - the current token must be an equals sign
    // before this function is called
    if (tk->currentToken().type != TokenType::EQUALS)
    {
        cout << endl << "Impossible condition: Non-equals token found on entry to get_assignment, found ";
        tk->currentToken().print_self();
        cout << endl;
        exit(-1);
    }

    // allrighty, let's create a fucknig assignment eh.
    Variable *var = new Variable("", var_name);
    tk->advance();

    if (tk->currentToken().type == TokenType::END_OF_FILE)
    {
        cout << endl << "Parse error: More data expected." << endl;
        exit(-1);
    }

    Assignment *res = new Assignment(var);
    res -> set_expression (get_expression (tk));

    return res;
}

ProgramStatement *Parser::get_declaration(Tokeniser *tk, string var_type)
{
    // test for the impossible condition first.
    if (tk->currentToken().type != TokenType::ALPHANUMERIC)
    {
        cout << "Impossible condition; get_function_call has been called but the current token is not an identifier. Found ";
        tk->currentToken().print_self();
        cout << endl;
        exit(-1);
    }

    Declaration* res = new Declaration(var_type, tk -> currentToken().data_payload);
    tk -> advance();

    return res;
}

ProgramStatement *Parser::get_function_call(Tokeniser *tk, string func_name)
{
    // test for the impossible condition first.
    if (tk->currentToken().type != TokenType::L_BRACKET)
    {
        cout << "Impossible condition; get_function_call has been called but the current token is not L_BRACKET. Found ";
        tk->currentToken().print_self();
        cout << endl;
        exit(-1);
    }

    FunctionCall *res = new FunctionCall(func_name);
    tk -> advance();

    if (tk->currentToken().type == TokenType::END_OF_FILE)
    {
        cout << "Unexpected end of input." << endl;
        exit(-1);
    }

    while (tk->currentToken().type == TokenType::ALPHANUMERIC || tk->currentToken().type == TokenType::STRING_LITERAL || tk->currentToken().type == TokenType::NUMBER_LITERAL)
    {
        ExpressionTreeNode *expr = get_expression(tk);
        res -> add_parameter(expr);

        if (tk->currentToken().type == TokenType::END_OF_FILE)
        {
            cout << "Parse error: Unexpected end of input parsing a function call." << endl;
            exit(-1);
        }

        if (tk -> currentToken().type == TokenType::COMMA)
            tk -> advance();
    }

    if (tk->currentToken().type != TokenType::R_BRACKET)
    {
        cout << "Parse error: Expecting R_BRACKET, found ";
        tk->currentToken().print_self();
        cout << endl;
        exit(-1);
    }

    tk -> advance();
    return res;
}

ExpressionTreeNode *Parser::get_expression(Tokeniser *tk)
{
    ExpressionTreeNode *term = get_term(tk);
    ExpressionTreeNode *res = nullptr;

    if (tk -> currentToken().type == TokenType::PLUS)
    {
        tk -> advance();
        ExpressionTreeNode *right_side = get_expression(tk);

        res = new ExpressionTreeDualOperand(DoubleOperands::PLUS, term, right_side);
    }
    else if (tk -> currentToken().type == TokenType::MINUS)
    {
        tk -> advance();
        ExpressionTreeNode *right_side = get_expression(tk);

        res = new ExpressionTreeDualOperand(DoubleOperands::MINUS, term, right_side);
    }
    else
    {
        res = term;
    }

    return res;
}

ExpressionTreeNode *Parser::get_term(Tokeniser *tk)
{
    ExpressionTreeNode *factor = get_factor(tk);
    ExpressionTreeNode *res = nullptr;

    if (tk -> currentToken().type == TokenType::MULT)
    {
        tk -> advance();
        ExpressionTreeNode *right_side = get_term(tk);

        res = new ExpressionTreeDualOperand(DoubleOperands::MULT, factor, right_side);
    }
    else if (tk -> currentToken().type == TokenType::DIV)
    {
        tk -> advance();
        ExpressionTreeNode *right_side = get_term(tk);

        res = new ExpressionTreeDualOperand(DoubleOperands::DIV, factor, right_side);
    }
    else if (tk -> currentToken().type == TokenType::MOD)
    {
        tk -> advance();
        ExpressionTreeNode *right_side = get_term(tk);

        res = new ExpressionTreeDualOperand(DoubleOperands::MOD, factor, right_side);
    }
    else
    {
        res = factor;
    }

    return res;
}

ExpressionTreeNode *Parser::get_factor(Tokeniser *tk)
{
    ExpressionTreeNode *res = nullptr;

    if (tk -> currentToken().type == TokenType::L_BRACKET)
    {
        tk -> advance();
        res = get_expression(tk);

        if (tk -> currentToken().type != TokenType::R_BRACKET)
        {
            cout << "Parse error: Unbalanced parenthesis, found ";
            tk -> currentToken().print_self();
            cout << endl;
            exit (-1);
        }
        tk -> advance();
    }
    else if (tk -> currentToken().type == TokenType::MINUS)
    {
        tk -> advance();
        ExpressionTreeNode *child = get_factor(tk);
        res = new ExpressionTreeSingleOperand(SingleOperands::SOLO_MINUS, child);
    }
    else if (tk -> currentToken().type == TokenType::STRING_LITERAL)
    {
        res = new ExpressionTreeLiteral(tk -> currentToken().data_payload);
        tk -> advance();
    }
    else if (tk -> currentToken().type == TokenType::NUMBER_LITERAL)
    {
        res = new ExpressionTreeLiteral(stod(tk -> currentToken().data_payload));
        tk -> advance();
    }
    else if (tk -> currentToken().type == TokenType::ALPHANUMERIC)
    {
        // this may be a function call, or it may simply be a variable.
        // it's the next token that holds the key.

        string var_name = tk -> currentToken().data_payload;
        tk -> advance();

        if (tk -> currentToken().type == TokenType::L_BRACKET)
        {
            FunctionCall *functor = (FunctionCall*) get_function_call(tk, var_name);
            res = functor -> get_returner();
            delete (functor);           // tricky pointer shit
        }
        else
        {
            res = new ExpressionTreeVariable(var_name);
        }
    }
    else
    {
        cout << "Parse error: Unexpected token ";
        tk -> currentToken().print_self();
        cout << endl;
        exit (-1);
    }

    return res;
}
