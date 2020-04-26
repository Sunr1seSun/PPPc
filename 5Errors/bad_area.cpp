#include "std_lib_facilities.h"
class Bad_area{};

int area(int length, int width)
{
    if(length <= 0 || width <= 0)
        throw Bad_area{};
    return length * width;
}

int main()
{
    try{
        area(4,3);
    }catch(Bad_area){
        cout << "interesting!" << endl;
    }
    try{
        vector<int> v{1,2,3,4};
        cout << v[1] << endl;
    }catch(out_of_range){
        cout << "im here" << endl;
    }
}