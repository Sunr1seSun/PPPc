#include <iostream>
#include <vector>

using namespace std;

void print(vector<int> nums){
    for(auto x: nums){
        cout << x << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> vec;
    for(int i = 0; i < 10; ++i)
        vec.push_back(i);
    auto itr = vec.begin();
    for(int i = 0; i < 1000; ++i)
        vec.push_back(i);
    
    vector<int> vec2 {5, 5, 5};
    vec2.insert(vec2.begin(), vec.begin(), vec.begin()+ 5);
    print(vec2);


    vector<int> v;
	for (int i = 0; i < 100000;i ++){
		v.push_back(i);
	}

	cout << "capacity:" << v.capacity() << endl;
	cout << "size:" << v.size() << endl;

	//此时 通过resize改变容器大小
	v.resize(10);

	cout << "capacity:" << v.capacity() << endl;
	cout << "size:" << v.size() << endl;

	//容量没有改变
	vector<int>(v).swap(v);

	cout << "capacity:" << v.capacity() << endl;
	cout << "size:" << v.size() << endl;

    return 0;
}
