#include <unistd.h>
#include <stdlib.h>
#include <thread>
#include <ctime>
#include <iostream>
void func()
{
    clock_t t1 = clock();
    while(1){
        clock_t t1 = clock();
        while(clock()-t1 < 10){}
        usleep(10000);
    }
}

int main()
{
    func();
    return 0;
}