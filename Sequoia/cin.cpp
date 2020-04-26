#include"std_lib_facilities.h"
int main()
{
    try{
        double d = 0;
        cin >> d;
        if(!cin)
            error("no");
    }catch(runtime_error& e){
        cerr << "runtime error:" << e.what() << endl;
    }
    error("default");
    
}