#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<string> numbers = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string s = "sldkj skl 8 sdkj 9 lksdj 1 slfkj 0";
    for(int i = 0; i < s.size(); ++i){
        if(s[i] <= '9' && s[i] >= '0'){
            s.insert(i+1, numbers[s[i] - '0']);
            s.erase(i,1);
        }
    }
    cout << s;
}
