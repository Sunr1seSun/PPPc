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
vector<Token> tok;
int main()
{
    string userInput;
    double res;
    // read a line
    cout << "Expression: ";
    while(cin){
        Token temp = get_token();
        tok.push_back(temp);
    }
    for(auto x:tok){
        cout << "kind:" << x.kind << " value:"<< x.value << endl;
    }

    //calculate


    // write_result 
    cout << "Result: " << res;
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