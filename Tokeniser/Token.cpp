#include "Token.h"
#include <iostream>

using namespace std;


Token::Token()
{
    type = TokenType::NONE;
    data_payload = "";
}

void Token::print_self()
{
    string res = "";
    switch(type)
    {
        case TokenType::NONE:
            res = "NONE [" + data_payload + "]";
            break;
        case TokenType::PLUS:
            res = "PLUS";
            break;
        case TokenType::MINUS:
            res = "MINUS";
            break;
        case TokenType::MULT:
            res = "MULT";
            break;
        case TokenType::DIV:
            res = "DIV";
            break;
        case TokenType::MOD:
            res = "MOD";
            break;
        case TokenType::EQUALS:
            res = "EQ";
            break;
        case TokenType::STRING_LITERAL:
            res = "STRING: [" + data_payload + "]";
            break;
        case TokenType::NUMBER_LITERAL:
            res = "NUMBER: [" + data_payload + "]";
            break;
        case TokenType::L_BRACKET:
            res = "L_BRACKET";
            break;
        case TokenType::R_BRACKET:
            res = "R_BRACKET";
            break;
        case TokenType::L_BRACE:
            res = "L_BRACE";
            break;
        case TokenType::R_BRACE:
            res = "R_BRACE";
            break;
        case TokenType::L_SQUARE_BRACKET:
            res = "L_SQ_BR";
            break;
        case TokenType::R_SQUARE_BRACKET:
            res = "R_SQ_BR";
            break;
        case TokenType::PERIOD:
            res = "PERIOD";
            break;
        case TokenType::COMMA:
            res = "COMMA";
            break;
        case TokenType::COLON:
            res = "COLON";
            break;
        case TokenType::SEMICOLON:
            res = "SEMICOLON";
            break;
        case TokenType::WHITESPACE:
            res = "WHITESPACE";
            break;
        case TokenType::ALPHANUMERIC:
            res = "IDENTIFIER [" + data_payload + "]";
            break;
        case TokenType::PLUS_EQUALS:
            res = "PLUSEQ";
            break;
        case TokenType::MINUS_EQUALS:
            res = "MINEQ";
            break;
        case TokenType::MULT_EQUALS:
            res = "MULEQ";
            break;
        case TokenType::DIV_EQUALS:
            res = "DIVEQ";
            break;
        case TokenType::END_OF_FILE:
            res = " << EOF >>";
            break;
        default:
            break;
    }
    cout << res;
}
