#include <iostream>
#include <vector>
#include "ProgramStatement.h"
#include "Parser.h"

using namespace std;


int main()
{
    Parser *parser = new Parser();

    vector<ProgramStatement*> *interpreted_program = parser -> parse("hello_world.N");

    for (vector<ProgramStatement*>::iterator it = interpreted_program->begin(); it != interpreted_program->end(); ++it)
    {
        ProgramStatement *ptr = *it;
        ptr -> print_self();
        cout << endl;
    }


    // delete all the shit that the parser produced for us
    // geez
    // what I wouldn't give for garbage collection
    for (vector<ProgramStatement*>::iterator it = interpreted_program->begin(); it != interpreted_program->end(); ++it)
    {
        ProgramStatement *ptr = *it;
        delete (ptr);
    }
    delete (interpreted_program);
    delete (parser);
}
