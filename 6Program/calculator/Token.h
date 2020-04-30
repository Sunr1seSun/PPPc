#ifndef TOKEN_H
#define TOKEN_H
const char number = '8';
const char quit = 'q';
const char print = ';';

class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    Token(char ch);    // make a Token from a char 
    Token(char ch, double val);     // make a Token from a char and a double
};

#endif