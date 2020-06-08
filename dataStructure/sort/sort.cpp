#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

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

//插入排序
/*
    1、外循环：i是当前考察的数，i左边有序。
    2、内循环：在有序中找到nums[j]>nums[i]。
    3、将j到i-1范围内的数右移。
*/
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

//快速排序
/*
    1、cur = nums[left]
    2、从右往左找节点替换nums[l]
    3、从左往右找节点替换nums[r]
    4、cur找到合适位置，左右子数组分别处理。
*/
void quick(vector<int> &nums, int left, int right)
{
    if(left<right){
        int l = left, r = right;
        int cur = nums[left];
        while(l<r){
            while(l<r && nums[r] >= cur)
                --r;
            nums[l] = nums[r];
            while(l<r && nums[l] <= cur)
                ++l;
            nums[r] = nums[l];
        }
        nums[l] = cur;
        quick(nums, left, l-1);
        quick(nums, l+1, right);
    }
}
vector<int> quickSort(vector<int> nums)
{
    quick(nums, 0, nums.size()-1);
    return nums;
}

//希尔排序
/*
    1、分组，每次步长为原来一半。
    2、对每个分组做插入排序。
*/
void shellInsertSort(vector<int> &nums, int start, int gap)
{
    for(int i = start; i < nums.size(); i += gap){
        int cur = nums[i];
        for(int j = start; j < i; j += gap){
            if(nums[j] > cur){
                for(int k = i; k > j; k -= gap)
                    nums[k] = nums[k-gap];
                nums[j] = cur;
                break;
            }
        }
    }
}
vector<int> shellSort(vector<int> nums)
{
    int gap = nums.size()/2;
    for(gap; gap>0; gap/=2){
        for(int i=0; i<gap; ++i){
            shellInsertSort(nums,i,gap);
        }
    }
    return nums;
}

//选择排序
vector<int> selectSort(vector<int> nums)
{
    int n = nums.size();
    for(int i = n-1; i>0; --i){
        int maxIndex = i;
        for(int j = 0; j < i; ++j){
            if(nums[j] > nums[maxIndex]){
                maxIndex = j;
            }
        }
        swap(nums[i], nums[maxIndex]);
    }
    return nums;
}

//堆排序
/*
    parent = (i-1)/2
    child1 = 2i+1
    child2 = 2i+2
    实现思路：
        1、从一个节点开始heapify（递归）
        2、从parent处往前heapify建立堆。
        3、每次将堆顶换到末尾扔出堆，然后修复堆。
*/
void heapify(vector<int> &nums, int i, int n)
{
    int c1 = 2 * i + 1;
    int c2 = 2 * i + 2;
    int max = i;
    if(c1 < n && nums[c1] > nums[max]){
        max = c1;
    }
    if(c2 < n && nums[c2] > nums[max]){
        max = c2;
    }
    if(max != i){
        swap(nums[max],nums[i]);
        heapify(nums, max, n);
    }
}
void buildHeap(vector<int> &nums)
{
    int n = nums.size();
    int last = (n-2) / 2;
    for(int i = last; i >=0; --i){
        heapify(nums, i, n);
    }
}
vector<int> heapSort(vector<int> nums)
{
    buildHeap(nums);
    for(int i = nums.size()-1; i > 0; --i){
        swap(nums[0], nums[i]);
        heapify(nums,0,i);
    }
    return nums;
}

//归并排序
void merge(vector<int> &nums, int left, int mid, int right)
{
    vector<int> tmp;
    int l = left;
    int r = mid+1;
    while(l <= mid && r <= right){
        if(nums[l] <= nums[r]){
            tmp.push_back(nums[l++]);
        }else{
            tmp.push_back(nums[r++]);
        }
    }
    while(l <= mid)
        tmp.push_back(nums[l++]);
    while(r <= right)
        tmp.push_back(nums[r++]);
    for(int i=left;i<=right;++i){
        nums[i] = tmp[i-left];
    }
}
void mergeSort(vector<int> &nums, int left, int right)
{
    if(left>=right)
        return;
    int mid = (left+right)/2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid+1, right);

    merge(nums, left, mid, right);
}
vector<int> mergeSort(vector<int> nums)
{
    mergeSort(nums, 0, nums.size()-1);
    return nums;
}

vector<int> bucketSort(vector<int> nums)
{
    if(nums.empty()) return {};
    int low = *min_element(nums.begin(), nums.end());
    int high = *max_element(nums.begin(), nums.end());
    int n = high - low + 1;
    vector<int> buckets(n);
    for(int num: nums) ++buckets[num-low];
    vector<int> res;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < buckets[i]; ++j){
            res.push_back(i+low);
        }
    }
    return res;
}

int main()
{
    double start,end;
    vector<int> nums = getRandomVector(20000);
    //vector<int> nums = {5,2,3,1};
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
    if(bubble2Nums == bubbleNums)
        cout << "bubbleSort2:"<< LAST_TIME(start, end) << "ms" << endl;

    // insertSort
    start = clock();
    vector<int> insertSortNums = insertSort(nums);
    end = clock();
    if(insertSortNums == bubbleNums)
        cout << "insertSort:"<< LAST_TIME(start, end) << "ms" << endl;

    // quickSort
    start = clock();
    vector<int> quickSortNums = quickSort(nums);
    end = clock();
    if(quickSortNums == bubbleNums)
        cout << "quickSort:"<< LAST_TIME(start, end) << "ms" << endl;

    // shellSort
    start = clock();
    vector<int> shellSortNums = shellSort(nums);
    end = clock();
    if(shellSortNums == bubbleNums)
        cout << "shellSort:"<< LAST_TIME(start, end) << "ms" << endl;

    // selectSort
    start = clock();
    vector<int> selectSortNums = selectSort(nums);
    end = clock();
    if(selectSortNums == bubbleNums)
        cout << "selectSort:"<< LAST_TIME(start, end) << "ms" << endl;

    // heapSort
    start = clock();
    vector<int> heapSortNums = heapSort(nums);
    end = clock();
    if(heapSortNums == bubbleNums)
        cout << "heapSort:"<< LAST_TIME(start, end) << "ms" << endl;

    // mergeSort
    start = clock();
    vector<int> mergeSortNums = mergeSort(nums);
    end = clock();
    if(mergeSortNums == bubbleNums)
        cout << "mergeSort:"<< LAST_TIME(start, end) << "ms" << endl;

    start = clock();
    vector<int> bucketSortNums = bucketSort(nums);
    end = clock();
    if(bucketSortNums == bubbleNums)
        cout << "bucketSort:"<< LAST_TIME(start, end) << "ms" << endl;

    //for(auto i:mergeSort(nums)) cout << i << " ";
    
    return 0;
}
