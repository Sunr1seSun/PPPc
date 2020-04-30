#include "Token_stream.h"
#include <iostream>
#include <cmath>

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback() 

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
        {    
            double d = expression();
            t = ts.get();
            if (t.kind != ')') throw std::runtime_error("')' expected");
            return d;
        }
    case number:
        return t.value;  // return the number's value
    case '-':
        return -primary();
    case '+':
        return primary();
    default:
        throw std::runtime_error("primary expected");
    }
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = primary();
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '%':
            {
                double d = primary();
                if(d == 0) throw std::runtime_error("%:divide by zero");
                left = fmod(left, d);
                t = ts.get();
                break;
            }
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
            {    
                double d = primary();
                if (d == 0) throw std::runtime_error("divide by zero");
                left /= d; 
                t = ts.get();
                break;
            }
        default: 
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {    
        switch(t.kind) {
        case '+':
            std::cout << "counting:" << left << " + term()" << std::endl;
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            std::cout << "counting:" << left << " + term()" << std::endl;
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default: 
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

//------------------------------------------------------------------------------
void calculate()
{
    std::string greeting("Welcome to our simple calculator.\nPlease enter expressions using floating-point numbers.\n");
    std::string tips("'1+1=' to count, 'x' to quit.\n");
    std::cout << greeting << tips; 
    double val = 0;
    while (std::cin) {
        try{
            std::cout << "> ";
            Token t = ts.get();
            while(t.kind == print) t = ts.get();
            if (t.kind == quit) return;
            ts.putback(t);
            std::cout << "= " << expression()<< std::endl;
        }
        catch(std::exception& e){
            std::cerr << e.what() << std::endl;
            ts.ignore(print);
        }  
    }
}


int main()
try
{
    calculate();
}
catch (std::exception& e) {
    std::cerr << "error: " << e.what() << '\n'; 
    return 1;
}
catch (...) {
    std::cerr << "Oops: unknown exception!\n"; 
    return 2;
}

//------------------------------------------------------------------------------