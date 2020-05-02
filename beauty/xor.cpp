#include <iostream>
#include <vector>
int main()
{
    std::vector<int> nums = {1,3,2};
    //std::vector<int> nums = {1,3,2,4,6,2,6,1,3};
    int a = 0;
    for(auto num:nums){
        a ^= num;
        std::cout << a << std::endl;
    }
    std::cout << a << std::endl;
}