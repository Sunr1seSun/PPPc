#include "easyTag.h"
#include "BDDTag.h"
#include <set>
#include <ctime>

#define LAST_TIME(begin, end) (end-begin) / CLOCKS_PER_SEC * 1000
int main()
{
    srand(time(0));
    double start,end;
    BDDTag t;
    start = clock();
    for(int i =0; i < 1000; ++i) t.insert(i);

    //for(int i =0; i < 10; ++i) t.combine(int(rand()),int(rand()));
    end = clock();
    std::cout << "BDD:"<< LAST_TIME(start, end) << "ms" << std::endl;

    easyTag t2;
    start = clock();
    for(tag_off i =0; i < 10; ++i) t2.insert(i);

    for(int i =0; i < 20; ++i) t2.combine(int(rand()%t2.nodes.size()),int(rand()%t2.nodes.size()));
    end = clock();
    std::cout << "easy:"<< LAST_TIME(start, end) << "ms" << std::endl;
    for(int i = 0; i < t2.nodes.size(); ++i){
        std::cout << i << ":";
        for(auto x: *t2.nodes[i]){
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
}