#ifndef TOKENISER_H
#define TOKENISER_H

#include "Token.h"
#include <string>
#include <boost/tokenizer.hpp>


class Tokeniser
{
    public:
        Tokeniser();                            // null constructor, not sure if srs
        Tokeniser(std::string data_to_tokenise);     // construct the tokeniser and get ready to rumble.
        ~Tokeniser();                           // DESTRUCTOR
        Token currentToken();                   // returns the current token.
        void next();                            // advances to the next token.
        bool more_data();                       // returns true if next will return useful data, false otherwise.
    protected:
    private:
        boost::tokenizer<boost::char_separator<char> > *tk;     // the basic tokeniser itself
        boost::tokenizer<boost::char_separator<char> >::iterator tk_iterator;      // the iterator
        std::string currentDataPayload();            // returns the defererenced iterator, in the form of a string
};

#endif // TOKENISER_H
