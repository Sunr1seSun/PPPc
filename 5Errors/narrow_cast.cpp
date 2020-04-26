#include "std_lib_facilities.h"
int main()
{
    int x1 = 5;
    try{
        int x1 = narrow_cast<int>(2.9);
    }catch(runtime_error &e){
        cout << "hahah" <<endl;
    }
    cout << x1;
}