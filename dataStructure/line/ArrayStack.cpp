#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template<class T>
class ArrayStack{
public:
    ArrayStack(int size);
    ~ArrayStack();

    void push(T t);
    T pop();
    int size();
    int isEmpty();
private:
    int count=0;
    int capacity;
    T *arr;
};
template<class T>
ArrayStack<T>::ArrayStack(int size):capacity(size)
{
    arr = new T[size];
    if(!arr){
        cout << "arr malloc error!" << endl;
    }
}
template<class T>
ArrayStack<T>::~ArrayStack()
{
    if(arr)
    {
        //使用delete[] arr释放动态数组
        cout << "sizeof(T):" << sizeof(T) << endl;
        delete[] arr;
        arr = nullptr;
    }
}
template<class T>
void ArrayStack<T>::push(T t)
{
    if (count == capacity){
        cout << "Out of bound!" << endl;
        cout << count;
        return;
    }
    arr[count++] = t;
}
template<class T>
T ArrayStack<T>::pop()
{
    T ret = arr[count-1];
    --count;
    return ret;
}
template<class T>
int ArrayStack<T>::size()
{
    return count;
}

int main()
{
    ArrayStack<string> s(20);
    for(int i = 0; i < 20; ++i){
        string add(i,'a');
        //cout << add << endl;
        s.push(add);
    }
    cout << s.pop() << endl;
    cout << "s.size():" << s.size() << endl;
    //cout << s.pop() << endl;

    return 0;
}
