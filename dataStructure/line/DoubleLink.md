![1590642857384](.\photo\1590642857384.png)

Node:

```c++
template<class T>
struct DNode
{
    T value;
    DNode *prev;
    DNode *next;
};
```

Linked list:

```c++
template<class T>
class DoubleLink
{
private:
    int count;
    DNode<T> *phead;
    DNode<T> *ptail;
public:
    插入;
    删除;
    获取;
}
```

