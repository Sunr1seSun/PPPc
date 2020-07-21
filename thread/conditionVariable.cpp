#include <iostream>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

// 向队列中放一个数字。
void function_1() {
    int count = 10;
    while (count > 0) {
        std::unique_lock<std::mutex> locker(mu);
        q.push_front(count);
        locker.unlock();
        cond.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        count--;
    }
}

// 如果队列不为空，将队列中的数字打印出来。
void function_2() {
    int data = 0;
    while ( data != 1) {
        std::unique_lock<std::mutex> locker(mu);
        //每次唤醒都要再判断一下q.empty()
        /*
        while (q.empty()) {
            cond.wait(locker);
            std::cout<< "1" << std::endl;
        }*/
        cond.wait(locker, [](){return !q.empty;});
        data = q.back();
        q.pop_back();
        locker.unlock();
        std::cout << "t2 got a value from t1: " << data << std::endl;
    }
}
int main() {
    std::thread t1(function_1);
    std::thread t2(function_2);
    t1.join();
    t2.join();
    return 0;
}