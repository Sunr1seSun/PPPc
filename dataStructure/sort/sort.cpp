#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

#define LAST_TIME(begin, end) (end-begin) / CLOCKS_PER_SEC * 1000

// 公共
vector<int> getRandomVector(int size){
    srand(time(0));
    vector<int> nums;
    for(int i=0; i < size; ++i){
        nums.push_back(rand());
    }
    return nums;
}
void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
    return;
}

vector<int> bubbleSort1(vector<int> nums)
{   
    int n = nums.size();
    for(int i =n-1; i > 0; --i)
        for(int j=0; j<i; ++j){
            if(nums[j] > nums[j+1])
                swap(nums[j], nums[j+1]);
        }
    return nums;
}

//改进：有序时直接结束
vector<int> bubbleSort2(vector<int> nums)
{
    int n = nums.size();
    bool flag;
    for(int i =n-1; i > 0; --i){
        flag = 0;
        for(int j=0; j<i; ++j){
            if(nums[j] > nums[j+1]){
                swap(nums[j], nums[j+1]);
                flag = 1;
            }    
        }
        if(flag == 0)
            return nums;
    }
    return nums;
}

vector<int> insertSort(vector<int> nums)
{
    int n = nums.size();
    for(int i = 0; i < n; ++i){
        int cur = nums[i];
        for(int j = 0; j < i; ++j){
            if(nums[j] > cur){
                for(int k = i; k > j; --k)
                    nums[k] = nums[k-1];
                nums[j] = cur;
                break;
            }
        }
    }
    return nums;
}


int main()
{
    double start,end;
    vector<int> nums = getRandomVector(10000);
    //for(auto i:nums) cout << i << " ";
    // bubbleSort1
    start = clock();
    vector<int> bubbleNums = bubbleSort1(nums);
    end = clock();
    cout << "bubbleSort1:"<< LAST_TIME(start, end) << "ms" << endl;

    // bubbleSort2
    start = clock();
    vector<int> bubble2Nums = bubbleSort2(nums);
    end = clock();
    cout << "bubbleSort2:"<< LAST_TIME(start, end) << "ms" << endl;

    // insertSort
    start = clock();
    vector<int> insertSortNums = insertSort(nums);
    end = clock();
    cout << "insertSortMy:"<< LAST_TIME(start, end) << "ms" << endl;

    //for(auto i:insertSort(nums)) cout << i << " ";
    
    return 0;
}
