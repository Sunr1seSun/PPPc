#include "easyTag.h"
#include "BDDTag.h"
#include <set>
#include <ctime>

#define LAST_TIME(begin, end) (end-begin) / CLOCKS_PER_SEC * 1000

void printBDDTag(BDDTag &t)
{
    std::cout << "-----------This is BDDTag -------------" << std::endl;
    for(int i = 0; i < t.nodes.size(); ++i){
        std::cout << i << ":";
        std::cout << "(" << t.nodes[i].seg.begin << "," << t.nodes[i].seg.end << ")";
        std::cout << std::endl; 
    }

}
void printEasyTag(easyTag &t)
{
    std::cout << "-----------This is EasyTag -------------" << std::endl;
    for(int i = 0; i < t.nodes.size(); ++i){
        std::cout << i << ":";
        for(auto x: *t.nodes[i]){
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    srand(time(0));
    double start,end;
    BDDTag t;
    start = clock();
    for(int i =0; i < 1000; ++i) t.insert(i);
    std::cout << "BDDSIZE:" << sizeof(TagNode) << std::endl;

    for(int i =0; i < 4000; ++i) t.combine(int(rand()%t.nodes.size()),int(rand()%t.nodes.size()));
    end = clock();
    std::cout << "BDD:"<< LAST_TIME(start, end) << "ms" << std::endl;

    easyTag t2;
    start = clock();
    for(tag_off i =0; i < 1000; ++i) t2.insert(i);

    for(int i =0; i < 4000; ++i) t2.combine(int(rand()%t2.nodes.size()),int(rand()%t2.nodes.size()));
    end = clock();
    std::cout << "easy:"<< LAST_TIME(start, end) << "ms" << std::endl;
    //printBDDTag(t);
    printEasyTag(t2);
    
}