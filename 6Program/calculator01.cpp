#include "std_lib_facilities.h"
class Token{
public:
    // '()','+','-','*','/','n' 
    char kind;
    double value;
    Token(char ch = char()):kind(ch), value(0){}
    Token(char ch, double val):kind(ch), value(val){}
};

class Token_stream{
    public:
        Token get();
        void putback(Token t);
    private:
        bool full {false};
        Token buffer = {'0'};
};

void Token_stream::putback(Token t)
{
    if(full) error("putback into a full buffer");
    buffer = t;
    full = true;
}

Token Token_stream::get()
{
    if(full){
        full = false;
        return buffer;
    }
    
}