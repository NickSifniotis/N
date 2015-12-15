#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/tokenizer.hpp>
#include "Tokeniser/Tokeniser.h"

using namespace std;


string readFile(string);       // reads the contents of a textfile and returns them in the form of a vector
                                            // whatever that is

string readFile(string f)
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


int main()
{
    string file_contents = readFile("hello_world.N");

    Tokeniser* tk = new Tokeniser(file_contents);
    while (tk->more_data())
    {
        Token toke = tk->currentToken();
        cout << toke.type << ": " << toke.data_payload << endl;
    }

    delete (tk);
}
