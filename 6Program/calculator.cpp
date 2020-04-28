#include "std_lib_facilities.h"
class Token{
public:
    // '()','+','-','*','/','8' 
    char kind;
    double value;
    Token(char ch = char()):kind(ch), value(0){}
    Token(char ch, double val):kind(ch), value(val){}
};
Token get_token();
double expression();
double term();
double primary();

vector<Token> tok;
int main()
{
    // read a line
    // 词法分析
    /*
    cout << "Expression: ";
    while(cin){
        Token temp = get_token();
        tok.push_back(temp);
    }
    for(auto x:tok){
        cout << "kind:" << x.kind << " value:"<< x.value << endl;
    }
    */
    //calculate
    // 语法分析:按优先级分块
    /*
    Expression:
          Term
          Expression "+" Term         // addition
          Expression "–" Term         // subtraction
    Term:
          Primary
          Term "*" Primary             // multiplication
          Term "/" Primary              // division
          Term "%" Primary               // remainder (modulo)
    Primary:
          Number
           "(" Expression ")"             // grouping
    Number:
          floating-point-literal
    */
   
   try{
        while(cin)
            cout << "=" << expression() << endl;
        keep_window_open();
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

Token get_token()
{
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

double expression()
{
    double left = term();
    Token t = get_token();
    while(true){
        switch(t.kind){
            case '+':
                left += term();
                t = get_token();
                break;
            case '-':
                left -= term();
                t = get_token();
                break;
            default:
                return left;
        }
    }
}

double term()
{
    double left = primary();
    Token t = get_token();
    while(true){
        switch(t.kind){
            case '*':
                left *= primary();
                t = get_token();
                break;
            case '/':
            {
                double d = primary();
                if(d == 0) error("dividi by zero");
                left /= primary();
                t = get_token();
                break;
            }
            /*
            case '%':
                left %= primary();
                t = get_token();
                break;
            */
            default:
                return left;
        }
    }
}

double primary()
{
    Token t = get_token();
    switch(t.kind){
        case '(':
        {
            double d = expression();
            t = get_token();
            if(t.kind != ')') error("')' expected");
            return d;
        }
        case 'n':
            return t.value;
        default:
            error("primary expected");
    }
}