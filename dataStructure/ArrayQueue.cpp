#include <iostream>

using namespace std;

template<class T>
class ArrayQueue{
public:
    ArrayQueue(int size);
    ~ArrayQueue();

    int size();
    void push(T value);
    T pop();
private:
    int count=0;
    int capacity;
    T *arr;
};

template<class T>
ArrayQueue<T>::ArrayQueue(int size):capacity(size)
{
    arr = new T[size];
    if(!arr){
        cout << "arr malloc error!" << endl;
    }
}

template<class T>
ArrayQueue<T>::~ArrayQueue()
{
    if(arr){
        delete[] arr;
        arr = nullptr;
    }
}

template<class T>
void ArrayQueue<T>::push(T value)
{
    arr[count++] = value;
}

template<class T>
T ArrayQueue<T>::pop()
{
    T ret = arr[0];
    --count;
    for(int i = 0; i < count; ++i){
        arr[i] = arr[i+1];
    }
    return ret;
}

template<class T>
int ArrayQueue<T>::size()
{
    return count;
}

int main()
{
    ArrayQueue<int> q(12);
    
    for(int i = 0; i < 10; ++i)
        q.push(i);
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    return 0;
}
