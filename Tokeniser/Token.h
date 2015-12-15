#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType
{
    NONE,
    PLUS,
    MINUS,
    MULT,
    DIV,
    MOD,
    EQUALS,
    STRING_LITERAL,
    NUMBER_LITERAL,
    L_BRACKET,
    R_BRACKET,
    L_BRACE,
    R_BRACE,
    L_SQUARE_BRACKET,
    R_SQUARE_BRACKET,
    PERIOD,
    COMMA,
    COLON,
    SEMICOLON,
    WHITESPACE,
    ALPHANUMERIC,
    PLUS_EQUALS,
    MINUS_EQUALS,
    MULT_EQUALS,
    DIV_EQUALS
};


class Token
{
    public:
        TokenType type;                 // the type of token, as interpreted
        std::string data_payload;            // the string itself
        Token();
    protected:
    private:
};

#endif // TOKEN_H
