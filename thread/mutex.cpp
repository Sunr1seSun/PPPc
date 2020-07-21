#include <iostream>
#include <string>
#include <thread>
using namespace std;
#include <mutex>
#include <fstream>
/*
mutex mu;
void shared_print(string msg, int id)
{
    lock_guard<mutex> guard(mu);
    // lock unlock不推荐使用
    //mu.lock();
    cout << msg << id << endl;
    //mu.unlock();
}
*/
class LogFile
{
    public:
        LogFile(){
            f.open("log.txt");
        }
        void shared_print(string id, int value){
            lock(mu, mu2);
            lock_guard<mutex> locker(mu, adopt_lock);
            lock_guard<mutex> locker2(mu2, adopt_lock);
            cout << id << ":" << value << endl; 
        }
    protected:
    private:
        mutex mu;
        mutex mu2;
        ofstream f;
};


void func1(LogFile& log)
{
    for (int i = 0; i > -100; --i){
        log.shared_print("From t1:", i);
    }
}

int main()
{
    LogFile log;
    thread t1(func1,ref(log));
    for(int i = 0; i < 100; ++i){
        log.shared_print("From main:", i);
    }
    t1.join();
    return 0;
}