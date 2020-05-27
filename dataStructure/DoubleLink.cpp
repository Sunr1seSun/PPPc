#include <iostream>
using namespace std;


template<class T>
struct DNode
{
    T value;
    DNode *prev;
    DNode *next;
    DNode(){}
    DNode(T t): value(t), prev(nullptr), next(nullptr) {}
    DNode(T t, DNode *prev, DNode *next): value(t), prev(prev), next(next){}
};

template<class T>
class DoubleLink
{
public:
    DoubleLink();
    ~DoubleLink();

    int size();
    int isEmpty();

    T get(int index);
    T getFirst();
    T getLast();

    int insert(int index, T t);

    int del(int index);

    void show();


private:
    int count;
    DNode<T> *phead;
    DNode<T> *ptail;
    DNode<T> *getNode(int index);
};

template<class T>
DoubleLink<T>::DoubleLink() : count(0)
{
    phead = new DNode<T>();
    ptail = new DNode<T>();
    phead->next = ptail;
    ptail->prev = phead;
}
template<class T>
DoubleLink<T>::~DoubleLink()
{
    DNode<T> *pDelete;
    DNode<T> *p = phead;
    while(p != ptail){
        pDelete = p;
        p = p->next;
        delete pDelete;
    }
    delete ptail;
}
template<class T>
DNode<T>* DoubleLink<T>::getNode(int index)
{
    if(index < 0 || index > count){
        cout << "Wrong index!" << endl;
        return nullptr;
    }
    DNode<T>* pindex;
    if(index <= count/2)
    {
        pindex = phead;
        for(int i=0; i <= index; ++i){
            pindex = pindex->next;
        }
    }else{
        pindex = ptail;
        for(int i=count-1; i >= index; --i){
            pindex = pindex->prev;
        }
    }
    return pindex;
}

template<class T>
T DoubleLink<T>::get(int index)
{
    DNode<T> *p = getNode(index);
    return p->value;
}
template<class T>
T DoubleLink<T>::getFirst()
{
    return phead->next->value;
}
template<class T>
T DoubleLink<T>::getLast()
{
    return ptail->prev->value;
}
template<class T>
int DoubleLink<T>::insert(int index, T t)
{
    DNode<T> *p = getNode(index);
    DNode<T> *cur = new DNode<T>(t, p->prev, p);
    p->prev->next = cur;
    p->prev = cur;
    ++count;
    return 0;
}
template<class T>
int DoubleLink<T>::del(int index)
{
    DNode<T> *p = getNode(index);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
}

template<class T>
void DoubleLink<T>::show()
{
    DNode<T>* p = phead;
    while(p->next != ptail){
        p = p->next;
        cout << p->value <<"-";
    }
    cout << endl;
}

int main()
{
    DoubleLink<int> l1;
    l1.insert(0,4);
    l1.insert(0,5);
    l1.insert(1,55);
    l1.show();
    //cout<<l1.get(1) << endl;

    l1.del(1);
    l1.show();
}
