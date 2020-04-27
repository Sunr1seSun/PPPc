//返回数组中所有元素被第一个元素除的结果

#include <iostream>
#include <vector>
using namespace std;
void divide(vector<int>& nums)
{
    int temp = nums[0];
    for(auto &num:nums){
        num /= temp;
    }
}
int main()
{
    vector<int> test {2,4,6,8,16,14,8};
    divide(test);
    for(auto num: test){
        cout<< num << endl;
    }

}