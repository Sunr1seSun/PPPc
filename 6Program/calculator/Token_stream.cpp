#include "Token_stream.h"
#include <iostream>
Token_stream::Token_stream()
:full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) std::cout << "putback() into a full buffer"<< std::endl;
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full=false;
        return buffer;
    } 

    char ch;
    std::cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case print:    // for "print"
    case quit:    // for "quit"
    case '(': case ')': 
    case '+': case '-': 
    case '*': case '/': case '%':
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        {    
            std::cin.putback(ch);         // put digit back into the input stream
            double val;
            std::cin >> val;              // read a floating-point number
            return Token(number,val);   // let '8' represent "a number"
        }
    default:
        std::cout << ch << std::endl;
        throw std::runtime_error("Bad token");
    }
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
{
    if(full && c == buffer.kind){
        full = false;
        return;
    }
    full = false;
    char ch = 0;
    while(std::cin >> ch)
        if(ch == c) return;
}