#include "std_lib_facilities.h"
int main()
{
    string temp;
    vector<string> accepted = {"cm", "m", "in", "ft"};
    vector<double> nums;
    while(cin >> temp)
    {
        string count = "";
        string units = "";
        bool flag = true;
        for(auto i:temp){
            if(i>='0' && i<='9' && flag == true){
                count.push_back(i);
                continue;
            }else{
                flag = false;
                units.push_back(i);
            }
        }
        double countNum = atoi(count.c_str());
        cout << "count:" << countNum << endl;
        cout << "units:" << units << endl;
        if(find(accepted.begin(),accepted.end(),units) == accepted.end()){
            cout << "not accepted!" << endl;
            continue;
        }else{
            if(units == "cm") ;
            if(units == "in") countNum *= 2.54;
            if(units == "m") countNum *= 100;
            if(units == "ft") countNum *=12*2.54;
        }
        cout << "final num:" << countNum << " cm" << endl;
        nums.push_back(countNum);
    }
    sort(nums);
    cout << endl;
    for(auto cur: nums){
        cout << cur << " ";
    }
}