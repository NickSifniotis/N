#include "Tokeniser.h"

using namespace std;
using namespace boost;


Tokeniser::Tokeniser()
{
    Tokeniser("");
}


Tokeniser::Tokeniser(string data)
{
    char_separator<char> sep("\n", " \"+-*/=.,()[]{}'");
    tk = new tokenizer<char_separator<char> > (data, sep);
    tk_iterator = tk->begin();
}


Tokeniser::~Tokeniser()
{
    // remember always to clean up after yourself.
    delete(tk);
}


bool Tokeniser::more_data()
{
    return tk_iterator != tk->end();
}


Token Tokeniser::currentToken()
{
    /**
    Parses the next complete token, sets and returns a Token structure that contains the
    sort of token that this is, along with the data string (if relevant).

    Advances the tokeniser to the start of the next token.
    **/
    Token res;

    if (!currentDataPayload().compare("+"))
    {
        next_no_whitespace();

        if (!currentDataPayload().compare("="))
        {
            res.type = PLUS_EQUALS;
            next_no_whitespace();
        }
        else
            res.type = PLUS;
    }
    else if (!currentDataPayload().compare("-"))
    {
        next_no_whitespace();

        if (!currentDataPayload().compare("="))
        {
            res.type = MINUS_EQUALS;
            next_no_whitespace();
        }
        else
            res.type = MINUS;
    }
    else if (!currentDataPayload().compare("*"))
    {
        next_no_whitespace();

        if (!currentDataPayload().compare("="))
        {
            res.type = MULT_EQUALS;;
            next_no_whitespace();
        }
        else
            res.type = MULT;
    }
    else if (!currentDataPayload().compare("/"))
    {
        next_no_whitespace();

        if (!currentDataPayload().compare("="))
        {
            res.type = DIV_EQUALS;
            next_no_whitespace();
        }
        else
            res.type = DIV;
    }
    else if (!currentDataPayload().compare("%"))
    {
        next_no_whitespace();
        res.type = MOD;
    }
    else if (!currentDataPayload().compare("="))
    {
        next_no_whitespace();
        res.type = EQUALS;
    }
    else if (!currentDataPayload().compare("("))
    {
        next_no_whitespace();
        res.type = L_BRACKET;
    }
    else if (!currentDataPayload().compare(")"))
    {
        next_no_whitespace();
        res.type = R_BRACKET;
    }
    else if (!currentDataPayload().compare("\""))
    {
        string payload = "";
        next();

        while (currentDataPayload().compare("\"") && more_data())
        {
            payload += currentDataPayload();
            next();
        }
        next_no_whitespace();
        res.type = STRING_LITERAL;
        res.data_payload = payload;
    }
    else
    {
        res.data_payload = currentDataPayload();
        next_no_whitespace();
        res.type = ALPHANUMERIC;
    }

    return res;
}


string Tokeniser::currentDataPayload()
{
    string res = *tk_iterator;
    return res;
}


void Tokeniser::next()
{
    if (more_data())
        tk_iterator++;
}


void Tokeniser::next_no_whitespace()
{
    // need to rewrite the next/nextnowhitespace to take a bool so its in one function
    // and also not suck with the notnull tests
    if (!more_data())
        return;

    tk_iterator++;

    if (!more_data())
        return;

    if (!currentDataPayload().compare(" "))
        next_no_whitespace();               // a truly terrible recursive solution to this problem
}
