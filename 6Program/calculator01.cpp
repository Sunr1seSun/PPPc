#include "std_lib_facilities.h"
//在该版本下因为token是string读入，不同字符间必须用空格分割。
//-----------------------------------------------
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
    string word;
    Token cur;
    cin >> word;
    if(cin.eof()){
        Token temp('z');
        return temp;
    }
    if(word.length() == 1){
        switch(word[0]){
            case '+':
            case '-':
            case '*':
            case '/':
            case '(':
            case ')':
            {
                Token temp(word[0]);
                return temp;
            }
            default:
            {
                Token temp('n', stof(word));
                return temp;
            }
        }
    }else{
        Token temp('n', stof(word));
        return temp;
    }
}
//--------------------------------------------------
Token_stream ts;
double expression();
double term();
double primary();
//--------------------------------------------------
double expression()
{
    double left = term();
    Token t = ts.get();
    while(true){
        switch(t.kind){
            case '+':
                cout << "counting:" << left << " + term()" << endl;
                left += term();
                t = ts.get();
                break;
            case '-':
                cout << "counting:" << left << " - term()" << endl;
                left -= term();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}
double term()
{
    double left = primary();
    Token t = ts.get();
    while(true){
        switch(t.kind){
            case '*':
                cout << "counting:" << left << " * primary()" << endl;
                left *= primary();
                t = ts.get();
                break;
            case '/':
            {
                double d = primary();
                if(d == 0)
                    error("divide by zero");
                cout << "counting:" << left << " / primary()" << endl;
                left /= d;
                t = ts.get();
                break;
            }
            default:
                ts.putback(t);
                return left;
        }
    }
}

double primary()
{
    Token t = ts.get();
    switch(t.kind){
        case '(':
        {
            double d = expression();
            t = ts.get();
            if(t.kind != ')') error("')' expected");
            cout << "number in () is " << d << endl;
            return d;
        }
        case 'n':
            cout << "primary() = " << t.value << endl;
            return t.value;
        default:
            error("primary expected");
    }
}

int main()
{
    try{
        double val = 0;
        while(cin){
            val = expression();
            cout << "=" << val << endl;
        }
   }catch(exception& e){
       cerr << e.what() << endl;
       keep_window_open();
       return 1;
   }catch(...){
       cerr << "exception" << endl;
       keep_window_open();
       return 2;
   }
}