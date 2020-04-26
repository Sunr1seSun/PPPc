#include "std_lib_facilities.h"
int main()
{
    vector<string> disliked = {"a", "bc", "sdf"};
    vector<string> words;
    for(string temp; cin >> temp;){
        words.push_back(temp);
    }
    for(auto temp: words){
        if(find(disliked.begin(), disliked.end(), temp)!= disliked.end()){
            cout << "BLEEP" << endl;
        }else{
            cout << temp << endl;
        }
    }
}