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

    while (tk->more_data())
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
    if (tk->currentToken().type != ALPHANUMERIC)
    {
        cout << endl << "Parse error: Identifier expected." << endl;
        exit(-1);
    }

    // the thing is, every statement starts with an identifier - so far. It's actually the next token
    // that will determine what sort of statement this is.
    string first_datum = tk->currentToken().data_payload;
    tk->next_no_whitespace();

    if (!tk->more_data())
    {
        cout << endl << "Parse error: More data expected." << endl;
        exit(-1);
    }

    Token toke = tk->currentToken();
    switch (toke.type)
    {
        case ALPHANUMERIC:
            break;
        case L_BRACKET:
            break;
        case EQUALS:
            break;
    }
}

ProgramStatement *Parser::get_assignment(Tokeniser *tk, string var_name)
{
    // allrighty, let's create a fucknig assignment eh.
    Variable *var = new Variable("", var_name);
    tk->next_no_whitespace();

    if (!tk->more_data())
    {
        cout << endl << "Parse error: More data expected." << endl;
        exit(-1);
    }

}

ProgramStatement *Parser::get_declaration(Tokeniser *tk, string var_type)
{
    return nullptr;
}

ProgramStatement *Parser::get_function_call(Tokeniser *tk, string func_name)
{
    return nullptr;
}
