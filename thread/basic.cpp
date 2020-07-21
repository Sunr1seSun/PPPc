#include <iostream>
#include <thread>
#include <time.h>
using namespace std;
void func1(string &s)
{
    //s[1] = '8';
    while(true){
        if(clock()%1000 == 0) cout << "hello" << clock() <<endl;
    }
    //for (int i =0; i < 10; ++i)
    //    cout << "func1:" << i << s <<endl;
}

int main()
{
    string s1 = "my name is ?";
    // 引用传参需要ref()
    // move()将s1从主线程移动到子线程
    // move()在没必要的时候避免复制，将lvalue强转为rvalue
    // lvalue：locator value在内存中占有确定位置的对象
    thread t1(func1, ref(s1));
    thread t2(func1, ref(s1));
    thread t3(func1, ref(s1));
    //*this.join() 阻塞当前线程，直到*this执行完成
    //t1.join()
    //*this.detach() 分离线程，主线程不会等待*this执行完成
    /*
    try{
        for (int i =0; i < 10; ++i)
            cout << "main:" << i << endl;
    }catch(...){
        t1.join();
    }
    */
    t1.join();
    t2.join();
    t3.join();
    // hardware_concurrency一直是1，奇怪。
    cout << thread::hardware_concurrency;
    

    return 0;
}